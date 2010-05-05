#include <stdio.h>
#include <sys/select.h>
#include "mfs.h"
#include "udp.h"
#include "mssg.h"

int msg_len[NUM_MESSAGES];
void * data[NUM_MESSAGES];

int port = -1;                  // port number
int sd = -1;                    // socket descriptor
struct sockaddr_in addr, addr2;

/*
int main(int argc, char *argv[])
{
    int sd = UDP_Open(20000);
    assert(sd > -1);

    struct sockaddr_in addr, addr2;
    char machine_name[] = "mumble-06.cs.wisc.edu";
    int rc = UDP_FillSockAddr(&addr, machine_name, 10000);
    assert(rc == 0);
    printf("filled sock addr\n");

    char message[BUFFER_SIZE];

    rc = UDP_Write(sd, &addr, message, BUFFER_SIZE);
    printf("CLIENT:: sent message (%d)\n", rc);
    if (rc > 0) {
        int rc = UDP_Read(sd, &addr2, buffer, BUFFER_SIZE);
        printf("CLIENT:: read %d bytes (message: '%s')\n", rc, buffer);
    }

    return 0;
}
*/

int ClientSendBuffer( char * buffer ) { 
    int rc = UDP_Write(sd, &addr, buffer, UDP_BUFFER_SIZE);
    return rc;
}

int ClientReadBuffer( char * buffer ) {
    int rc = UDP_Read(sd, &addr2, buffer, UDP_BUFFER_SIZE);
    return rc;
}


/*
int SendMessage( char * buffer ) { 

    int rc = UDP_Write(sd, &addr, buffer, UDP_BUFFER_SIZE);
    printf("CLIENT:: sent message (%d)\n", rc);
    if (rc > 0) {
        int rc = UDP_Read(sd, &addr2, buffer, BUFFER_SIZE);
        printf("CLIENT:: read %d bytes (message: '%s')\n", rc, buffer);
    }
    return 0;

}
*/

// Takes a host name and port number and uses those to find the server 
// exporting the file system.  (Return status?)
int MFS_Init(char *hostname, int port) {

    sd = UDP_Open(22107);
    if( sd < 0 ) { return -1; }
//  assert(sd > -1);

    int rc = UDP_FillSockAddr(&addr, hostname, port);
//  if( rc != 0 ) { return -1; }
    assert(rc == 0);

    InitData( msg_len, data);

    char buffer_read[UDP_BUFFER_SIZE];   // buffer used for reading messages
    char buffer_write[UDP_BUFFER_SIZE];   // buffer used for writing messages
    Params params;

    // save all the necessary parameters
    Params *p = &params;
    ResetParams( p );
    p->func_num = 0;

    // create and send the message
    ClientCreatMessage( p, msg_len, data, buffer_write );
    ClientSendBuffer( buffer_write );

    // read the response
    Params read_params;
    Params * r = &read_params;
    ClientReadBuffer( buffer_read );
    ClientReadMessage( r, msg_len, data, buffer_read );
    return r->status;
}

// MFS_Lookup() takes the parent inode number (which should be the inode number
// of a directory) and looks up the entry name in it. The inode number of name
// is returned. Success: return inode number of name; failure: return -1.
// Failure modes: invalid pinum, name does not exist in pinum.
int MFS_Lookup(int pinum, char *name) {

    char buffer_read[UDP_BUFFER_SIZE];   // buffer used for reading messages
    char buffer_write[UDP_BUFFER_SIZE];   // buffer used for writing messages
    Params params;

    // save all the necessary parameters
    Params *p = &params;
    ResetParams( p );
    p->func_num = 1;
    p->pinum    = pinum;
    strncpy( p->name, name, BUFFER_SIZE );

    // create and send the message
    ClientCreatMessage( p, msg_len, data, buffer_write );
retry_lookup:
    ClientSendBuffer( buffer_write );

    // read the response
    Params read_params;
    Params * r = &read_params;
    if( ClientReadBuffer( buffer_read ) == TIME_OUT ){
	    goto retry_lookup;
    }
    ClientReadMessage( r, msg_len, data, buffer_read );
    int inum = r->inum;
    if( inum < 0 ) {
        return -1;
    }

    return inum;
}

// MFS_Stat() returns some information about the file specified by inum. Upon
// success, return 0, otherwise -1. The exact info returned is defined by
// MFS_Stat_t. Failure modes: inum does not exist.
int MFS_Stat(int inum, MFS_Stat_t *m) {

    char buffer_read[UDP_BUFFER_SIZE];   // buffer used for reading messages
    char buffer_write[UDP_BUFFER_SIZE];   // buffer used for writing messages
    Params params;

    Params *p = &params;
    ResetParams( p );
    p->func_num = 2;
    p->inum     = inum;
    // create and send the message
    ClientCreatMessage( p, msg_len, data, buffer_write );
retry_stat:
    ClientSendBuffer( buffer_write );

    // read the response
    Params read_params;
    Params * r = &read_params;
    if( ClientReadBuffer( buffer_read ) == TIME_OUT ){
	    goto retry_stat;
    }
    ClientReadMessage( r, msg_len, data, buffer_read );
    if( r->status != 0 ) {
        return -1;
    }
    m->type = r->type;
    m->size = r->size;
    m->blocks = r->blocks;

    return 0;

}



// MFS_Write() writes a block of size 4096 bytes at the block offset specified
// by block . Returns 0 on success, -1 on failure. Failure modes: invalid inum,
// invalid block, not a regular file (you can't write to directories).
int MFS_Write(int inum, char *buffer, int block) {

    char buffer_read[UDP_BUFFER_SIZE];   // buffer used for reading messages
    char buffer_write[UDP_BUFFER_SIZE];   // buffer used for writing messages
    Params params;

    Params *p = &params;
    ResetParams( p );
    p->func_num = 3;
    p->inum     = inum;
    p->block    = block;
    memcpy( p->buffer, buffer, BUFFER_SIZE);
    // create and send the message
    ClientCreatMessage( p, msg_len, data, buffer_write );
retry_write:
    ClientSendBuffer( buffer_write );

    // read the response
    Params read_params;
    Params * r = &read_params;
    if( ClientReadBuffer( buffer_read ) == TIME_OUT ){
	    goto retry_write;
    }
    ClientReadMessage( r, msg_len, data, buffer_read );
    if( r->status != 0 ) {
        return -1;
    }
    return r->status;

}

// MFS_Read() reads a block specified by block into the buffer from file
// specified by inum . The routine should work for either a file or directory;
// directories should return data in the format specified by MFS_DirEnt_t.
// Success: 0, failure: -1. Failure modes: invalid inum, invalid block.
int MFS_Read(int inum, char *buffer, int block) {

    char buffer_read[UDP_BUFFER_SIZE];   // buffer used for reading messages
    char buffer_write[UDP_BUFFER_SIZE];   // buffer used for writing messages
    Params params;

    Params *p = &params;
    ResetParams( p );
    p->func_num = 4;
    p->inum     = inum;
    p->block    = block;
    // create and send the message
    ClientCreatMessage( p, msg_len, data, buffer_write );
retry_read:
    ClientSendBuffer( buffer_write );

    // read the response
    Params read_params;
    Params * r = &read_params;
    if( ClientReadBuffer( buffer_read ) == TIME_OUT ){
	    goto retry_read;
    }
    ClientReadMessage( r, msg_len, data, buffer_read );
    if( r->status != 0 ) {
        return -1;
    }

    // copy the buffer out
    memcpy( buffer, r->buffer, BUFFER_SIZE);
    return 0;

}

// MFS_Creat() makes a file ( type == MFS_REGULAR_FILE) or directory ( type ==
// MFS_DIRECTORY) in the parent directory specified by pinum of name name .
// Returns 0 on success, -1 on failure. Failure modes: pinum does not exist. If
// name already exists, return success (think about why).
int MFS_Creat(int pinum, int type, char *name) {

    char buffer_read[UDP_BUFFER_SIZE];   // buffer used for reading messages
    char buffer_write[UDP_BUFFER_SIZE];   // buffer used for writing messages
    Params params;

    Params *p = &params;
    ResetParams( p );
    p->func_num = 5;
    p->type     = type;
    strncpy( p->name, name, BUFFER_SIZE);
    // create and send the message
    ClientCreatMessage( p, msg_len, data, buffer_write );
retry_create:
    ClientSendBuffer( buffer_write );

    // read the response
    Params read_params;
    Params * r = &read_params;
    if( ClientReadBuffer( buffer_read ) == TIME_OUT ){
	    goto retry_create;
    }
    ClientReadMessage( r, msg_len, data, buffer_read );
    if( r->status != 0 ) {
        return -1;
    }

    return r->status;

}

// MFS_Unlink() removes the file or directory name from the directory specified
// by pinum . 0 on success, -1 on failure. Failure modes: pinum does not exist,
// directory is NOT empty. Note that the name not existing is NOT a failure by
// our definition (think about why this might be).
int MFS_Unlink(int pinum, char *name) {

    char buffer_read[UDP_BUFFER_SIZE];   // buffer used for reading messages
    char buffer_write[UDP_BUFFER_SIZE];   // buffer used for writing messages
    Params params;

    Params *p = &params;
    ResetParams( p );
    p->func_num = 6;
    p->pinum     = pinum;
    strncpy( p->name, name, BUFFER_SIZE);
    // create and send the message
    ClientCreatMessage( p, msg_len, data, buffer_write );
retry_unlink:
    ClientSendBuffer( buffer_write );

    // read the response
    Params read_params;
    Params * r = &read_params;
    if( ClientReadBuffer( buffer_read ) == TIME_OUT ){
	    goto retry_unlink;
    }
    ClientReadMessage( r, msg_len, data, buffer_read );
    if( r->status != 0 ) {
        if( r->status == -1) {
            fprintf(stderr, "pinum %d does not exist\n",pinum);
        } else if ( r->status == -2 ) {
            fprintf(stderr, "directory is not empty\n");
        } else {
            fprintf(stderr, "unknown error!  terminating pgm\n");
            exit(1);
        }
        return -1;
    }

    // copy the buffer out
    return 0;

}
