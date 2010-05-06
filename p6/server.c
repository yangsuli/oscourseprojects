#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "udp.h"
#include "mfs.h"
#include "mssg.h"
#include "server.h"

int image_fd;
Bit_Map_t Inode_BitMap;
Bit_Map_t Data_BitMap;
Inode_t *inode_table;
Block_t *data_region;

/*
 * Main program for running the file server.
 */
int main(int argc, char *argv[])
{

	///////////////////////// parse the arguments //////////////////////////////
	if(argc != 3){
		fprintf(stderr,"usage: server [portnum] [file-system-image]\n");
		fprintf(stderr,"you supplied %d args\n", argc);
		exit(1);
	}
	int portnum = atoi( argv[1] );
	if( ! (portnum > 0 ) ) {
		fprintf(stderr, "  portnum = %d;  this should be a pos number",portnum);
	}

	const int sd = UDP_Open(portnum);
	assert(sd > -1);

	inode_table = (Inode_t *)malloc(MFS_BLOCK_NUMS * sizeof(Inode_t));
	data_region = (Block_t *)malloc(MFS_BLOCK_NUMS * sizeof(Block_t));
	if(inode_table == NULL || data_region == NULL){
		fprintf(stderr, "malloc error!\n");
		exit(-1);
	}

	//open file image
	if( (image_fd = open(argv[2],O_RDWR)) == -1){
		image_fd = Image_Init(argv[2]);
	}
	///////////////////////////////////////////////////////////////////////////

	///////////////////////// main loop ///////////////////////////////////////
	int rc = -1;
	struct sockaddr_in s;
	char buffer_read[ UDP_BUFFER_SIZE];
	char buffer_reply[UDP_BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	char * ptr = buffer_read;

	// every possible parameter that could be used
	int block  = -1;       // block number
	int blocks = -1;       // number of blocks allocated to inum
	int pinum  = -1;       // parent inode number
	int inum   = -1;       // inode number
	int size   = -1;
	int status = -1;       // return status for server
	int type   = -1;       // either MFS_DIRECTORY or MFS_REGULAR_FILE
	char * name   = NULL;  // name of file/directory

	// these are helper pointers to make code more readable
	int * i_ptr   = NULL;  // helper pointer
	char * c_ptr  = NULL;  // helper pointer
	MFS_Stat_t * m_ptr  = NULL;  // helper pointer

	while (1) {

		// every possible parameter that could be used
		block  = -1;    // block number
		blocks = -1;    // number of blocks allocated to inum
		pinum  = -1;    // parent inode number
		inum   = -1;    // inode number
		size   = -1;
		status = -1;    // return status for server
		type   = -1;    // either MFS_DIRECTORY or MFS_REGULAR_FILE
		name   = NULL;  // name of file/directory
		i_ptr  = NULL;  // helper pointer
		c_ptr  = NULL;  // helper pointer

		// read a message //
		rc = UDP_Read(sd, &s, buffer_read, UDP_BUFFER_SIZE);
		ptr = buffer_read;
		if (rc < 1) {
			// bad read -- continue waiting for another message ...
			rc = -1;
			continue;
		}

		// call the appropriate function //
		i_ptr = (int*) ptr;
		int * func_num = i_ptr;
		i_ptr++;
		switch( *func_num )
		{   
			// TODO -- fill this in!
			case 0:
				// since this is an empty function, why call it?
				//                Server_Init(); 
				printf("  func_num == 0 \n");
				break;

			case 1: 

				// parse the args passed in for this function
				pinum = *( i_ptr );
				i_ptr++;
				c_ptr = (char*)i_ptr;
				name = c_ptr;

#ifdef MSSG_DEBUG
				printf("Server read arguments in func_num %d:\n", *func_num);
				printf("    pinum = %d;", pinum);
				printf("    name = %s;", name);
				printf("\n");
#endif

				// call the function
				inum = Server_LookUp(pinum, name );

				// parse a response
				i_ptr = (int*) buffer_reply;
				*i_ptr = inum;

#ifdef MSSG_DEBUG
				printf(
						"Server is Sending func_num %d response with parameters:\n",
						*func_num);
				printf("    inum = %d", inum);
				printf("\n");
#endif


				break;


			case 2:

				// parse the args passed in for this function
				inum = *( i_ptr );
				i_ptr++;
				m_ptr = (MFS_Stat_t*)i_ptr;

#ifdef MSSG_DEBUG
				MFS_Stat_t * m = m_ptr;
				printf("Server read arguments in func_num %d:\n", *func_num);
				printf("    inum = %d;", inum);
				printf("    m->type = %d;", m->type);
				printf("    m->size = %d;", m->size);
				printf("    m->blocks = %d;", m->blocks);
				printf("\n");
#endif

				// call the function
				status = Server_Stat(inum, m_ptr );

				// parse a response
				i_ptr = (int*) buffer_reply;
				*i_ptr = status;
				//              if( status == 0 ) { 
				//                  // only need to pass m_ptr info if inum exists
				i_ptr++;
				memcpy((void*) i_ptr, (void*)m_ptr, sizeof( MFS_Stat_t ) );
				//              }

#ifdef MSSG_DEBUG
				m = (MFS_Stat_t*) i_ptr;;
				printf(
						"Server is Sending func_num %d response with parameters:\n", *func_num);
				printf("    status = %d; m->type = %d, m->size = %d, m->blocks = %d\n", 
						status, m->type, m->size, m->blocks);
#endif


				break;

			case 3:

				// save inum, buffer, block 
				inum = *( i_ptr );
				i_ptr++;
				c_ptr = (char*)i_ptr;
				memcpy( buffer, c_ptr, BUFFER_SIZE );
				c_ptr += BUFFER_SIZE;
				i_ptr = (int*) c_ptr;
				block = *i_ptr;

#ifdef MSSG_DEBUG
				printf("Server read arguments in func_num %d:\n", *func_num);
				printf("    inum = %d;", inum);
				// WARNING: this might be bad if buffer is not of type char *
				printf("    buffer = %s;", buffer);
				printf("    block = %d;", block);
				printf("\n");
#endif

				status = Server_Write( inum, buffer, block );

				i_ptr = (int *) buffer_reply;
				*i_ptr = status;

#ifdef MSSG_DEBUG
				printf(
						"Server is Sending func_num %d response with parameters:\n",
						*func_num);
				printf("    status = %d", status);
				printf("\n");
#endif

				break;

			case 4:

				// save inum, buffer, block 
				inum = *( i_ptr );
				i_ptr++;
				c_ptr = (char*)i_ptr;
				memcpy( buffer, c_ptr, BUFFER_SIZE );
				c_ptr += BUFFER_SIZE;
				i_ptr = (int*) c_ptr;
				block = *i_ptr;

#ifdef MSSG_DEBUG
				printf("Server read arguments in func_num %d:\n", *func_num);
				printf("    inum = %d;", inum);
				// WARNING: this might be bad if buffer is not of type char *
				printf("    buffer = %s;", buffer);
				printf("    block = %d;", block);
				printf("\n");
#endif

				status = Server_Read( inum, buffer, block );

                // parse a response
				i_ptr = (int *) buffer_reply;
				*i_ptr = status;
                i_ptr++;
                c_ptr = (char*) i_ptr;
                memcpy(c_ptr, buffer, BUFFER_SIZE);

#ifdef MSSG_DEBUG
				printf(
						"Server is Sending func_num %d response with parameters:\n",
						*func_num);
				printf("    status = %d", status);
                printf("    buffer = %s\n", c_ptr);  // NOTE: this may crash if buffer is not type char *
				printf("\n");
#endif


				break;

			case 5:

				// save pinum, type, name
				pinum = *( i_ptr );
				i_ptr++;
				type = *i_ptr;
				i_ptr++;
				name = (char*) i_ptr;

#ifdef MSSG_DEBUG
				printf("Server read arguments in func_num %d:\n", *func_num);
				printf("    pinum = %d;", pinum);
				printf("    type  = %d;", type);
				printf("    name  = %s;", name);
				printf("\n");
#endif

				status = Server_Creat( pinum, type, name );

				i_ptr = (int *) buffer_reply;
				*i_ptr = status;

#ifdef MSSG_DEBUG
				printf(
						"Server is Sending func_num %d response with parameters:\n",
						*func_num);
				printf("    status = %d", status);
				printf("\n");
#endif
				break;

			case 6:

				// save pinum, name
				pinum  = *(i_ptr++);
				name   = (char*)(i_ptr);
#ifdef MSSG_DEBUG
				m = m_ptr;
				printf("Server read arguments in func_num %d:\n", *func_num);
				printf("    pinum = %d;", pinum);
				printf("    name = %s;", name);
				printf("\n");
#endif

				status = Server_Unlink( pinum, name );
				i_ptr  = (int*) buffer_reply;
				*i_ptr = status;

#ifdef MSSG_DEBUG
				printf(
						"Server is Sending func_num %d response with parameters:\n",
						*func_num);
				printf("    status = %d", status);
				printf("\n");
#endif

				break;

			default:
				fprintf(stderr, "bad function number %d called.\n", *func_num );
				fprintf(stderr, "terminating server\n");
				exit(1);
		}

		// write the response //
		rc = UDP_Write(sd, &s, buffer_reply, UDP_BUFFER_SIZE);

	}
	///////////////////////////////////////////////////////////////////////////

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
int Image_Init(const char * filename){
	int fd, i;
	if((fd = open(filename,O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) == -1){
		fprintf(stderr,"open failed!\n");
		exit(-1);
	}

	BitMap_Init(&Inode_BitMap);
	BitMap_Init(&Data_BitMap);

	for(i = 0; i < MFS_BLOCK_NUMS; i++){
		Inode_Init(&inode_table[i]);
	}

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
/*
   int Server_Init(){
   printf("  server_init called -- this function does nothing!\n");
   return 0;
   }
 */

void Data_Init(){

	if(lseek(image_fd,0,SEEK_SET) != 0){
		fprintf(stderr,"lseek error\n");
		exit(-1);
	}

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

}

// TODO -- write what the return value is
int Server_LookUp(int pinum, char *name){

	if(pinum < 0){
		return -1;
	}

	int idx;


	Data_Init();

	//return -2 if invalid pinum
	if(Inode_BitMap.bits[pinum] == false){
		return -1;
	}else if(inode_table[pinum].type != MFS_DIRECTORY){
		return -1;
	}

	int curr_blk_num;
	for(idx = 0; idx < MFS_PTR_NUMS; idx++){
		if((curr_blk_num = inode_table[pinum].ptr[idx]) == -1){
			continue;
		}

		//    int entries_in_curr_blk = (inode_table[pinum].size / MFS_BLOCK_SIZE > idx) ? MFS_BLOCK_SIZE / sizeof(MFS_DirEnt_t) : (inode_table[pinum].size % MFS_BLOCK_SIZE) / sizeof(MFS_DirEnt_t);

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
	return -1;
}

// TODO -- what does this function return?
int Server_Stat(int inum, MFS_Stat_t *m){


	Data_Init();

	//return -2 if inum doesn't exit
	if(Inode_BitMap.bits[inum] == false){
		return -1;
	}

	m -> type = inode_table[inum].type;
	m -> size = inode_table[inum].size;
	m -> blocks = inode_table[inum].blocks;

	return 0;
}

// TODO - what does this function return?
int  Server_Write(int inum, char * buffer, int block){

	int i;
	Data_Init();

	//return -2 if invalid inum
	if(Inode_BitMap.bits[inum] == false){
		return -1;
	}

	//return -4 if not a regular file
	if(inode_table[inum].type != MFS_REGULAR_FILE){
		return -1;
	}

	//return -3 if invaid block 
	if(block < 0 || block > 9){
		return -1;
	}


	int to_write_block;
	if(inode_table[inum].ptr[block] == -1){// allocate a new data block
		to_write_block = First_Empty(&Data_BitMap);
		Set_Bit(&Data_BitMap,to_write_block);
		for(i = 0; i <= inum; i++){
			if(inode_table[inum].ptr[i] == -1){
			inode_table[inum].size += MFS_BLOCK_SIZE; // should I and MFS_BLOCK_SIZE of should I add the actual size in buf? yangsuli 
			inode_table[inum].blocks ++;
			}
		}
		inode_table[inum].ptr[block] = to_write_block;
	}else{//overwrite existing data block
		to_write_block = inode_table[inum].ptr[block];
	}


	for(i = 0; i < MFS_BLOCK_SIZE; i++){
		data_region[to_write_block].data[i] = buffer[i];
	}

	Data_Write();

	return 0;
}

void Data_Write(){

	if(lseek(image_fd,0,SEEK_SET) != 0){
		fprintf(stderr,"lseek error\n");
		exit(-1);
	}

	if(ftruncate(image_fd,0) != 0){
		fprintf(stderr,"truncate error\n");
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

}




// TODO - what does this function return?
int Server_Read(int inum, char *buffer, int block){

	Data_Init();

	//return -2 if invalid inum
	if(Inode_BitMap.bits[inum] == false){
		return -1;
	}


	//return -3 if invalid block
	if(block < 0 || block > 9){
		return -1;
	}else if(inode_table[inum].ptr[block] == -1){
		return -1;
	}


	int to_read_block = inode_table[inum].ptr[block];

	int j;
	for(j = 0; j < MFS_BLOCK_SIZE; j++){
		buffer[j] = data_region[to_read_block].data[j];
	}

	return 0;

}

// TODO -- what is the return type of this function call?
int Server_Creat(int pinum, int type, char *name){



	Data_Init();

	//return -2 if pinum doesn't exit or not a directory
	if(Inode_BitMap.bits[pinum] == false || inode_table[pinum].type != MFS_DIRECTORY){
		return -1;
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

	Data_Write();

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


	Data_Init();

	//return -2 if pinum doesn't exist
	if(Inode_BitMap.bits[pinum] == false){
		return -1;
	}

	int inum = Server_LookUp(pinum, name);
	if(inum < 0){//name does not exist
		return 0;
	}

	//return -3 if directory not empty
	if(inode_table[inum].type == MFS_DIRECTORY){
		if(inode_table[inum].size > 2 * sizeof(MFS_DirEnt_t)){
			return -1;
		}
	}

	int i;
	for(i = 0; i < MFS_PTR_NUMS; i++){
		if(inode_table[inum].ptr[i] != -1){
			Unset_Bit(&Data_BitMap, inode_table[inum].ptr[i]);
		}
	}
	Unset_Bit(&Inode_BitMap, inum);

	Remove_Entry(pinum, inum, name, inode_table, data_region);

	Data_Write();

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
