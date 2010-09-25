#include <sys/time.h>
#include <assert.h>

double time_offset;

double get_time_offset(){
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

