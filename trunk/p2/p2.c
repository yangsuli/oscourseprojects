#include "mysh.h"
#include "error.h"

int main(int argc, char *argv[]){
	if(argc > 2){
		error_and_exit();
	}
	if(argc == 1){
		lauch_shell(NULL);
	}else if(argc == 2){
		lauch_shell(argv[1]);
	}

	return 0;
}
