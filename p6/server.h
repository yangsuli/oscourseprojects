#ifndef __SERVER_H__
#define __SERVER_H__

#include "mfs.h"
#include <stdbool.h>

#define MFS_BLOCK_NUMS (4096)
#define MFS_PTR_NUMS 10

typedef struct __Inode_t{
	int type; //MFS_DIRECTORY or MFS_REGULAR
	int size; //bytes;
	int blocks;
	int ptr[MFS_PTR_NUMS]; //direct pointers, -1 means not allocated
} Inode_t;


typedef struct __Bit_Map_t{
	bool bits[MFS_BLOCK_NUMS];
} Bit_Map_t;

typedef struct __Block_t{
	char data[MFS_BLOCK_SIZE];
} Block_t;

int Image_Init(char * filename);

//initialize, should just be an empty function
//Note that this function just corresponds to MFS_Init
//the initialization of file system image is done in function Image_Init()
int Server_Init();

//takes the parent inode number and looks up the entry name in it
//Return Value: inode number of name on sucess, -2 if invalid pinum, -3 if name doesn't exist in pinum
int Server_LookUp(int pinum, char *name);

//returns some infomation obout the file specified by inum
//Return value: 0 on success, -2 if inum doesn't exit
int Server_Stat(int inum, MFS_Stat_t *m);

//writes a block of size 4096 bytes at the block offset specified by block
//Return Value: 0 on sucess, -2 if invalid inum, -3 if invalid block, -4 if not a regular file 
int Server_Write(int inum, char *buffer, int block);


//reads a block specified by block into the buffer from the file specified by inum
//Return Value: 0 on success, -2 if invalid inum, -3 if invalid block
int Server_Read(int inum, char *buffer, int block);

//create a file or directory in the parent directory specified by 'pinum' of name 'name'
//Return value: 0 on sucess, -2 if pinum does not exist
int Server_Creat(int pinum, int type, char *name);

//removes the file or directory 'name' from the directory specified by pinum.
//Return value: 0 on success, -2 if pinum does not exist, -3 if directoy is not empty
int Server_Unlink(int pinum, char *name);

#endif 



