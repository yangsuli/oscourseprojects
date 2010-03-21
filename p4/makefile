a.out: test.c libcounter.so counter.h lock_type.h
	gcc -g -L . -lcounter test.c -D SPINLOCK

libcounter.so:counter.o spinlock.o
	gcc -g -shared -o libcounter.so counter.o spinlock.o

counter.o: counter.c counter.h lock_type.h
	gcc -g -c -fpic counter.c spinlock.c -D SPINLOCK

spinlock.o: spinlock.c spinlock.h
	gcc -g -c -fpic spinlock.c

libcounter_pthread.so:counter_pthread.o
	gcc -g -shared -o libcounter_pthread.so counter_pthread.o

counter_pthread.o: counter.c counter.h lock_type.h
	gcc -g -c -fpic counter.c -o counter_pthread.o -D PTHREAD_LOCK

clean:
	rm -rf *.o
