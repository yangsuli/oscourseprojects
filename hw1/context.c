#include <sched.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include "hw1.h"

#define REPEAT_SIZE 500

int main(){
	struct sched_param param;
	int i = 0, j = 0, k = 0;
	int pid;
	double time1_start[REPEAT_SIZE], time2_start[REPEAT_SIZE];
	double time1_end[REPEAT_SIZE], time2_end[REPEAT_SIZE];
	double *time_start, *time_end;
	char *prefix;
	cpu_set_t run_set;
	
	get_time_offset();
	CPU_ZERO(&run_set);
	CPU_SET(0,&run_set);

	assert(sched_setaffinity(0,sizeof(cpu_set_t),&run_set) == 0);

	assert(sched_getparam(0,&param) == 0);
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	//fprintf(stderr,"%d\n",param.sched_priority);
	assert(sched_setscheduler(0, SCHED_FIFO,&param) == 0);

	if((pid = fork()) < 0){
		fprintf(stderr,"fork error!");
		return -1;
	}

	if(pid ==0 ){//childe;
		time_start = time2_start;
		time_end = time2_end;
	}else{//parent
		time_start = time1_start;
		time_end = time1_end;
	}

	for(i = 0; i < REPEAT_SIZE; i++){
		time_start[i] = get_time();
		for(j = 0; j < 1000000; j++){
			k++;
		}
		time_end[i] = get_time();
		assert(sched_yield() == 0);
	}

	if(pid == 0){
 		prefix = "child";
	}else{
		prefix = "parent";
	}
	
	for(i = 0; i < REPEAT_SIZE; i++){
		fprintf(stdout,"%s start %f\n", prefix, time_start[i]);
	}

	for(i = 0; i < REPEAT_SIZE; i++){
		fprintf(stdout, "%s, end %f\n", prefix, time_end[i]);
	}


	return 0;
}

	
