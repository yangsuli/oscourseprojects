#include "hw1.h"
#include <sched.h>
#include <stdio.h>


#define PAGE_SIZE 4096
#define TRIAL_PAGES 500
#define REPEAT_ACCESS 100

struct full_page{
	char whatever[PAGE_SIZE];
};

int main(){
	struct sched_param param;
	struct full_page page_array[TRIAL_PAGES];
	int i, trial_size;
	double time[TRIAL_PAGES];
	double start, end;

	assert(sched_getparam(0,&param) == 0);
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	assert(sched_setscheduler(0,SCHED_FIFO,&param) == 0);

	get_time_offset();

	for(trial_size = 1; trial_size <= TRIAL_PAGES; trial_size++){
		start = get_time();
		for(i = 0; i < REPEAT_ACCESS; i++){
			page_array[i%trial_size].whatever[0] = 'c';
		}
		end = get_time();
		time[trial_size-1] = end - start;
	}

	for(i = 0; i < TRIAL_PAGES; i++){
		fprintf(stdout,"%d: %f\n",i+1, time[i]);
	}

	return 0;
}



