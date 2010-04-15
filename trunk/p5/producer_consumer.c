#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "cs537.h"

#define MAXTHREADS 100
#define MAX_LOOPS 50

//// global variables ////
pthread_cond_t c_empty, c_fill;
pthread_mutex_t mutex; 
int loops = 0; 
int numconsumers = 0;

int buffer[MAX_LOOPS]; 
int fill = 0; 
int use = 0; 
int numfilled = 0; 

void put(int value) { 
    buffer[fill] = value; // line F1 
    fill = (fill + 1) % MAX_LOOPS; // line F2 
    numfilled++; 
} 
int get() { 
    int tmp = buffer[use]; // line G1 
    use = (use + 1) % MAX_LOOPS; // line G2 
    numfilled--; 
    return tmp; 
} 

void *producer(void *arg) { 
    int i; 
    for (i = 0; i < loops; i++) { 
        Pthread_mutex_lock(&mutex); // p1 
        while (numfilled == MAX_LOOPS) // p2 
            Pthread_cond_wait(&c_empty, &mutex); // p3 
            put(i); // p4 
            Pthread_cond_signal(&c_fill); // p5 
            Pthread_mutex_unlock(&mutex); // p6 
    } 
} 
void *consumer(void *arg) { 
    int i; 
    for (i = 0; i < loops; i++) { 
        Pthread_mutex_lock(&mutex); // c1 
        while (numfilled == 0) // c2 
            Pthread_cond_wait(&c_fill, &mutex); // c3 
            int tmp = get(); // c4 
            Pthread_cond_signal(&c_empty); // c5 
            Pthread_mutex_unlock(&mutex); // c6 
            printf("%d\n", tmp); 
    } 
} 

int main(int argc, char *argv[]) { 
    assert(argc == 3); 
    loops = atoi(argv[1]); 
    numconsumers = atoi(argv[2]); 

    pthread_t pid, cid[MAXTHREADS];  // one producer, and many consumers

    // create threads (producer and consumers) 
    Pthread_create(&pid, NULL, producer, NULL); 

    int i = 0;
    for (i = 0; i < numconsumers; i++) 
        Pthread_create(&cid[i], NULL, consumer, NULL); 

        // wait for producer and consumers to finish 
        Pthread_join(pid, NULL); 

        for (i = 0; i < numconsumers; i++) { 
            Pthread_join(cid[i], NULL); 
        } 
        return 0; 
} 
