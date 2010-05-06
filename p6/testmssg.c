#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mfs.h"

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
    char buffer[] = "SOME_BUFFER";
    int inum  = 3;
    int type = 1;  
    MFS_Stat_t m;

printf("  calling MFS_Init() \n");
    MFS_Init(hostname, port);

    ////////// Test a bunch of calls to MFS_Lookup //////
    MFS_Lookup(-1, "usr");
//  MFS_Lookup(-2, "usr");
//  MFS_Lookup(-3, "usr");

    //////// Test a bunch of Calls to Creat ///////////
    MFS_Creat(pinum, type, name);
    pinum = 20;  type = 2;  
    MFS_Creat(pinum, type, name);

//  MFS_Stat(inum, MFS_Stat_t *m);
    m.type = 1; m.size = 100; m.blocks = 20;
    MFS_Stat(inum, &m);

//  MFS_Write(inum, "buffer", block);
//  MFS_Read(inum, "buffer", block);
    MFS_Unlink(pinum, name);

    return 0;

}

