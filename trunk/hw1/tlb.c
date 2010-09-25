#include "hw1.h"
#include <sched.h>
#include <stdio.h>


#define PAGE_SIZE 4096
#define TRIAL_PAGES 500

struct full_page{
	char whatever[PAGE_SIZE];
};

int main(){
	struct sched_param param;
	struct full_page page_array[TRIAL_PAGES];
	int i;
	double time[TRIAL_PAGES];




	assert(sched_getparam(0,&param) == 0);
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	assert(sched_setscheduler(0,SCHED_FIFO,&param) == 0);

	get_time_offset();

	for(i = 0; i < TRIAL_PAGES; i++){
		page_array[i].whatever[0] = 'c';
		time[i] = get_time();
	}

	for(i = 0; i < TRIAL_PAGES; i++){
		fprintf(stdout,"%f\n",time[i]);
	}
	
	return 0;
}



