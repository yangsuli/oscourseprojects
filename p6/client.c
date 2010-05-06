#include <stdio.h>
#include <sys/select.h>
#include "mfs.h"
#include "udp.h"
#include "mssg.h"

int port = -1;                  // port number
int sd   = -1;                    // socket descriptor
struct sockaddr_in addr, addr2;

int MFS_Init_flag = 0;         // 0 means the function has not been called

/*
int ClientSendBuffer( char * buffer ) { 

    int rc = UDP_Write(sd, &addr, buffer, UDP_BUFFER_SIZE);
    return rc;
}

int ClientReadBuffer( char * buffer ) {
    int rc = UDP_Read(sd, &addr2, buffer, UDP_BUFFER_SIZE);
    return rc;
}
*/

// Takes a host name and port number and uses those to find the server 
// exporting the file system.  (Return status?)
int MFS_Init(char *hostname, int port) {

    if( MFS_Init_flag != 0 ) {
        fprintf(stderr, " You called MFS_Init multiple times!\n");
        exit(1);
    }
    MFS_Init_flag = 1;

    int rc = -1;

    // use some random port number here
    sd = UDP_Open(port + 17);
    assert( sd >= 0 );

    rc = UDP_FillSockAddr(&addr, hostname, port);
    if( rc != 0 ) {
        fprintf(stderr, "unable to call UDP_FillSockAddr() correctly\n");
        exit(1);
    }

/////////////// there is no need to send anything ot the server because it does
//NOTHING when func_num 0 is passed to it ///////////////////////////////
/*
    // create the message
    char * buffer_write = malloc( UDP_BUFFER_SIZE ); 
    assert( buffer_write != NULL );
    *( (int*) buffer_write ) = 0;

    // write the message
    rc = TIME_OUT;
    while( rc == TIME_OUT ) {
        rc = UDP_Write(sd, &addr, buffer_write, UDP_BUFFER_SIZE);
    }

    // read the response
    char * buffer_read = malloc( UDP_BUFFER_SIZE );
    assert( buffer_read != NULL );
    rc = TIME_OUT;
    while( rc == TIME_OUT ) {
        rc = Safe_UDP_Read(sd, &addr2, buffer_read, UDP_BUFFER_SIZE);
    }
    int status = *((int*)buffer_read);

    // free buffers
    free( buffer_read );
    free( buffer_write );

    return status;
*/

}

// MFS_Lookup() takes the parent inode number (which should be the inode number
// of a directory) and looks up the entry name in it. The inode number of name
// is returned. Success: return inode number of name; failure: return -1.
// Failure modes: invalid pinum, name does not exist in pinum.
int MFS_Lookup(int pinum, char *name) {

    assert( MFS_Init_flag == 1 );

    int func_num = 1;

    // create the message
    char * buffer_write = malloc( UDP_BUFFER_SIZE ); 
    assert( buffer_write != NULL );
    char * c_ptr = buffer_write;
    int  * i_ptr  = (int*) buffer_write;
    *(i_ptr) = func_num;
    i_ptr++;

    // save other parameters here
    *( i_ptr ) = pinum;
    i_ptr++;
    c_ptr = (char*)i_ptr;
    strncpy( c_ptr, name, BUFFER_SIZE );

    int rc = TIME_OUT;
    char * buffer_read = malloc( UDP_BUFFER_SIZE );
    assert( buffer_read != NULL );
    while( rc == TIME_OUT ) {
        // write the message
        rc = UDP_Write(sd, &addr, buffer_write, UDP_BUFFER_SIZE);

        // read the response
        rc = Safe_UDP_Read(sd, &addr2, buffer_read, UDP_BUFFER_SIZE);
    }

    // free buffers
    free( buffer_read );
    free( buffer_write );

    // parse the response
    i_ptr = (int*) buffer_read;
    int inum = *i_ptr;

#ifdef MSSG_DEBUG
    printf("Client received func_num %d with parameters:\n", func_num);
    printf("    inum = %d\n", inum );
#endif

    if( inum < 0 ){
        return -1;
    }
    return inum;
}

// MFS_Stat() returns some information about the file specified by inum. Upon
// success, return 0, otherwise -1. The exact info returned is defined by
// MFS_Stat_t. Failure modes: inum does not exist.
int MFS_Stat(int inum, MFS_Stat_t *m) {

    assert( MFS_Init_flag == 1 );
    int func_num = 2;
#ifdef MSSG_DEBUG
    printf("Client is sending func_num %d with parameters:\n", func_num);
    printf("    inum = %d;", inum);
    printf("    m->type = %d;", m->type);
    printf("    m->size = %d;", m->size);
    printf("    m->blocks = %d;", m->blocks);
    printf("\n");
#endif

    // create the message
    char * buffer_write = malloc( UDP_BUFFER_SIZE ); 
    assert( buffer_write != NULL );
    char * c_ptr = buffer_write;
    int  * i_ptr  = (int*) buffer_write;
    *(i_ptr) = func_num;
    i_ptr++;

    // save other parameters here
    *( i_ptr ) = inum;
    i_ptr++;
    MFS_Stat_t * m_ptr = (MFS_Stat_t *) i_ptr;
    memcpy( m_ptr, m, sizeof(MFS_Stat_t) );

    int rc = TIME_OUT;
    char * buffer_read = malloc( UDP_BUFFER_SIZE );
    assert( buffer_read != NULL );
    while( rc == TIME_OUT ) {
        // write the message
        rc = UDP_Write(sd, &addr, buffer_write, UDP_BUFFER_SIZE);

        // read the response
        rc = Safe_UDP_Read(sd, &addr2, buffer_read, UDP_BUFFER_SIZE);
    }

    i_ptr = (int*) buffer_read;
    int status = *i_ptr;
    i_ptr++;
    m_ptr = (MFS_Stat_t*) i_ptr;
    memcpy( m, m_ptr, sizeof(MFS_Stat_t) );

    // free buffers
    free( buffer_read );
    free( buffer_write );

#ifdef MSSG_DEBUG
    printf("Client received func_num %d with parameters:\n", func_num);
    printf("    status = %d; m->type = %d, m->size = %d, m->blocks = %d\n", 
        status, m->type, m->size, m->blocks);
#endif
    if( status != 0 ) { return -1; }
    return 0;
}

// MFS_Write() writes a block of size 4096 bytes at the block offset specified
// by block . Returns 0 on success, -1 on failure. Failure modes: invalid inum,
// invalid block, not a regular file (you can't write to directories).
int MFS_Write(int inum, char *buffer, int block) {

    assert( MFS_Init_flag == 1 );
    int func_num = 3;
#ifdef MSSG_DEBUG
    printf("Client is sending func_num %d with parameters:\n", func_num);
    printf("    inum = %d;", inum);
    printf("    block = %d;", block);
    printf("\n");
#endif

    // create the message
    char * buffer_write = malloc( UDP_BUFFER_SIZE ); 
    assert( buffer_write != NULL );
    int  * i_ptr = (int*) buffer_write;
    char * c_ptr = buffer_write;
    *i_ptr = func_num;
    i_ptr++;

    // save other parameters here
    *i_ptr = inum;
    i_ptr++;
    c_ptr = (char*)i_ptr;
    memcpy( c_ptr, buffer, BUFFER_SIZE );
    c_ptr += BUFFER_SIZE;
    i_ptr = (int*)c_ptr; 
    *i_ptr = block;

    int rc = TIME_OUT;
    char * buffer_read = malloc( UDP_BUFFER_SIZE );
    assert( buffer_read != NULL );
    while( rc == TIME_OUT ) {
        // write the message
        rc = UDP_Write(sd, &addr, buffer_write, UDP_BUFFER_SIZE);

        // read the response
        rc = Safe_UDP_Read(sd, &addr2, buffer_read, UDP_BUFFER_SIZE);
    }

    i_ptr = (int*) buffer_read;
    int status = *i_ptr;

    // free buffers
    free( buffer_read );
    free( buffer_write );

#ifdef MSSG_DEBUG
    printf("Client received func_num %d with parameters:\n", func_num);
    printf("    status = %d\n", status);
#endif

    if( status != 0 ) { return -1; }
    return 0;

}

// MFS_Read() reads a block specified by block into the buffer from file
// specified by inum . The routine should work for either a file or directory;
// directories should return data in the format specified by MFS_DirEnt_t.
// Success: 0, failure: -1. Failure modes: invalid inum, invalid block.
int MFS_Read(int inum, char *buffer, int block) {

    assert( MFS_Init_flag == 1 );
    int func_num = 4;

#ifdef MSSG_DEBUG
    printf("Client is sending func_num %d with parameters:\n", func_num);
    printf("    inum = %d;", inum);
    printf("    buffer = %s;", buffer);  // NOTE: this may crash if buffer is not type char *
    printf("    block = %d;", block);
    printf("\n");
#endif

    // create the message
    char * buffer_write = malloc( UDP_BUFFER_SIZE ); 
    assert( buffer_write != NULL );
    int  * i_ptr = (int*) buffer_write;
    char * c_ptr = buffer_write;
    *i_ptr = func_num;
    i_ptr++;

    // save other parameters here
    *i_ptr = inum;
    i_ptr++;
    c_ptr = (char*) i_ptr;
    memcpy(c_ptr, buffer, BUFFER_SIZE);
    c_ptr += BUFFER_SIZE;
    i_ptr = (int *) c_ptr;
    *i_ptr = block;

    int rc = TIME_OUT;
    char * buffer_read = malloc( UDP_BUFFER_SIZE );
    assert( buffer_read != NULL );
    while( rc == TIME_OUT ) {
        // write the message
        rc = UDP_Write(sd, &addr, buffer_write, UDP_BUFFER_SIZE);

        // read the response
        rc = Safe_UDP_Read(sd, &addr2, buffer_read, UDP_BUFFER_SIZE);
    }

    i_ptr = (int*) buffer_read;
    int status = *i_ptr;
    i_ptr++;
    c_ptr = (char*) i_ptr;
    memcpy(buffer, c_ptr, BUFFER_SIZE);

    // free buffers
    free( buffer_read );
    free( buffer_write );

#ifdef MSSG_DEBUG
    printf("Client received func_num %d with parameters:\n", func_num);
    printf("    status = %d\n", status);
    printf("    buffer = %s\n", buffer);  // NOTE: this may crash if buffer is not type char *
#endif

    if( status != 0 ) { return -1; }
    return 0;

}

// MFS_Creat() makes a file ( type == MFS_REGULAR_FILE) or directory ( type ==
// MFS_DIRECTORY) in the parent directory specified by pinum of name name .
// Returns 0 on success, -1 on failure. Failure modes: pinum does not exist. If
// name already exists, return success (think about why).
int MFS_Creat(int pinum, int type, char *name) {

    assert( MFS_Init_flag == 1 );
    int func_num = 5;
#ifdef MSSG_DEBUG
    printf("Client is sending func_num %d with parameters:\n", func_num);
    printf("    pinum = %d;", pinum);
    printf("    type = %d;", type);
    printf("    name = %s;", name);
    printf("\n");
#endif

    // create the message
    char * buffer_write = malloc( UDP_BUFFER_SIZE ); 
    assert( buffer_write != NULL );
    int  * i_ptr = (int*) buffer_write;
    char * c_ptr = buffer_write;
    *i_ptr = func_num;
    i_ptr++;

    // save other parameters here
    *i_ptr = pinum;
    i_ptr++;
    *i_ptr = type;
    i_ptr++;
    c_ptr = (char*) i_ptr;
    strncpy( c_ptr, name, BUFFER_SIZE );

    int rc = TIME_OUT;
    char * buffer_read = malloc( UDP_BUFFER_SIZE );
    assert( buffer_read != NULL );
    while( rc == TIME_OUT ) {
        // write the message
        rc = UDP_Write(sd, &addr, buffer_write, UDP_BUFFER_SIZE);

        // read the response
        rc = Safe_UDP_Read(sd, &addr2, buffer_read, UDP_BUFFER_SIZE);
    }

    i_ptr = (int*) buffer_read;
    int status = *i_ptr;

    // free buffers
    free( buffer_read );
    free( buffer_write );

#ifdef MSSG_DEBUG
    printf("Client received func_num %d with parameters:\n", func_num);
    printf("    status = %d\n", status);
#endif

    if( status != 0 ) { return -1; }
    return 0;

}

// MFS_Unlink() removes the file or directory name from the directory specified
// by pinum . 0 on success, -1 on failure. Failure modes: pinum does not exist,
// directory is NOT empty. Note that the name not existing is NOT a failure by
// our definition (think about why this might be).
int MFS_Unlink(int pinum, char *name) {

    assert( MFS_Init_flag == 1 );
    int func_num = 6;

#ifdef MSSG_DEBUG
    printf("Client is sending func_num %d with parameters:\n", func_num);
    printf("    pinum = %d;", pinum);
    printf("    name = %s;", name);
    printf("\n");
#endif

    // create the message
    char * buffer_write = malloc( UDP_BUFFER_SIZE ); 
    assert( buffer_write != NULL );
    int  * i_ptr = (int*) buffer_write;
    char * c_ptr = buffer_write;
    *i_ptr = func_num;
    i_ptr++;

    // save other parameters here
    *i_ptr = pinum;
    i_ptr++;
    c_ptr = (char*) i_ptr;
    strncpy( c_ptr, name, BUFFER_SIZE );

    int rc = TIME_OUT;
    char * buffer_read = malloc( UDP_BUFFER_SIZE );
    assert( buffer_read != NULL );
    while( rc == TIME_OUT ) {
        // write the message
        rc = UDP_Write(sd, &addr, buffer_write, UDP_BUFFER_SIZE);

        // read the response
        rc = Safe_UDP_Read(sd, &addr2, buffer_read, UDP_BUFFER_SIZE);
    }

    i_ptr = (int*) buffer_read;
    int status = *i_ptr;

#ifdef MSSG_DEBUG
    printf("Client received func_num %d with parameters:\n", func_num);
    printf("    status = %d\n", status);
#endif

    // free buffers
    free( buffer_read );
    free( buffer_write );

    if( status != 0 ) { return -1; }
    return 0;

}

/*
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

*/
