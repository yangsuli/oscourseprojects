#include <stdio.h>
#include <string.h>
#include "udp.h"
#include "mfs.h"
#include <fcntl.h>
#include "server.h"

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

void Set_Bit(Bit_Map_t *map, int index){
	if(index < 0 || index >= MFS_BLOCK_NUMS){
		fprintf(stderr, "index error!\n");
		exit(-1);
	}
	map->bits[index] = true;
}

void Unset_Bit(Bit_Map_t *map, int index){
	if(index < 0 || index >= MFS_BLOCK_NUMS){
		fprintf(stderr, "index error!\n");
		exit(-1);
	}
	map->bits[index] = false;
}


int First_Empty(Bit_Map_t *map){
	int index;
	for(index = 0; index < MFS_BLOCK_NUMS; index++){
		if(map->bits[index] == false){
			break;
		}
	}

	if(index == MFS_BLOCK_NUMS){
		index = -1;
	}

	return index;
}

void BitMap_Init(Bit_Map_t *map){
	int idx;
	for (idx = 0; idx < MFS_BLOCK_NUMS; idx ++){
		map->bits[idx] = false;
	}
}

void Inode_Init(Inode_t *inode){
	inode->type = MFS_REGULAR_FILE;
	inode->size = 0;
	inode->blocks = 0;
	int i;
	for(i = 0; i < MFS_PTR_NUMS; i++){
		inode->ptr[i] = -1;
	}
}



//return the file descriptor of the image file
int Image_Init(char * filename){
	int fd, i;
	if((fd = open(filename,O_WRONLY|O_CREAT|O_TRUNC)) == -1){
		fprintf(stderr,"open failed!\n");
		exit(-1);
	}

	Bit_Map_t Inode_BitMap;
	Bit_Map_t Data_BitMap;

	BitMap_Init(&Inode_BitMap);
	BitMap_Init(&Data_BitMap);

	Inode_t inode_table[MFS_BLOCK_NUMS];

	for(i = 0; i < MFS_BLOCK_NUMS; i++){
		Inode_Init(&inode_table[i]);
	}

	Block_t data_region[MFS_BLOCK_NUMS];

	//initialize root directory
        //root dir uses data block 0	
	inode_table[0].type = MFS_DIRECTORY;
	inode_table[0].size = 2 * sizeof(MFS_DirEnt_t);
	inode_table[0].blocks = 1;
	inode_table[0].ptr[0] = 0;

	MFS_DirEnt_t *root_dot = (MFS_DirEnt_t *)data_region[0].data;
	MFS_DirEnt_t *root_dotdot = root_dot + 1;

	root_dot -> inum = 0;
	strcpy(root_dot -> name,".");

	root_dotdot -> inum = 0;
	strcpy(root_dotdot -> name, "..");

	Set_Bit(&Inode_BitMap, 0);
	Set_Bit(&Data_BitMap,0);


	if(write(fd, &Inode_BitMap, sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr, "write error!\n");
		exit(-1);
	}

	if(write(fd,&Data_BitMap, sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"write error!\n");
		exit(-1);
	}

	if(write(fd,inode_table, MFS_BLOCK_NUMS*sizeof(Inode_t)) != MFS_BLOCK_NUMS*sizeof(Inode_t)){
		fprintf(stderr,"write error!\n");
		exit(-1);
	}


	if(write(fd,data_region, MFS_BLOCK_NUMS*sizeof(Block_t)) != MFS_BLOCK_NUMS*sizeof(Block_t)){
		fprintf(stderr,"write error\n");
		exit(-1);
	}

	fsync(fd);

	return fd;

}


