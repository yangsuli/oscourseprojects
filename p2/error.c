#include <unistd.h>
#include "error.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

const char error_message[30] = "An error has occurred\n";

void error_and_continue(){
	assert(write(STDERR_FILENO, error_message, strlen(error_message)) != -1);
}

void error_and_exit(){
        assert(write(STDERR_FILENO,error_message,strlen(error_message)) != -1);
	exit(1);
}
