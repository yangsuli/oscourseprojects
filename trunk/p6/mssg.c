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

void SetLenZero( int istart, int msg_len[] ) {
    int i = istart;
    while( i < NUM_MESSAGES ) {
        msg_len[i++] = 0; 
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
            SetLenZero(1, msg_len);
            break;

        case 1:

            msg_len[0] = sizeof(int);
            inum = params->inum;
            p = &inum;
            data[0] = (void *) p;
            SetLenZero(1, msg_len);
            break;

        case 2:

            inum = params->inum;
            p = &inum;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;

            int type = params->type;
            p = &type;
            msg_len[1] = sizeof(int);
            data[1] = (void *) p;

            int size = params->size;
            p = &size;
            msg_len[2] = sizeof(int);
            data[2] = (void *) p;

/// TODO i don't think this is correct ....
            msg_len[3] = sizeof(int);
            data[3] = (void *) params->block;

            SetLenZero(4, msg_len );

            break;

        case 3:
            
            inum = params->inum;
            p = &inum;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;

            buff = params->buffer;
            msg_len[1] = strlen(buff) + 1;
            data[1]    = (void *) buff;

            SetLenZero(2, msg_len);
            break;

        case 4:

            status = params->status;
            p = &status;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;

            buff   = params->buffer;
            data[1] = (void *) buff;
            msg_len[1] = strlen(buff) + 1;

            SetLenZero(2, msg_len );
            
            break;

        case 5:

            status = params->status;
            p = &status;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;
            SetLenZero(1, msg_len);

            break;

        case 6:

            status = params->status;
            p = &status;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;

            SetLenZero(1, msg_len);

            break;

    }

    // create the message
    i = CreateMessage( 0, func_num, msg_len, data, buffer);
    ResetParams( params );
    return i;

}

// main routine for reading a message from the client side
int ClientReadMessage(Params *params, int msg_len[], void * data[], 
                            char * buffer ) {

    int * p = NULL;       // generic data pointer here
    char * buf = NULL;

    ///////// read an entire message /////
    int msg_type = -1;
    int func_num = -1;
    ResetParams( params );
    ReadMessage( &msg_type, &func_num, msg_len, data, buffer);
    params->func_num = func_num;
    switch( func_num ) {
        case 0:

            p = (int *) data[0];
            params->status = *p;
            break;

        case 1:

            p = (int *) data[0];
            params->inum = *p;
            break;

        case 2:

            fprintf(stderr, "  this function is not implemented yet\n");
            exit(1);

            p = (int *) data[0];
            params->inum = *p;

            p = (int *) data[1];
            params->size = *p;

            // TODO WHAT IS TYPE?

            //params->block = data[3];
            //data[3] = (void *) params->block;

            break;

        case 3:
            
            p = (int *) data[0];
            params->inum = *p;

            buf = (char *) data[1];
            strncpy( params->buffer, buf, BUFFER_SIZE);
            break;

        case 4:

            p = (int *) data[0];
            params->status = *p;

            buf = (char *) data[1];
            strncpy( params->buffer, buf, BUFFER_SIZE);

            break;

        case 5:

            p = (int *) data[0];
            params->status = *p;

            break;

        case 6:

            p = (int *) data[0];
            params->status = *p;

            break;

    }

    return 0;

}


// main routine for creating a client side message to be passed to the server
int ClientCreatMessage(Params *params, int msg_len[], void * data[], 
                            char * buffer ) {

    int * p = NULL;       // generic data pointer here
    int i, pinum, inum, block, type;

    char * buff;
    char * name;

    int func_num = params->func_num;
    switch( func_num ) {
        case 0:

            break;

        case 1:

            msg_len[0] = sizeof(int);
            pinum = params->pinum;
            p = &pinum;
            data[0] = (void *) p;

            msg_len[1] = strlen(name) + 1;
            name = params->name;
            data[1] = (void *) name;

            SetLenZero(2,msg_len);

            break;
        case 2:

            inum = params->inum;
            p = &inum;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;

            SetLenZero(1,msg_len);

            break;

        case 3:
            
            inum = params->inum;
            p = &inum;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;

            buff = params->buffer;
            msg_len[1] = strlen(buff)+1;
            data[1]    = (void *) buff;

            block = params->block;
            p = &block;
            msg_len[2] = sizeof(int);
            data[2] = (void *) p;

            SetLenZero(3,msg_len);
            break;

        case 4:

            inum = params->inum;
            p = &inum;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;

            block = params->block;
            p = &block;
            data[1] = (void *) p;
            msg_len[1] = sizeof(int);

            SetLenZero(2,msg_len);
            
            break;

        case 5:

            type = params->type;
            p = &type;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;

            data[1] = (void *) params->name;
            msg_len[1] = strlen( params->name ) + 1;

            SetLenZero(2,msg_len);
 
            break;

        case 6:

            pinum = params->pinum;
            p = &pinum;
            msg_len[0] = sizeof(int);
            data[0] = (void *) p;

            data[1] = (void *) params->name;
            msg_len[1] = strlen( params->name ) + 1;

            SetLenZero(2,msg_len);

            break;

    }

    // create the message
    i = CreateMessage( 0, func_num, msg_len, data, buffer);
    ResetParams( params );
    return i;

}

int ServerReadMessage(Params *params, int msg_len[], void * data[], 
                            char * buffer ) {

    int * p = NULL;       // generic data pointer here
    char * buff;

    /////////// read an entire message /////
    int msg_type = -1;
    int func_num = -1;
    ResetParams( params );
    ReadMessage( &msg_type, &func_num, msg_len, data, buffer);
    params->func_num = func_num;

    switch( func_num ) {
        case 0:

            break;

        case 1:

            p = (int*) data[0];
            params->pinum = *p;

            strncpy( params->name, (char*)data[1], BUFFER_SIZE);

            break;

        case 2:

            p = (int*) data[0];
            params->inum = *p;

            break;

        case 3:
            
            p = (int*) data[0];
            params->inum = *p;

            buff = (char *) data[1];
            strncpy( params->buffer, buff, BUFFER_SIZE);

            p = (int*) data[2];
            params->block = *p;

            break;

        case 4:

            p = (int*) data[0];
            params->inum = *p;

            p = (int*) data[1];
            params->block = *p;

            break;

        case 5:

            p = (int*) data[0];
            params->type = *p;

            buff = (char *) data[1];
            strncpy( params->name, buff, BUFFER_SIZE );
            break;

        case 6:

            p = (int*) data[0];
            params->pinum = *p;

            buff = (char *) data[1];
            strncpy( params->name, buff, BUFFER_SIZE );

            break;

    }


    return 0;

}
