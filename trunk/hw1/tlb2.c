#include "hw1.h"
#include <sched.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

#define PAGE_SIZE 4096
#define TRIAL_PAGES 500


struct full_page{
	char whatever[PAGE_SIZE];
};

struct full_page page_array[TRIAL_PAGES];

int main(){
	struct sched_param param;
	int i;
	double time[TRIAL_PAGES];
	double start, end;
	cpu_set_t run_set;

	CPU_ZERO(&run_set);
	CPU_SET(0,&run_set);
	assert(sched_setaffinity(0,sizeof(cpu_set_t),&run_set) == 0);

	assert(sched_getparam(0,&param) == 0);
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	assert(sched_setscheduler(0,SCHED_FIFO,&param) == 0);

	//pop up entries into TLB
	for(i = 0; i < TRIAL_PAGES; i++){
		page_array[i].whatever[0] = 'c';
	}

	get_realtime_offset();

	//access memory, which may or may not reside in TLB
	for(i = TRIAL_PAGES - 1; i >= 0; i--){
		start = get_realtime();
		page_array[i].whatever[0] = 'a';
		end = get_realtime();
		time[i] = end - start;
	}

	for(i = TRIAL_PAGES -1; i >= 0; i--){
		fprintf(stdout,"%f\n", time[i]);
	}

	return 0;
}



