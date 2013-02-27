all: prefetch prefetch2

prefetch:prefetch.c mytime.h
	gcc -O2 -lrt -D_GNU_SOURCE -o prefetch prefetch.c

prefetch2:prefetch2.c mytime.h
	gcc -O2 -lrt -D_GNU_SOURCE -o prefetch2 prefetch2.c

clean:
	rm -rf prefetch prefetch2


