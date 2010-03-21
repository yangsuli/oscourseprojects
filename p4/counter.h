#ifndef __counter_h__
#define __counter_h__

#include <pthread.h>
#include "lock_type.h"
#include "spinlock.h"


typedef struct __counter_t {
	int count;
	LOCK_TYPE counter_lock; //to protect count
	//spinlock_t counter_lock; //just for debug purpose
} counter_t;

void Counter_Init(counter_t *c, int value);
int  Counter_GetValue(counter_t *c);
void Counter_Increment(counter_t *c);
void Counter_Decrement(counter_t *c);

#endif 

