#include "counter.h"
#include <pthread.h>

void Counter_Init(counter_t *c, int value){
	c -> count = value; // no need to protect this initialization
	c -> counter_lock = PTHREAD_MUTEX_INITIALIZER;
}

int Counter_GetValue(counter_t *c){
	int n_val;
	//lock needed here since if one thread is updating this value, we would like to wait until it's done and then get the new value
	//also, if the write operation  cannot be done within one instruction, then lock become necessary here. So, also for portability
	pthread_mutex_lock(&c->counter_lock);
	n_val = c -> count;
	pthread_mutex_unlock(&c->counter_lock);
	return n_val;
}

void Counter_Increment(counter_t *c){
	pthread_mutex_lock(&c->counter_lock);
	c -> count ++;
	pthread_mutex_unlock(&c->counter_lock);
}

void Counter_Decrement(counter_t *c){
	pthread_mutex_lock(&c->counter_lock);
	c -> count --;
	pthread_mutex_unlock(&c->counter_lock);
}
