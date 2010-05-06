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
/*
printf("  calling MFS_Lookup with -1\n");
    MFS_Lookup(-1, "usr");
    sleep(5);
printf("  calling MFS_Lookup with -2\n");
    MFS_Lookup(-2, "usr");
    sleep(5);
printf("  calling MFS_Lookup with -3\n");
    MFS_Lookup(-3, "usr");
*/

    printf("  calling MFS_Creat with arguments \n");
    pinum = 2;  
    int type = 1;  
    printf("  pinum, type, name = %d, %d, %s\n",pinum, type, name);
    MFS_Creat(pinum, type, name);
    sleep(5);
    printf("  calling MFS_Creat with arguments \n");
    pinum = 20;  
    type = 2;  
    printf("  pinum, type, name = %d, %d, %s\n",pinum, type, name);
    MFS_Creat(pinum, type, name);

//  MFS_Stat(inum, MFS_Stat_t *m);
//  int block = 4;
//  MFS_Write(inum, "buffer", block);
//  MFS_Read(inum, "buffer", block);
//  MFS_Unlink(int pinum, char *name);

    return 0;

}

