#include "hw1.h"
#include <sched.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>


#define PAGE_SIZE 4096
#define TRIAL_PAGES 500
#define REPEAT_ACCESS 10000

struct full_page{
	char whatever[PAGE_SIZE];
};

struct timespec ts;

struct full_page page_array[TRIAL_PAGES];

int main(){
	struct sched_param param;
	int i, trial_size;
	double time[TRIAL_PAGES];
	double start, end;
	cpu_set_t run_set;

	CPU_ZERO(&run_set);
	CPU_SET(0,&run_set);
	assert(sched_setaffinity(0,sizeof(cpu_set_t),&run_set) == 0);

	assert(sched_getparam(0,&param) == 0);
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	assert(sched_setscheduler(0,SCHED_FIFO,&param) == 0);

	get_realtime_offset();

	for(trial_size = 1; trial_size <= TRIAL_PAGES; trial_size++){
		start = get_realtime();
		for(i = 0; i < REPEAT_ACCESS; i++){
			page_array[i%trial_size].whatever[0] = 'c';
		}
		end = get_realtime();
		time[trial_size-1] = end - start;
	}

	for(i = 0; i < TRIAL_PAGES; i++){
		fprintf(stdout,"%d: %f\n",i+1, time[i]);
	}

	fprintf(stdout,"%Ld\n",get_ticks());
	clock_getres(CLOCK_PROCESS_CPUTIME_ID, &ts);
	fprintf(stdout,"%d, %d\n", ts.tv_sec, ts.tv_nsec);
	return 0;
}



