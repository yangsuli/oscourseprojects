all: prefetch prefetch4 buffer_size file_cache

prefetch:prefetch.c mytime.h
	gcc -O2 -lrt -D_GNU_SOURCE -o prefetch prefetch.c

prefetch4:prefetch4.c mytime.h
	gcc -O2 -lrt -D_GNU_SOURCE -o prefetch4 prefetch4.c

buffer_size:buffer_size.c mytime.h
	gcc -O2 -lrt -D_GNU_SOURCE -o buffer_size buffer_size.c

file_cache:file_cache.c mytime.h
	gcc -O2 -lrt -D_GNU_SOURCE -o file_cache file_cache.c

clean:
	rm -rf prefetch prefetch4 buffer_size file_cache


