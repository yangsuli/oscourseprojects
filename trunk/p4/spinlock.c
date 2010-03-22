#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include<fcntl.h>
#include <sys/types.h>
#include <string.h>
#include "spinlock.h"


static inline uint
xchg(volatile unsigned int *addr, unsigned int newval)
{
	uint result;
	asm volatile("lock; xchgl %0, %1" : "+m" (*addr), "=a" (result) : "1" (newval) : "cc");
	return result;
}


void spinlock_init(spinlock_t *lock, void * null_ptr)
{
	lock->flag=0;
}//here we add a null pointer arugment to mimic the interface provided by pthread_mutex_init so that we can switch to pthread_lock seamlessly

void spinlock_acquire(spinlock_t *lock)
{
	while(xchg(&lock->flag,1)==1)
	{
		;
	}
}

void spinlock_release(spinlock_t *lock)
{
	lock->flag=0;
}


void spinlock_destroy(spinlock_t *lock){
}//empty body. Just to mimic pthread_mutex behavior
