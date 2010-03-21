#ifndef __spinlock_h__
#define __spinlock_h__

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


typedef struct lock_t {
	int flag;
}spinlock_t;


void spinlock_acquire(spinlock_t *lock);

void spinlock_release(spinlock_t *lock);

void spinlock_init(spinlock_t *lock, void * null_ptr);

#endif
