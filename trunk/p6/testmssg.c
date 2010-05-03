#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include "mssg.h"

// check message type 0
int test0() {

    char buffer1[BUFFER_SIZE];    

    int msg_len1[NUM_MESSAGES];
    int msg_len2[NUM_MESSAGES];

    void * data1[NUM_MESSAGES];
    void * data2[NUM_MESSAGES];

    Params params;
    InitData( msg_len1, data1, &params );
    InitData( msg_len2, data2, &params );

    int fun_num1 = -1;
    int fun_num2 = -1;

    // create a message
    int x = 10;
    int * p = &x;
    data1[0] = (void *) p;

    char word1[] = "hi mom!";
    strncpy( (char*) data1[1], word1, BUFFER_SIZE);
    msg_len1[0] = sizeof(int);
    msg_len1[1] = (int) (strlen( (char*) data1[1] ) + 1);

    fun_num1 = 3;
    CreateMessage( fun_num1, msg_len1, data1, buffer1);

    // read the message
    ReadMessage( &fun_num2, msg_len2, data2, buffer1);

    // check if everything is the same
    int i;
    for( i = 0; i < NUM_MESSAGES; i++) {
        assert( msg_len1[i] == msg_len2[i] );
    }
    assert( msg_len1[0] > 0 );
    assert( msg_len1[1] > 0 );
    for( i = 2; i < NUM_MESSAGES; i++) {
        assert( msg_len1[i] == 0 );
    }

    printf("   fun_num1 = %d, fun_num2 = %d\n", fun_num1, fun_num2);
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

    char buffer1[BUFFER_SIZE];    

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
        assert( data1[i] != NULL );
        assert( data2[i] != NULL );
    }

    // create a message
    int x = 10;
    int * p = &x;
    char word1[] = "hi mom!";
    char word2[] = "what!?";
    data1[0] = (void *) p;
    strncpy( (char*) data1[1], word1, BUFFER_SIZE);
    strncpy( (char*) data1[2], word2, BUFFER_SIZE);
    msg_len1[0] = sizeof(int);
    msg_len1[1] = (int) (strlen( (char*) data1[1] ) + 1);
    msg_len1[2] = (int) (strlen( (char*) data1[2] ) + 1);

    CreateMessage( 3, msg_len1, data1, buffer1);

    // read the message
    int fun_num2 = -1;
    ReadMessage( &fun_num2, msg_len2, data2, buffer1);

    // check if everything is the same
    for( i = 0; i < NUM_MESSAGES; i++) {
        printf("  msg_len1[%d] = %d;  msg_len2[%d] = %d\n", i,msg_len1[i],
            i, msg_len2[i] );
    }

    printf("   data1[0] = %d;", * ((int *) data1[0] ) );
    printf("   data2[0] = %d\n", * ((int *) data2[0] ) );
    printf("   data1[1] = %s;", (char*) data1[1] );
    printf("   data2[1] = %s\n", (char*) data2[1] );
    printf("   data1[2] = %s;", (char*)  data1[2] );
    printf("   data2[2] = %s\n", (char*) data2[2] );

    printf("  does everything match up with each other?\n");
    sleep(1.0);

    return 0;

}
int main(int argc, char ** argv) {

    test0();

    test1();

    return 0;
}
