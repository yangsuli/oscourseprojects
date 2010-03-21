#ifndef __counter_h__
#define __counter_h__

#include <pthread.h>

typedef struct __counter_t {
	int count;
	pthread_mutex_t counter_lock; //to protect count
} counter_t;

void Counter_Init(counter_t *c, int value);
int  Counter_GetValue(counter_t *c);
void Counter_Increment(counter_t *c);
void Counter_Decrement(counter_t *c);

#endif 

