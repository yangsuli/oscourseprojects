#include <stdio.h>
#include "udp.h"
#include "mssg.h"

char buffer[BUFFER_SIZE];

int main(int argc, char *argv[])
{
    int sd = UDP_Open(20000);
    assert(sd > -1);

    struct sockaddr_in addr, addr2;
    char machine_name[] = "mumble-06.cs.wisc.edu";
    int rc = UDP_FillSockAddr(&addr, machine_name, 10020);
    assert(rc == 0);
    printf("filled sock addr\n");

    char message[BUFFER_SIZE];
//  sprintf(message, "hello world");

    rc = UDP_Write(sd, &addr, message, BUFFER_SIZE);
    printf("CLIENT:: sent message (%d)\n", rc);
    if (rc > 0) {
        int rc = UDP_Read(sd, &addr2, buffer, BUFFER_SIZE);
        printf("CLIENT:: read %d bytes (message: '%s')\n", rc, buffer);
    }

    return 0;
}

// need to implement these public routines
/*
int MFS_Init(char *hostname, int port);
int MFS_Lookup(int pinum, char *name);
int MFS_Stat(int inum, MFS_Stat_t *m);
int MFS_Write(int inum, char *buffer, int block);
int MFS_Read(int inum, char *buffer, int block);
int MFS_Creat(int pinum, int type, char *name);
int MFS_Unlink(int pinum, char *name);
*/
