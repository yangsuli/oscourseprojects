#include "mytime.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

//Let's read in 512K
//#define BUF_SIZE (128*1024)
#define BUF_SIZE 4096
#define SEQ_READ_SIZE (200*1024*1024) //200M
#define NUM_TRY 100 //I think 500*512K = 256M might be big enough for prefetch cache?
#define START 0
#define STEP (512*1024)

int main(int argc, char** argv){
	int fd;
	int i, j;
	double time1, time2;
	cpu_set_t run_set;
	struct sched_param param;
	double time[NUM_TRY];
	void *buf_ptr = malloc(BUF_SIZE);
	assert(buf_ptr != NULL);

	if(argc != 2){
		printf("Usage prefetch4 file_to_read\n");
		exit(-1);
	}

	char* file = argv[1]; 

	//disable look-ahead cache of disk, because that could affect our measurements
	//assert(system("hdparm -A0 /dev/sda") == 0);
	//assert(system("hdparm -W0 /dev/sda") == 0);

	//attach to one cpu and have the highest priority so that it doesn't get scheduled out
	CPU_ZERO(&run_set);
	CPU_SET(0, &run_set);
	assert(sched_setaffinity(0,sizeof(cpu_set_t),&run_set) == 0);
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	assert(sched_setscheduler(0,SCHED_FIFO,&param) == 0);


	for(i = 0; i < NUM_TRY; i++){


		//get_time_offset();
		get_realtime_offset();
		assert((fd = open(file, O_RDONLY)) >= 0);
/*
		//Let's read sequentially for some time
		for(j = 0; j < SEQ_READ_SIZE/BUF_SIZE; j++){
			assert(read(fd,buf_ptr, BUF_SIZE) == BUF_SIZE);
		}
*/
		//Let's measure time now
		//time1 = get_time();
		assert(read(fd,buf_ptr, BUF_SIZE) == BUF_SIZE);
		//wait for prefetching
		usleep(40000);
		assert(lseek(fd, (i + START)*STEP, SEEK_SET) == (i + START)*STEP);
		time1 = get_realtime();
		assert(read(fd,buf_ptr,BUF_SIZE) == BUF_SIZE);
		time2 = get_realtime();
		time[i] = time2 - time1;

		close(fd);
	}


	for(i = 0; i < NUM_TRY; i++){
		printf("%f\n", time[i]);
	}


	return 0;
}
	






