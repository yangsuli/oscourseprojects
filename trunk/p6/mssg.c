#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>  // needed for memcpy
#include "mssg.h"

// Create a message of type "type" and write out to buffer
// Returns 0 on success, -1 on failure.
int CreateMessage( int type, int fun_number, int msg_len[], 
    void * data[], char * buffer) {

    // write out all the header information
    int * header = (int *) buffer;
    *header = type;
    header++;
    *header = fun_number;
    header++;
    int i = 0;
    int mssglen = 0;
    for( i = 0; i < NUM_MESSAGES; i++ ) {
        *header = msg_len[i];
        mssglen += msg_len[i];
        header++;
    }

    if(  mssglen > UDP_BUFFER_SIZE ) {
        fprintf(stderr, "mssglen is too big\n");
    }

    // write out all the data
    void * data_ptr = (void*) header;
    for( i = 0; i < NUM_MESSAGES; i++ ) {
        if( msg_len[i] > 0 ) {
            memcpy( data_ptr, data[i], msg_len[i] );
            data_ptr += msg_len[i];
        }
    }

    return 0;

}

// Read a message from buffer, and write to type, msg_len and data.
void ReadMessage( int * type, int * fun_number, int msg_len[], 
    void * data[], const char * buffer) {

    // read all the header information (sizes and message type)
    int * header = (int *) buffer;
    *type = *header;
    header++;
    *fun_number = *header;
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

// put garbage values in every entry in Params p
void ResetParams( Params *p ) {
    p->func_num = -1;
    strncpy( p->name, "", BUFFER_SIZE);
    strncpy( p->buffer, "", BUFFER_SIZE);
    p->pinum = -1;
    p->inum  = -1;
    p->size  = -1;
    p->block = -1;
    p->message_type = -1;
    p->status = -1;
}

int InitData( int msg_len[], void * data[], Params *p) {

    int i;
    for(i = 0; i < NUM_MESSAGES; i++ ) {
        msg_len[i] = 0;
        data[i] = malloc( BUFFER_SIZE );
        if( data[i] == NULL ) {
            fprintf(stderr, "malloc failed\n");
            return -1;
        }
    }

    // put garbage values in every paramater field
    ResetParams( p );
    return 0;
}

// main routine for creating a server side message to be passed to the client
int ServerCreatMessage(Params *params, int msg_len[], void * data[], 
                            char * buffer ) {

    int * p = NULL;       // generic data pointer here
    int i, inum, status;

    char * buff;

    int func_num = params->func_num;
    switch( func_num ) {
        case 0:
            msg_len[0] = sizeof(int);
            status = params->status;
            p = &status;
            data[0] = (void *) p;
            i = 1;
            while( i < NUM_MESSAGES ) {
                msg_len[i++] = 0;
            }

            break;

        case 1:

            msg_len[0] = sizeof(int);
            inum = params->inum;
            p = &inum;
            data[0] = (void *) p;
            i = 1;
            while( i < NUM_MESSAGES ) {
                msg_len[i++] = 0;
            }

            break;
        case 2:

            inum = params->inum;
            p = &inum;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;

            int size = params->size;
            p = &size;
            msg_len[1] = sizeof(int);
            data[1] = (void *) p;

            // TODO WHAT PARAMETER IS TYPE HERE?
            msg_len[2] = 0;
            
            msg_len[3] = sizeof(int);
            data[3] = (void *) params->block;

            i = 4;
            while( i < NUM_MESSAGES ) {
                msg_len[i++] = 0;
            }

            break;

        case 3:
            
            inum = params->inum;
            p = &inum;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;

            buff = params->buffer;
            msg_len[1] = BUFFER_SIZE;
            data[1]    = (void *) buff;

            i = 2;
            while( i < NUM_MESSAGES ) {
                msg_len[i++] = 0;
            }
            break;

        case 4:

            status = params->status;
            p = &status;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;

            buff   = params->buffer;
            data[1] = (void *) buff;
            msg_len[1] = BUFFER_SIZE;

            i = 2;
            while( i < NUM_MESSAGES ) {
                msg_len[i++] = 0;
            }
            
            break;

        case 5:

            status = params->status;
            p = &status;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;
            i = 1;
            while( i < NUM_MESSAGES ) {
                msg_len[i++] = 0;
            }

            break;

        case 6:

            status = params->status;
            p = &status;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;

            i = 1;
            while( i < NUM_MESSAGES ) {
                msg_len[i++] = 0;
            }

            break;

    }

    // create the message
    i = CreateMessage( 0, func_num, msg_len, data, buffer);
    ResetParams( params );
    return i;

}

int ClientCreatMessage(Params *p,int msg_len[],void * data[],char * buffer) {
    return -1;
}
