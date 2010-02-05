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


bool is_eol(char x){
	return (x == '\n' || x == '\r');
}

void initialize_buf_with_eol(char *buf, int size){
	int i = 0;
	for(i = 0; i<size; i++){
		buf[i] = '\n';
	}
}
void run_command(char *cmd){

	pid_t pid;
	int arg_count = 0;
	char * argv[MAX_ARGUMENTS];

	argv[arg_count] = strtok(cmd,delims_for_args);
	while(argv[arg_count] != NULL){
		arg_count++;
		argv[arg_count] = strtok(NULL,delims_for_args);
	}
	//empty command, no error
	if(argv[0] == NULL){
		return;
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
		if(wait(NULL) == -1){
			error_and_exit();
		}
	}

}

int main(){

	char buf[MAX_LINE_LENGTH + 2];
	char * serial_cmds[MAX_COMMANDS];
	char * parallel_cmds[MAX_COMMANDS];	
	int serial_cmd_count;
	int parallel_cmd_count;
	pid_t pid[MAX_COMMANDS];

	while(1){
		write(STDOUT_FILENO,prompt,strlen(prompt));
		read_one_line(buf, MAX_LINE_LENGTH + 2, stdin);

		serial_cmd_count = 0;
		//So here we assumer that '+' is more asscoiative than ';' in our syntax
		cmds[serial_cmd_count] = strtok(buf,delims_for_cmds_serial);
		while(cmds[serial_cmd_count] != NULL){
			run_command(cmds[serial_cmd_count]);
			serial_cmd_count++;
			cmds[serial_cmd_count] = strtok(NULL,delims_for_cmds_serial);	       }


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
