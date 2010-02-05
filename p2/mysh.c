#include <sys/wait.h>
#include <stdio.h>
#include "error.h"

#define MAX_LINE_LENGTH 512

int main(){
	error_and_continue();
	error_and_exit();
	fprintf(stderr,"this should not appear\n");
	return 0;
}
	

