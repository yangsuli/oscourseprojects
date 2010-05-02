#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "mssg.h"

// check message type 0
int test0() {

    char buffer1[BUFFER_SIZE];    
//  char buffer2[BUFFER_SIZE];    

    int msg_len1[NUM_MESSAGES];
    int msg_len2[NUM_MESSAGES];

    void * data1[NUM_MESSAGES];
    void * data2[NUM_MESSAGES];

    int i;
    for(i = 0; i < NUM_MESSAGES; i++ ) {
        msg_len1[i] = 0;
        msg_len2[i] = 0;
        data1[i] = malloc( BUFFER_SIZE );
        data2[i] = malloc( BUFFER_SIZE );
    }

    int type1 = -1;
    int type2 = -1;

    // create a message
    type1 = 0;
    int x = 10;
    int * p = &x;
    char word1[] = "hi mom!";
    data1[0] = (void *) p;
    strncpy( (char*) data1[1], word1, BUFFER_SIZE);
    msg_len1[0] = sizeof(int);
    msg_len1[1] = (int) (strlen( (char*) data1[1] ) + 1);

    CreateMessage( type1, msg_len1, data1, buffer1);

    // read the message
    ReadMessage( &type2, msg_len2, data2, buffer1);

    // check if everything is the same
    for( i = 0; i < NUM_MESSAGES; i++) {
        assert( msg_len1[i] == msg_len2[i] );
    }
    assert( msg_len1[0] > 0 );
    assert( msg_len1[1] > 0 );
    for( i = 2; i < NUM_MESSAGES; i++) {
        assert( msg_len1[i] == 0 );
    }

    printf("   data1[0] = %d;", * ((int *) data1[0] ) );
    printf("   data2[0] = %d\n", * ((int *) data2[0] ) );
    printf("   data1[1] = %s;", (char*) data1[1] );
    printf("   data2[1] = %s\n", (char*) data2[1] );

    printf("  does everything match up with each other?\n");
    sleep(1.0);

    return 0;

}

// check message type 1
int test1() {

// THIS IS CURRENTLY A DUPLICATE OF TEST0 -- CHANGE THIS TO TEST MESSAGE TYPE
// 1
/*
    char buffer1[BUFFER_SIZE];    
    char buffer2[BUFFER_SIZE];    

    int msg_len1[NUM_MESSAGES];
    int msg_len2[NUM_MESSAGES];

    void * data1[NUM_MESSAGES];
    void * data2[NUM_MESSAGES];

    int i;
    for(i = 0; i < NUM_MESSAGES; i++ ) {
        msg_len1[i] = 0;
        msg_len2[i] = 0;
        data1[i] = malloc( BUFFER_SIZE );
        data2[i] = malloc( BUFFER_SIZE );
    }

    int type1 = -1;
    int type2 = -1;

    // create a message
    type1 = 0;
    int x = 10;
    int * p = &x;
    char word1[] = "hi mom!";
    data1[0] = (void *) p;
    strncpy( (char*) data1[1], word1, BUFFER_SIZE);
    msg_len1[0] = sizeof(int);
    msg_len1[1] = (int) (strlen( (char*) data1[1] ) + 1);

    CreateMessage( type1, msg_len1, data1, buffer1);

    // read the message
    ReadMessage( &type2, msg_len2, data2, buffer1);

    // check if everything is the same
    for( i = 0; i < NUM_MESSAGES; i++) {
        printf("  msg_len1[%d] = %d;  msg_len2[%d] = %d\n", i,msg_len1[i],
            i, msg_len2[i] );
    }

    printf("   data1[0] = %d;", * ((int *) data1[0] ) );
    printf("   data2[0] = %d\n", * ((int *) data2[0] ) );
    printf("   data1[1] = %s;", (char*) data1[1] );
    printf("   data2[1] = %s\n", (char*) data2[1] );

    printf("  does everything match up with each other?\n");
    pause(1.0);

*/

    return 0;

}
int main(int argc, char ** argv) {

    test0();

    test1();

    return 0;
}
