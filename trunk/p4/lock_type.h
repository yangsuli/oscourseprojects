#ifndef __lock_type_h__
#define __lock_type_h__

#include <pthread.h>

#ifdef SPINLOCK
#define LOCK_TYPE spinlock_t
#define LOCK_INITIALIZER SPINLOCK_INITIALIZER
#define LOCK_INIT(lock_p,null_p) spinlock_init(lock_p,null_p)
#define LOCK(lock_p) spinlock_acquire(lock_p)
#define UNLOCK(lock_p) spinlock_release(lock_p)
#elif defined PTHREAD_LOCK
#define LOCK_TYPE pthread_mutex_t
#define LOCK_INITIALIZER PTHREAD_MUTEX_INITIALIZER
#define LOCK_INIT(lock_p,attr_p) pthread_mutex_init(lock_p,attr_p)
#define LOCK(lock_p) pthread_mutex_lock(lock_p)
#define UNLOCK(lock_p) pthread_mutex_unlock(lock_p)
#endif

#endif
