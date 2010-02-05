#include <sys/wait.h>
#include <stdio.h>
#include "error.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE_LENGTH 5

const char prompt[] = "mysh> "; 

void read_one_line(char * buf, int n, FILE * input);

bool is_eol(char x){
	return (x == '\n' || x == '\r');
}
void initialize_buf_with_eol(char *buf, int size){
	int i = 0;
	for(i = 0; i<size; i++){
		buf[i] = '\n';
	}
}

int main(){

	char buf[MAX_LINE_LENGTH + 2];

	while(1){
		write(STDOUT_FILENO,prompt,strlen(prompt));
		read_one_line(buf, MAX_LINE_LENGTH + 2, stdin);
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
