#include "mfs.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    if( argc != 3 ) {
        fprintf(stderr, "bad number of arguments passed in\n");
        fprintf(stderr, "usage: testclient [port] [hostname]\n");
        exit(1);
    }
    char * hostname = argv[2];
    int port = atoi( argv[1] );

    int pinum = 2;
    char name[] = "SOME_NAME";
    int inum  = 3;
    MFS_Stat_t m;

    MFS_Init(hostname, port);
    MFS_Lookup(-1, "usr");
    MFS_Lookup(pinum, name);
//  MFS_Stat(int inum, MFS_Stat_t *m);
//  MFS_Write(int inum, char *buffer, int block);
//  MFS_Read(int inum, char *buffer, int block);
//  MFS_Creat(int pinum, int type, char *name);
//  MFS_Unlink(int pinum, char *name);

    return 0;

}

