all:spinlock_test pthread_test

spinlock_test: test.c libcounter.so liblist.so libhash.so counter.h lock_type.h list.h hash.h
	gcc -L . -lcounter -llist -lhash -lpthread -o spinlock_test test.c -D SPINLOCK

pthread_test: test.c libcounter_pthread.so liblist_pthread.so libhash_pthread.so counter.h lock_type.h list.h hash.h
	gcc -L . -lcounter_pthread -llist_pthread -lhash_pthread -lpthread -o pthread_test test.c -D PTHREAD_LOCK

libhash.so:hash.o spinlock.o
	gcc -shared -o libhash.so hash.o spinlock.o

hash.o:hash.c hash.h lock_type.h
	gcc -c -fpic  hash.c spinlock.c -D SPINLOCK

liblist.so:list.o spinlock.o
	gcc -shared -o liblist.so list.o spinlock.o

list.o:list.c list.h lock_type.h
	gcc -c -fpic list.c spinlock.c -D SPINLOCK

libcounter.so:counter.o spinlock.o
	gcc -shared -o libcounter.so counter.o spinlock.o

counter.o: counter.c counter.h lock_type.h
	gcc -c -fpic counter.c spinlock.c -D SPINLOCK

spinlock.o: spinlock.c spinlock.h
	gcc -c -fpic spinlock.c

libcounter_pthread.so:counter_pthread.o
	gcc -shared -o libcounter_pthread.so counter_pthread.o

counter_pthread.o: counter.c counter.h lock_type.h
	gcc -c -fpic counter.c -o counter_pthread.o -D PTHREAD_LOCK

liblist_pthread.so:list_pthread.o
	gcc -shared -o liblist_pthread.so list_pthread.o

list_pthread.o:list.c list.h lock_type.h
	gcc -c -fpic list.c -o list_pthread.o -D PTHREAD_LOCK

libhash_pthread.so:hash_pthread.o
	gcc -shared -o libhash_pthread.so hash_pthread.o

hash_pthread.o:hash.c hash.h lock_type.h
	gcc -c -fpic hash.c -o hash_pthread.o -D PTHREAD_LOCK

clean:
	rm -rf *.o

cleanall:
	rm -rf *.o *.so *.out *.log pthread_test spinlock_test
