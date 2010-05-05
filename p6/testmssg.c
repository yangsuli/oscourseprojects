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

printf("  calling MFS_Init() \n");
    MFS_Init(hostname, port);
//  MFS_Lookup(-1, "usr");
//  MFS_Stat(inum, MFS_Stat_t *m);
//  int block = 4;
//  MFS_Write(inum, "buffer", block);
//  MFS_Read(inum, "buffer", block);
//  MFS_Creat(int pinum, int type, char *name);
//  MFS_Unlink(int pinum, char *name);

    return 0;

}

