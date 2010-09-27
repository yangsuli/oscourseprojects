#include <sys/time.h>
#include <assert.h>
#include <stddef.h>
#include <unistd.h> 
#include <time.h>

typedef unsigned long long ticks;

static __inline__ ticks get_ticks(void){
	unsigned a, d;
	asm("cpuid");
	asm volatile("rdtsc" : "=a" (a), "=d" (d));

	return (((ticks)a) | (((ticks)d) << 32));
}

double time_offset;
double realtime_offset;

void get_time_offset(){
	struct timeval t;
	int rc = gettimeofday(&t,NULL);
	assert(rc==0);
	time_offset = t.tv_sec;
}

double get_time(){
	struct timeval t;
	int rc = gettimeofday(&t,NULL);
	assert(rc == 0);
	return 1e3*(t.tv_sec - time_offset) + t.tv_usec/1e3;
}

void get_realtime_offset(){
	struct timespec t;
	int rc = clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&t);
	assert(rc==0);
	time_offset = t.tv_sec;
}

double get_realtime(){
	struct timespec t;
	int rc = clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&t);
	assert(rc==0);
	return 1e3*(t.tv_sec -realtime_offset) + t.tv_nsec/1e6;
}
