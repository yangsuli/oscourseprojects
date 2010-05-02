#ifndef __MSSG_H
#define __MSSG_H

#define BUFFER_SIZE (4096)
#define NUM_MESSAGES (5)
// TODO -- why can't these have const in front of them?
//void CreateMessage( int type, const int msg_len[], 
//    const void * data[], char * buffer);
void CreateMessage( int type, int msg_len[], 
    void * data[], char * buffer);

void ReadMessage( int * type, int msg_len[], 
    void * data[], const char * buffer); 

// SUMMMARY OF message types:
//
// type = 0: 
//
//         typeof( data[0] ) = int * 
//         typeof( data[1] ) = char *
//
//         msg_len[0] = sizeof(int);
//         msg_len[1] = strlen(data[1]) + 1;   (extra character for '\0')
//
// type = 1: 
//
//         typeof( data[0] ) = int * 
//         typeof( data[1] ) = char *
//
//         msg_len[0] = sizeof(int);
//         msg_len[1] = strlen(data[1]) + 1;   (extra character for '\0')

#endif
