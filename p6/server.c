#include <stdio.h>
#include <unistd.h>
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

int image_fd;

// read message (read from udp)
// parse message
// choose which function to run
// run the function
// create return message (parse response)
// write to udp


/*
 * Main program for running the file server.
 *
 */
int main(int argc, char *argv[])
{

    ///////////////////////// parse the arguments //////////////////////////////
    if(argc != 2){
        printf("usage: server [portnm] [file-system-image]");
        exit(-1);
    }
    int portnum = atoi( argv[1] );
    if( ! (portnum > 0 ) ) {
        fprintf(stderr, "  portnum = %d;  this should be a pos number",portnum);
    }
    char* filename = malloc( sizeof(char) * (1 + strlen(argv[2])) );
    strcpy( filename, argv[2] );

    const int sd = UDP_Open(portnum);
    assert(sd > -1);
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////// main loop ///////////////////////////////////////
    char buffer_read [BUFFER_SIZE];
    char buffer_reply[BUFFER_SIZE];
    int rc = -1;
    struct sockaddr_in s;
    while (1) {

        // read a message //
        rc = UDP_Read(sd, &s, buffer_read, BUFFER_SIZE);
        if (rc > 0) {

            // parse the message into arguments //
            printf("SERVER:: read %d bytes (message: '%s')\n", rc, buffer_read);
            sleep(10);
        } else {  // bad read -- continue waiting for another message ...
            rc = -1;
            continue;
        }

        // call the appropriate function //
        int func_num = 20;
        switch( func_num )
        {   
            // TODO -- fill this in!
            case 0:

            break;
            case 1:

            break;
            case 2:

            break;
            case 3:

            break;
            case 4:

            break;
            case 5:

            break;
            case 6:

            break;
            case 7:

            break;
            default:
            fprintf(stderr, "bad function number %d called \n", func_num );
        }
        

        // parse a response //
        sprintf(buffer_reply, "reply");

        // write the response //
        rc = UDP_Write(sd, &s, buffer_reply, BUFFER_SIZE);

    }
    ///////////////////////////////////////////////////////////////////////////

    return 0;
}


/*
int main(int argc, char *argv[]){
	if(argc != 2){
		printf("usage: server [portnm] [file-system-image]");
		exit(-1);
	}

	//TODO
	//listen to port and other stuff

	return 0;

}
*/

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

	int j;
	for(j = 2; j < MFS_BLOCK_SIZE / sizeof(MFS_DirEnt_t); j ++){
		(root_dot + j) -> inum = -1;
	}

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

//empty function for Server_Init
int Server_Init(){
	return 0;
}

int Server_LookUp(int pinum, char *name){

	int idx;

	if(lseek(image_fd,0,SEEK_SET) != 0){
		fprintf(stderr,"lseek error\n");
		exit(-1);
	}

	Bit_Map_t Inode_BitMap;
	Bit_Map_t Data_BitMap;
	Inode_t inode_table[MFS_BLOCK_NUMS];
	Block_t data_region[MFS_BLOCK_NUMS];

	if(read(image_fd, &Inode_BitMap, sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd, &Data_BitMap,sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd,inode_table, MFS_BLOCK_NUMS*sizeof(Inode_t)) != MFS_BLOCK_NUMS*sizeof(Inode_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd,data_region, MFS_BLOCK_NUMS*sizeof(Block_t)) != MFS_BLOCK_NUMS*sizeof(Block_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	//return -2 if invalid pinum
	if(Inode_BitMap.bits[pinum] == false){
		return -2;
	}else if(inode_table[pinum].type != MFS_DIRECTORY){
		return -2;
	}

	int curr_blk_num;
	for(idx = 0; idx < MFS_PTR_NUMS; idx++){
		if((curr_blk_num = inode_table[pinum].ptr[idx]) == -1){
			continue;
		}

	//	int entries_in_curr_blk = (inode_table[pinum].size / MFS_BLOCK_SIZE > idx) ? MFS_BLOCK_SIZE / sizeof(MFS_DirEnt_t) : (inode_table[pinum].size % MFS_BLOCK_SIZE) / sizeof(MFS_DirEnt_t);
		
		int entries_in_curr_blk = MFS_BLOCK_SIZE / sizeof(MFS_DirEnt_t);

		MFS_DirEnt_t *entries = (MFS_DirEnt_t *)data_region[curr_blk_num].data;
		int j; 
		for (j = 0; j < entries_in_curr_blk; j++){
			if(entries[j].inum == -1){
				continue;
			}
			if(strcmp(entries[j].name, name) == 0){
				return entries[j].inum;
			}
		}

	}

	//return -3 if name doesn't exist in pinum
	return -3;
}
	





int Server_Stat(int inum, MFS_Stat_t *m){

	if(lseek(image_fd,0,SEEK_SET) != 0){
		fprintf(stderr,"lseek error\n");
		exit(-1);
	}

	Bit_Map_t Inode_BitMap;
	Bit_Map_t Data_BitMap;
	Inode_t inode_table[MFS_BLOCK_NUMS];
	Block_t data_region[MFS_BLOCK_NUMS];

	if(read(image_fd, &Inode_BitMap, sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd, &Data_BitMap,sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd,inode_table, MFS_BLOCK_NUMS*sizeof(Inode_t)) != MFS_BLOCK_NUMS*sizeof(Inode_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd,data_region, MFS_BLOCK_NUMS*sizeof(Block_t)) != MFS_BLOCK_NUMS*sizeof(Block_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}


	//return -2 if inum doesn't exit
	if(Inode_BitMap.bits[inum] == false){
		return -2;
	}

	m -> type = inode_table[inum].type;
	m -> size = inode_table[inum].size;
	m -> blocks = inode_table[inum].blocks;

	return 0;
}

int  Server_Write(int inum, char * buffer, int block){

	if(lseek(image_fd,0,SEEK_SET) != 0){
		fprintf(stderr,"lseek error\n");
		exit(-1);
	}

	Bit_Map_t Inode_BitMap;
	Bit_Map_t Data_BitMap;
	Inode_t inode_table[MFS_BLOCK_NUMS];
	Block_t data_region[MFS_BLOCK_NUMS];

	if(read(image_fd, &Inode_BitMap, sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd, &Data_BitMap,sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd,inode_table, MFS_BLOCK_NUMS*sizeof(Inode_t)) != MFS_BLOCK_NUMS*sizeof(Inode_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd,data_region, MFS_BLOCK_NUMS*sizeof(Block_t)) != MFS_BLOCK_NUMS*sizeof(Block_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}


	//return -2 if invalid inum
	if(Inode_BitMap.bits[inum] == false){
		return -2;
	}

	//return -4 if not a regular file
	if(inode_table[inum].type != MFS_REGULAR_FILE){
		return -4;
	}

	//return -3 if invaid block 
	if(block < 0 || block > 9){
		return -3;
	}

	
	int to_write_block;
	if(inode_table[inum].ptr[block] == -1){// allocate a new data block
		to_write_block = First_Empty(&Data_BitMap);
		Set_Bit(&Data_BitMap,to_write_block);
		inode_table[inum].blocks ++;
		inode_table[inum].ptr[block] = to_write_block;
		inode_table[inum].size += MFS_BLOCK_SIZE; // should I and MFS_BLOCK_SIZE of should I add the actual size in buf? yangsuli 
	}else{//overwrite existing data block
		to_write_block = inode_table[inum].ptr[block];
	}


	int i;
	for(i = 0; i < MFS_BLOCK_SIZE; i++){
		data_region[to_write_block].data[i] = buffer[i];
	}


	if(lseek(image_fd,0,SEEK_SET) != 0){
		fprintf(stderr,"lseek error\n");
		exit(-1);
	}

	if(write(image_fd, &Inode_BitMap, sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr, "write error!\n");
		exit(-1);
	}

	if(write(image_fd,&Data_BitMap, sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"write error!\n");
		exit(-1);
	}

	if(write(image_fd,inode_table, MFS_BLOCK_NUMS*sizeof(Inode_t)) != MFS_BLOCK_NUMS*sizeof(Inode_t)){
		fprintf(stderr,"write error!\n");
		exit(-1);
	}


	if(write(image_fd,data_region, MFS_BLOCK_NUMS*sizeof(Block_t)) != MFS_BLOCK_NUMS*sizeof(Block_t)){
		fprintf(stderr,"write error\n");
		exit(-1);
	}

	fsync(image_fd);

	return 0;
}

int Server_Read(int inum, char *buffer, int block){
	
	if(lseek(image_fd,0,SEEK_SET) != 0){
		fprintf(stderr,"lseek error\n");
		exit(-1);
	}

	Bit_Map_t Inode_BitMap;
	Bit_Map_t Data_BitMap;
	Inode_t inode_table[MFS_BLOCK_NUMS];
	Block_t data_region[MFS_BLOCK_NUMS];

	if(read(image_fd, &Inode_BitMap, sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd, &Data_BitMap,sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd,inode_table, MFS_BLOCK_NUMS*sizeof(Inode_t)) != MFS_BLOCK_NUMS*sizeof(Inode_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd,data_region, MFS_BLOCK_NUMS*sizeof(Block_t)) != MFS_BLOCK_NUMS*sizeof(Block_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}


	//return -2 if invalid inum
	if(Inode_BitMap.bits[inum] == false){
		return -2;
	}


	//return -3 if invalid block
	if(block < 0 || block > 9){
		return -3;
	}else if(inode_table[inum].ptr[block] == -1){
		return -3;
	}


	int to_read_block = inode_table[inum].ptr[block];

	int j;
	for(j = 0; j < MFS_BLOCK_SIZE; j++){
		buffer[j] = data_region[to_read_block].data[j];
	}

	return 0;

}


int Server_Creat(int pinum, int type, char *name){

	if(lseek(image_fd,0,SEEK_SET) != 0){
		fprintf(stderr,"lseek error\n");
		exit(-1);
	}

	Bit_Map_t Inode_BitMap;
	Bit_Map_t Data_BitMap;
	Inode_t inode_table[MFS_BLOCK_NUMS];
	Block_t data_region[MFS_BLOCK_NUMS];

	if(read(image_fd, &Inode_BitMap, sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd, &Data_BitMap,sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd,inode_table, MFS_BLOCK_NUMS*sizeof(Inode_t)) != MFS_BLOCK_NUMS*sizeof(Inode_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd,data_region, MFS_BLOCK_NUMS*sizeof(Block_t)) != MFS_BLOCK_NUMS*sizeof(Block_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	//return -2 if pinum doesn't exit or not a directory
	if(Inode_BitMap.bits[pinum] == false || inode_table[pinum].type == MFS_DIRECTORY){
		return -2;
	}

	if(Server_LookUp(pinum,name) >= 0){//name already exists
	//how about name exists but types doesn't agree? yangsuli
		return 0;
	}

	int inum = First_Empty(&Inode_BitMap);
	Set_Bit(&Inode_BitMap, inum);

	if(Add_Entry(pinum, inum, name, inode_table, data_region) != 0){
		fprintf(stderr,"add entry error!\n");
	}

	if(type == MFS_REGULAR_FILE){
		inode_table[inum].type = type;
		inode_table[inum].size = 0;
		inode_table[inum].blocks = 0;
		int i;
		for(i = 0; i < MFS_PTR_NUMS; i++){
			inode_table[inum].ptr[i] = -1;
		}
	}

	if(type == MFS_DIRECTORY){
		int to_write_block = First_Empty(&Data_BitMap);
		Set_Bit(&Data_BitMap,to_write_block);
		inode_table[inum].type = type;
		inode_table[inum].size = 2 * sizeof(MFS_DirEnt_t);
		inode_table[inum].blocks = 1;
		inode_table[inum].ptr[0] = to_write_block;
		int i;
		for(i = 1; i < MFS_PTR_NUMS; i++){
			inode_table[inum].ptr[i] = -1;
		}

		MFS_DirEnt_t * entries = (MFS_DirEnt_t *) data_region[to_write_block].data;

		entries[0].inum = inum;
		strcpy(entries[0].name, ".");
		entries[1].inum = pinum;
		strcpy(entries[1].name, "..");
		
		for(i = 2; i < MFS_BLOCK_SIZE / sizeof(MFS_DirEnt_t); i++){
			entries[i].inum = -1;
		}
	}


	if(lseek(image_fd,0,SEEK_SET) != 0){
		fprintf(stderr,"lseek error\n");
		exit(-1);
	}

	if(write(image_fd, &Inode_BitMap, sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr, "write error!\n");
		exit(-1);
	}

	if(write(image_fd,&Data_BitMap, sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"write error!\n");
		exit(-1);
	}

	if(write(image_fd,inode_table, MFS_BLOCK_NUMS*sizeof(Inode_t)) != MFS_BLOCK_NUMS*sizeof(Inode_t)){
		fprintf(stderr,"write error!\n");
		exit(-1);
	}


	if(write(image_fd,data_region, MFS_BLOCK_NUMS*sizeof(Block_t)) != MFS_BLOCK_NUMS*sizeof(Block_t)){
		fprintf(stderr,"write error\n");
		exit(-1);
	}

	fsync(image_fd);

	return 0;
}


int Add_Entry(int pinum, int inum, char *name, Inode_t *inode_table, Block_t *data_region){
	int idx1, idx2;
	int curr_blk_num;
	bool insert = false;
	for(idx1 = 0; idx1 < MFS_PTR_NUMS; idx1 ++){
		if(inode_table[pinum].ptr[idx1] == -1){
			continue;
		}
		curr_blk_num = inode_table[pinum].ptr[idx1];

		MFS_DirEnt_t *entries = (MFS_DirEnt_t *)data_region[curr_blk_num].data;
		for(idx2 = 0; idx2 < MFS_BLOCK_SIZE / sizeof(MFS_DirEnt_t); idx2 ++){
			if(entries[idx2].inum == -1){
				entries[idx2].inum = inum;
				strcpy(entries[idx2].name, name);
				insert = true;
				break;
			}
		}

		if(insert == true){
			break;
		}
	}

	if(insert == false){//one has to allocate a new block and such things
		//TODO
	}

	inode_table[pinum].size += sizeof(MFS_DirEnt_t);

	return 0;
}

			

int Server_Unlink(int pinum, char *name){
	
	if(lseek(image_fd,0,SEEK_SET) != 0){
		fprintf(stderr,"lseek error\n");
		exit(-1);
	}

	Bit_Map_t Inode_BitMap;
	Bit_Map_t Data_BitMap;
	Inode_t inode_table[MFS_BLOCK_NUMS];
	Block_t data_region[MFS_BLOCK_NUMS];

	if(read(image_fd, &Inode_BitMap, sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd, &Data_BitMap,sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd,inode_table, MFS_BLOCK_NUMS*sizeof(Inode_t)) != MFS_BLOCK_NUMS*sizeof(Inode_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	if(read(image_fd,data_region, MFS_BLOCK_NUMS*sizeof(Block_t)) != MFS_BLOCK_NUMS*sizeof(Block_t)){
		fprintf(stderr,"read error!\n");
		exit(-1);
	}

	//return -2 if pinum doesn't exist
	if(Inode_BitMap.bits[pinum] == false){
		return -2;
	}

	int inum = Server_LookUp(pinum, name);
	if(inum < 0){//name does not exist
		return 0;
	}

	int i;
	for(i = 0; i < MFS_PTR_NUMS; i++){
		if(inode_table[inum].ptr[i] != -1){
			Unset_Bit(&Data_BitMap, inode_table[inum].ptr[i]);
		}
	}
	Unset_Bit(&Inode_BitMap, inum);

	Remove_Entry(pinum, inum, name, inode_table, data_region);
	

	if(lseek(image_fd,0,SEEK_SET) != 0){
		fprintf(stderr,"lseek error\n");
		exit(-1);
	}

	if(write(image_fd, &Inode_BitMap, sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr, "write error!\n");
		exit(-1);
	}

	if(write(image_fd,&Data_BitMap, sizeof(Bit_Map_t)) != sizeof(Bit_Map_t)){
		fprintf(stderr,"write error!\n");
		exit(-1);
	}

	if(write(image_fd,inode_table, MFS_BLOCK_NUMS*sizeof(Inode_t)) != MFS_BLOCK_NUMS*sizeof(Inode_t)){
		fprintf(stderr,"write error!\n");
		exit(-1);
	}


	if(write(image_fd,data_region, MFS_BLOCK_NUMS*sizeof(Block_t)) != MFS_BLOCK_NUMS*sizeof(Block_t)){
		fprintf(stderr,"write error\n");
		exit(-1);
	}

	fsync(image_fd);

	return 0;
}
	


int Remove_Entry(int pinum, int inum, char *name, Inode_t *inode_table, Block_t *data_region){

	int idx1, idx2;
	int curr_blk_num;
	bool found = false;
	for(idx1 = 0; idx1 < MFS_PTR_NUMS; idx1 ++){
		if(inode_table[pinum].ptr[idx1] == -1){
			continue;
		}
		curr_blk_num = inode_table[pinum].ptr[idx1];

		MFS_DirEnt_t *entries = (MFS_DirEnt_t *)data_region[curr_blk_num].data;
		for(idx2 = 0; idx2 < MFS_BLOCK_SIZE / sizeof(MFS_DirEnt_t); idx2 ++){
			if(entries[idx2].inum == inum && strcmp(entries[idx2].name, name) == 0){
				entries[idx2].inum = -1;
				found = true;
				break;
			}
		}

		if(found == true){
			break;
		}
	}

	if(found == false){//error here
		//TODO
	}

	inode_table[pinum].size -= sizeof(MFS_DirEnt_t);

	return 0;
}


