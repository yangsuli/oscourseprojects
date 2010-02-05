#include <sys/wait.h>
#include <stdio.h>
#include "error.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mysh.h"
#include <errno.h>

const char delims_for_args[] = " \n";
const char delims_for_cmds_serial[] = ";";
const char delims_for_cmds_parallel[] = "+";
const char prompt[] = "mysh> "; 
const char *support_build_in[NUM_BUILD_IN] = {"exit","pwd","cd"};


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
		fprintf(stderr,"build in\n");
		return fork_count;
	}

	if((pid = fork()) < 0){
		error_and_exit();
	}else if(pid == 0){
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

int main(){

	char buf[MAX_LINE_LENGTH + 2];
	char * serial_cmds[MAX_COMMANDS];
	int serial_cmd_count;

	while(1){
		write(STDOUT_FILENO,prompt,strlen(prompt));
		read_one_line(buf, MAX_LINE_LENGTH + 2, stdin);

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

void read_one_line(char * buf, int n, FILE * input){
	static int i = 0;
	//always intialize the buf, so that one can tell if the command line read in is too long. There might be a better way of doing this....
	initialize_buf_with_eol(buf,n);

	//when fgets returns NULL, exit. Here we don't print en error msg because it may be the end of input. However, when fgets encounters an error, out program would also exit silently.
	if(fgets(buf, n, input) == NULL){
		exit(0);
	}

	//if the command line is too long
	if( !is_eol(buf[n - 2]) ){
		//read till the end of this line
		if(i == 0){
			error_and_continue();
		}
		i++;
		read_one_line(buf,n,input);
	}
	i = 0;
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