all: prefetch prefetch4 buffer_size file_cache direct_access

prefetch:prefetch.c mytime.h
	gcc -O2 -lrt -D_GNU_SOURCE -o prefetch prefetch.c

prefetch4:prefetch4.c mytime.h
	gcc -O2 -lrt -D_GNU_SOURCE -o prefetch4 prefetch4.c

buffer_size:buffer_size.c mytime.h
	gcc -O2 -lrt -D_GNU_SOURCE -o buffer_size buffer_size.c

file_cache:file_cache.c mytime.h
	gcc -O2 -lrt -D_GNU_SOURCE -o file_cache file_cache.c

direct_access:direct_access.c mytime.h
	gcc -O2 -lrt -D_GNU_SOURCE -o direct_access direct_access.c

clean:
	rm -rf prefetch prefetch4 buffer_size file_cache direct_access


