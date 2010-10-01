#include "hw1.h"
#include <sched.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>


#define PAGE_SIZE 4096
#define TRIAL_PAGES 5000
#define REPEAT_ACCESS 10000

struct full_page{
	char whatever[PAGE_SIZE];
};

struct full_page page_array[TRIAL_PAGES];

int main(){
	struct sched_param param;
	int i,j, trial_size;
	double time[TRIAL_PAGES];
	double start, end;
	int add_result = 0;
	cpu_set_t run_set;

	//inialize page_array
	for(i = 0; i < TRIAL_PAGES; i++){
		for(j = 0; j < PAGE_SIZE; j++){
			page_array[i].whatever[j] = 0;
		}
	}
	
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
			page_array[(i*(trial_size-1))%trial_size].whatever[0] = 'c';
		}
		end = get_realtime();
		time[trial_size-1] = end - start;
	}

	//look at the value, just to make sure memory access is not optimized off
	for(i = 0; i < TRIAL_PAGES; i++){
		add_result+=page_array[i].whatever[0];
	}

	for(i = 0; i < TRIAL_PAGES; i++){
		fprintf(stdout,"%d: %f\n",i+1, time[i]);
	}

	fprintf(stdout, "add_result: %d\n", add_result);
	return 0;
}



