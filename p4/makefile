a.out: test.c libcounter.so liblist.so libhash.so counter.h lock_type.h list.h
	gcc -g -L . -lcounter -llist -lhash test.c -D SPINLOCK

libhash.so:hash.o spinlock.o
	gcc -g -shared -o libhash.so hash.o spinlock.o

hash.o:hash.c hash.h lock_type.h
	gcc -g -c -fpic  hash.c spinlock.c -D SPINLOCK

liblist.so:list.o spinlock.o
	gcc -g -shared -o liblist.so list.o spinlock.o

list.o:list.c list.h lock_type.h
	gcc -g -c -fpic list.c spinlock.c -D SPINLOCK

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

liblist_pthread.so:list_pthread.o
	gcc -g -shared -o liblist_pthread.so list_pthread.o

list_pthread.o:list.c list.h lock_type.h
	gcc -g -c -fpic list.c -o list_pthread.o -D PTHREAD_LOCK

clean:
	rm -rf *.o

cleanall:
	rm -rf *.o *.so *.out
