#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include "error.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mysh.h"
#include <errno.h>
#include <fcntl.h>

const char delims_for_args[] = " \t";
const char delims_for_cmds_serial[] = ";\n";
const char delims_for_cmds_parallel[] = "+";
const char prompt[] = "mysh> "; 
const char *support_build_in[NUM_BUILD_IN] = {"exit","pwd","cd"};
const char *redirection_chars = ">";
const char *grep_chars = "=";
const char *grep_path = "/bin/grep";


bool is_eol(char x){
	return (x == '\n' || x == '\r');
}

void initialize_buf_with_eol(char *buf, int size){
	int i = 0;
	for(i = 0; i<size; i++){
		buf[i] = '\n';
	}
}

bool check_build_in_cmd(char * str){
	int i = 0;
	for(i = 0; i<NUM_BUILD_IN; i++){
		if(strcmp(str,support_build_in[i]) == 0){
			return true;
		}
	}
	return false;
}

//this function doesn't deal with redirection and other stuff. It assumed that the argv[] passed to it is purely command arguments.
void deal_with_build_in(char *argv[]){
	if(strcmp(argv[0],"exit") == 0){
		if(argv[1] != NULL){
			error_and_continue();
			return;
		}
		//if the first token is "exit", exit the program. If there are exta arguments, error
		exit(0);
	}else if(strcmp(argv[0],"pwd") == 0){
		if(argv[1] != NULL){
			error_and_continue();
			return;
		}
		char buf[512];
		if(getcwd(buf,512) == NULL){
			error_and_exit();
		}
		strcat(buf,"\n");
		if(write(STDOUT_FILENO,buf,strlen(buf)) != strlen(buf)/* || write(STDOUT_FILENO,"\n",2) != 2*/){
			error_and_exit();
		}
	}else if(strcmp(argv[0],"cd") == 0){
		if(argv[2] != NULL){
			error_and_continue();
			return;
		}
		char *dir = argv[1];
		if(dir == NULL){
			dir = getenv("HOME");
		}

		//if there is no match in $HOME in current enviorment, do nothing
		if(dir != NULL){
			if(chdir(dir) == -1){
				//dir doesn't or other stuff
				error_and_continue();
				return;
			}
		}
	}else{
		//non supproted build_in cmd, shouldn't happen
		error_and_exit();
	}


}

// process the cmd line, deal with rediection and other stuff.
//just fork, do not wait
//if succesfully fork, return the number of processes if forked (should be 1)
//if an empty cmd or build in cmd is passed, return 0
//if fork failed, exit the program
int run_command(char *cmd){

	pid_t pid;
	int arg_count = 0;
	int fork_count = 0;
	char * argv[MAX_ARGUMENTS];
	char redirect_file[MAX_LINE_LENGTH];
	bool redirection_flag = false;
	bool grep_flag = false;
	char * keyword;
	char * redirec_char = strpbrk(cmd,redirection_chars);
	char * grep_char = strpbrk(cmd,grep_chars);

	//if there is a redirection charactor)
	if(redirec_char != NULL){
		//if more than one redireciton charactors or grepping char, bad syntax
		//Note that this implementation makes it very difficult to add support to >>. But whatever....
		if(strpbrk(redirec_char+1,redirection_chars) != NULL || grep_char != NULL){
			error_and_continue();
			return fork_count;
		}

		strcpy(redirect_file,redirec_char + 1);

		//change cmd, throw away all those > bla bla part
		//so that exec could recognize
		redirec_char[0] = '\0';

		parse_args(redirect_file,argv,MAX_ARGUMENTS,delims_for_args);

		if(argv[0] == NULL || argv[1] != NULL){
			error_and_continue();
			return fork_count;
		}

		redirection_flag = true;

		strcpy(redirect_file,argv[0]);

	}else if(grep_char != NULL){

		//change cmd, throw away those =...= output file stuff
		//so that exec could recognize
		grep_char[0] = '\0';

		parse_args(grep_char+1,argv,MAX_ARGUMENTS,grep_chars);

		if(argv[0] == NULL || argv[1] == NULL || argv[2] != NULL){
			error_and_continue();
			return fork_count;
		}

		//Note that here we allow whitespaces in keyword
		keyword = argv[0];

		parse_args(argv[1],argv,MAX_ARGUMENTS,delims_for_args);

		//if no outpuf file or more than one output file
		if(argv[0] == NULL || argv[1] != NULL){
			error_and_continue();
			return fork_count;
		}
		grep_flag = true;

		strcpy(redirect_file,argv[0]);
	}


	argv[arg_count] = strtok(cmd,delims_for_args);
	while(argv[arg_count] != NULL){
		arg_count++;
		argv[arg_count] = strtok(NULL,delims_for_args);
	}
	//empty command, no error
	if(argv[0] == NULL){
		return fork_count;
	}

	if(check_build_in_cmd(argv[0]) == true){
		//deal with build in cmd;
		deal_with_build_in(argv);
		return fork_count;
	}

	if((pid = fork()) < 0){
		error_and_exit();
	}else if(pid == 0){
		int fd;
		if(redirection_flag == true){
			if((fd = open(redirect_file,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1){
				error_and_exit();
			}
			if(dup2(fd,STDOUT_FILENO) == -1){
				error_and_exit();
			}
		}else if(grep_flag == true){
			int fd;
			int filedes[2];
			pid_t pid;
			if(pipe(filedes) == -1){
				error_and_exit();
			}
			if((pid = fork()) < 0){
				error_and_exit();
			}else if(pid > 0){//parent write the pipe
				close(filedes[0]);
				if(dup2(filedes[1],STDOUT_FILENO) == -1){
					error_and_exit();
				}
			}else{
				close(filedes[1]);
				if(dup2(filedes[0],STDIN_FILENO) == -1){
					error_and_exit();
				}
				if((fd = open(redirect_file,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == -1){
					error_and_exit();
				}
				if(dup2(fd,STDOUT_FILENO) == -1){
					error_and_exit();
				}
				char *grep_argv[3];
				grep_argv[0] = grep_path;
				grep_argv[1] = keyword;
				grep_argv[2] = NULL;
				if(execvp(grep_argv[0],grep_argv) == -1){
					error_and_exit();
				}
			}
		}


		if(execvp(argv[0],argv) == -1){
			//note that here just the child process exits.
			//Our shell still runs (after an error msg from
			//child appeared
			error_and_exit();
		}
	}else{
		fork_count++;
	}

	return fork_count;

}

void lauch_shell(char *batch_file){

	char buf[MAX_LINE_LENGTH + 2];
	char * serial_cmds[MAX_COMMANDS];
	int serial_cmd_count;
	FILE *input;

	if(batch_file != NULL){
		if((input = fopen(batch_file,"r")) == NULL){
			error_and_exit();
		}
	}else{
		input = stdin;
	}

	while(1){
		if(batch_file == NULL){
			write(STDOUT_FILENO,prompt,strlen(prompt));
		}
		if(read_one_line(buf, MAX_LINE_LENGTH + 2, input) == false){
			continue;
		}
		if(batch_file != NULL){
			write(STDOUT_FILENO,buf,strlen(buf));
		}

		serial_cmd_count = 0;
		//So here we assumer that '+' is more asscoiative than ';' in our syntax
		serial_cmds[serial_cmd_count] = strtok(buf,delims_for_cmds_serial);
		while(serial_cmds[serial_cmd_count] != NULL){
			serial_cmd_count++;
			serial_cmds[serial_cmd_count] = strtok(NULL,delims_for_cmds_serial);	      
		}
		serial_cmd_count = 0;
		while(serial_cmds[serial_cmd_count] != NULL){
			/*	if(strpbrk(serial_cmds[serial_cmd_count],delims_for_cmds_parallel) == NULL){
				run_command(serial_cmds[serial_cmd_count]);
				}else{ */
			run_parallel_commands(serial_cmds[serial_cmd_count]);
			/*	} */
			serial_cmd_count++;
		}

	}
}

bool read_one_line(char * buf, int n, FILE * input){
	bool correct_flag = true;
	static int i = 0;
	//always intialize the buf, so that one can tell if the command line read in is too long. There might be a better way of doing this....
	initialize_buf_with_eol(buf,n);

	//when fgets returns NULL, exit. Here we don't print en error msg because it may be the end of input. However, when fgets encounters an error, out program would also exit silently.
	if(fgets(buf, n, input) == NULL){
		exit(0);
	}

	//if the command line is too long
	if( !is_eol(buf[n - 2]) ){
		correct_flag = false;
		//read till the end of this line
		if(i == 0){
			error_and_continue();
		}
		i++;
		read_one_line(buf,n,input);
	}
	i = 0;

	return correct_flag;
}

void parse_args(char *buf, char **argv, int max_args, const char * delims){
	int arg_count = 0;
	argv[arg_count] = strtok(buf,delims);
	while(arg_count < max_args && argv[arg_count] != NULL){
		arg_count++;
		argv[arg_count] = strtok(NULL,delims);
	}
}

void run_parallel_commands(char *parallel_cmd){

	char * cmds[MAX_COMMANDS];
	int cmd_count = 0;
	int fork_count = 0;
	int i = 0;

	parse_args(parallel_cmd, cmds, MAX_COMMANDS, delims_for_cmds_parallel);

	cmd_count = 0;

	while(cmds[cmd_count] != NULL){
		if(run_command(cmds[cmd_count]) == 1){
			//	parse_args(cmds[cmd_count],argv[cmd_count],MAX_ARGUMENTS,delims_for_args);
			fork_count++;
		}
		cmd_count++;
	}


	for(i = 0; i < fork_count; i++){
		if(wait(NULL) == -1){
			fprintf(stderr,"wait error\n");
			error_and_exit();
		}
	}
}

