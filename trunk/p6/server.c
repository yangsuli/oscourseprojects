#include <stdio.h>
#include "udp.h"
#include "mfs.h"
#include <fcntl.h>

#define BUFFER_SIZE (4096)

/*
 * demo code to show how to use udp
 *
int
main(int argc, char *argv[])
{
    int sd = UDP_Open(10000);
    assert(sd > -1);

    printf("waiting in loop\n");

    while (1) {
	struct sockaddr_in s;
	char buffer[BUFFER_SIZE];
	int rc = UDP_Read(sd, &s, buffer, BUFFER_SIZE);
	if (rc > 0) {
	    printf("SERVER:: read %d bytes (message: '%s')\n", rc, buffer);
	    sleep(10);
	    char reply[BUFFER_SIZE];
	    sprintf(reply, "reply");
	    rc = UDP_Write(sd, &s, reply, BUFFER_SIZE);
	}
    }

    return 0;
}
*/


int main(int argc, char *argv[]){
	if(argc != 2){
		printf("usage: server [portnm] [file-system-image]");
		exit(-1);
	}

	//TODO
	//listen to port and other stuff

	return 0;

}


int image_init(char * filename){
	if((fd = open(filename,O_WRONLY|O_CREAT|O_TRUNC)) == -1){
		fprintf(stderr,"open failed!\n");
		exit(-1);
	}
	//TODO initilize file image and stuff

	return 0;

}


