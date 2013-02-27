all: prefetch prefetch4

prefetch:prefetch.c mytime.h
	gcc -O2 -lrt -D_GNU_SOURCE -o prefetch prefetch.c

prefetch4:prefetch4.c mytime.h
	gcc -O2 -lrt -D_GNU_SOURCE -o prefetch4 prefetch4.c

clean:
	rm -rf prefetch prefetch4


