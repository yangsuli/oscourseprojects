#include <stdlib.h>
#include <assert.h>
#include <string.h>  // needed for memcpy
#include "mssg.h"

// Create a message of type "type" and write out to buffer
void CreateMessage( int type, int msg_len[], 
    void * data[], char * buffer)
{

    // write out all the header information
    int * header = (int *) buffer;
    *header = type;
    header++;
    int i = 0;
    for( i = 0; i < NUM_MESSAGES; i++ ) {
        *header = msg_len[i];
        header++;
    }
    
    // write out all the data
    void * data_ptr = (void*) header;
    for( i = 0; i < NUM_MESSAGES; i++ ) {
        if( msg_len[i] > 0 ) {
            memcpy( data_ptr, data[i], msg_len[i] );
            data_ptr += msg_len[i];
        }
    }

}

// Read a message from buffer, and write to type, msg_len and data.
void ReadMessage( int * type, int msg_len[], 
    void * data[], const char * buffer)
{

    // read all the header information (sizes and message type)
    int * header = (int *) buffer;
    *type = *header;
    header++;
    int i = 0;
    for( i = 0; i < NUM_MESSAGES; i++ ) {
        msg_len[i] = *header;
        header++;
    }
    
    // read all the data -- save into buffers pointed to by (void*) data[]
    void * data_ptr = (void*) header;
    for( i = 0; i < NUM_MESSAGES; i++ ) {
        if( msg_len[i] > 0 ) {
            memcpy( data[i], data_ptr, msg_len[i] );
            data_ptr += msg_len[i];
        }
    }

}

/*
MFS_INIT: client send string '0', return 0 if hearing response, and -1 otherwise. 
          server send back 'alive'

MFS_Lookup: client send '1', 'pinum', name (3 strings in total) 
            server: 'inode_num' on success, '-2' if invalid pinum, '-3' if name does exist.  

MFS_Stat: client send '2' 'inum' (2 strings in total)
          server send '0'  'type' 'size' 'blocks' on sucess (4 strings in total, and ordering is important)
                 or send '-1' on failure (inum doesn't exist)

MFS_Write: client send '3' 'inum' buffer 'block' (4 strings in total)
           server send '0' on sucess,  '-2' if invalid inum, '-3' if invalid block, and '-4' if not a regular file

MFS_Read: client send '4' 'inum', 'block' (3 strings in total)
          server send '-1' on failure
                      '0' 'file/directory' in case of file, data as a string; in case of directory, unspecified yet.

MFS_Creat: client send '5' 'type' name (3 strings in total)
           server send '0' on success, '-2' pinum doesn't

MFS_Unlink: client send '6' 'pinum' name (3 strings in total)
            server send '0' on success or '-1' for pinum does not exist
            or '-2' if the directory is not empty.

Every communication from client to server or server to client will look like the
following:

    ---------------------------------------
    |  Header  |   Data                    |
    ----------------------------------------

Where the Header has the following format:

    ---------------------------------------------------------------
    |  Num_args  | arg1_size  | arg2_size | arg3_size | arg4_size |
    ---------------------------------------------------------------

and Data has the following format

    ---------------------------------------------------------------
    |  arg1  | arg2 | ...                                         |
    ---------------------------------------------------------------
*/
