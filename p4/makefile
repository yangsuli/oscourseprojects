libcounter.so:counter.o
	gcc -shared -o limcounter.so counter.o

counter.o: counter.c counter.h lock_type.h
	gcc -c -fpic counter.c -D SPINLOCK

libcounter_pthread.so:counter_pthread.o
	gcc -shared -o limcounter_pthread.so counter_pthread.o

counter_pthread.o: counter.c counter.h lock_type.h
	gcc -c -fpic counter.c -o counter_pthread.o -D PTHREAD_LOCK
