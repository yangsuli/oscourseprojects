#ifndef __MSSG_H
#define __MSSG_H

#define UDP_BUFFER_SIZE (16384)
#define BUFFER_SIZE (4096)
#define NUM_MESSAGES (5)

// singleton struct used for passing parameters around -- Note: the number of
// these parameters that get used depends of message_type -- see table below
typedef struct __params {
    int func_num;
    char name[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    int pinum;
    int inum;
    int size;
    int block;
    int message_type;
    int status;
} Params;

// TODO -- why can't these have const in front of them?
//void CreateMessage( int type, const int msg_len[], 
//    const void * data[], char * buffer);
int CreateMessage( int type, int fun_number, int msg_len[], 
    void * data[], char * buffer);

void ReadMessage( int * type, int * fun_number, int msg_len[], 
    void * data[], const char * buffer); 

// initializes each entry in msg_len to zero and allocates memory for each
// entry in data[]
int InitData( int msg_len[], void * data[], Params *p);
void ResetParams( Params *p );

int ServerCreatMessage(Params *p,int msg_len[],void * data[],char * buffer);
int ClientCreatMessage(Params *p,int msg_len[],void * data[],char * buffer);

// the format of these routines follows (int func_num, Params ) where Params
// can be anything of any length

/*
MFS_INIT (func_num == 0) : 
    client send ( )
    server send (int status) 
        where status == 0 if hearing response,
        otherwise status == -1

MFS_Lookup (func_num == 1): 
    client send (int pinum, char *name)
    server: (int inum)
        if invalid pinum, '-3' if name does exist.

MFS_Stat (func_num == 2): 
    client send (int inum)
    server send (int status, TODO type, int size, void * blocks)
        '0'  'type' 'size' 'blocks' on sucess (4 strings in total, and ordering is important)
        status == -1 on failure or inum doesn't exist

MFS_Write (func_num == 3): 
    client send (int inum, char * buffer, int block )
    server send (int status)
           status == 0 on sucess,  '-2' if invalid inum, '-3' if invalid block, and '-4' if not a regular file

MFS_Read (func_num == 4): 
    client send (int inum, int block)
    server send (int status, char * buffer).
        status == '-1' on failure owise
        status == '0' on success.
        buffer =='file/directory' in case of file, data as a string; in case of directory, unspecified yet.

// TODO -- why doesn't this send pinum ??
    "new version"
MFS_Creat (func_num == 5): 
    client send (int type, char *name)
    server send (int status)
           status == 0 on success, otherwise == -2 if ss, '-2' pinum doesn't

////// "old version"
////// MFS_Creat: client send '5' 'type' name (3 strings in total)
//////           server send '0' on success, '-2' pinum doesn't

MFS_Unlink (func_num == 6): 
    client send (int pinum, char *name)
    server send (int status)
        status == '0' on success or '-1' for pinum does not exist
        or '-2' if the directory is not empty.

*/
#endif