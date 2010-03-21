#ifndef __counter_h__
#define __counter_h__

#include <pthread.h>
#include "lock_type.h"


typedef struct __counter_t {
	int count;
	LOCK_TYPE counter_lock; //to protect count
} counter_t;

void Counter_Init(counter_t *c, int value);
int  Counter_GetValue(counter_t *c);
void Counter_Increment(counter_t *c);
void Counter_Decrement(counter_t *c);

#endif 

