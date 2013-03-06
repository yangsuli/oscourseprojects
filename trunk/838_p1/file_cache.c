#include "mytime.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MIN_SIZE (1024 * 1024) // let's try using 1M unit
//#define NUM_TRY 50
//#define START_POINT 64 //staring from 64M
#define BUF_SIZE 4096 //Let's read by 4K

//type = 1: expoential tryout
//type = 2: linear tryout
int main(int argc, char** argv){
	int fd;
	int i, j, k;
	double time1, time2;
	int try_cache_size = 0;
	cpu_set_t run_set;
	struct sched_param param;
	int step;
	int NUM_TRY;
	int START_POINT;
	void* buf_ptr = malloc(BUF_SIZE);
	assert(buf_ptr != NULL);

	if(argc != 5){
		printf("Usage file_cache start step NUM_TRY\n");
		exit(-1);
	}

	char* file = argv[1];
	START_POINT = atoi(argv[2]);
	step = atoi(argv[3]);
	NUM_TRY = atoi(argv[4]);

	//attach to one cpu and have the highest priority so that it doesn't get scheduled out
	CPU_ZERO(&run_set);
	CPU_SET(0, &run_set);
	assert(sched_setaffinity(0,sizeof(cpu_set_t),&run_set) == 0);
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	assert(sched_setscheduler(0,SCHED_FIFO,&param) == 0);

	get_realtime_offset();

	for(i = 1; i <= NUM_TRY; i++){
		try_cache_size = (START_POINT + i * step ) * MIN_SIZE;
		fd = open(file, O_RDONLY|O_LARGEFILE);
		assert(fd > 0);

	       //Let's just sequentially access these size
	       //this run is just for initialization
		for(j = 1; j <= try_cache_size/BUF_SIZE; j++){
			assert(read(fd, buf_ptr, BUF_SIZE) == BUF_SIZE); 
		}

	       //repeate 20 times to amortize intialization effort
		time1 = get_realtime();
		for(j = 0; j < 20; j++){
			assert(lseek(fd, 0, SEEK_SET) == 0);
			for(k = 1; k <= try_cache_size/BUF_SIZE; k++){
				assert(read(fd, buf_ptr, BUF_SIZE) == BUF_SIZE);
			}
		}
		time2 = get_realtime();
		printf("for cache size %d M, time for 20 repeated access is %.6f ms, avg is %.6f ms/M\n", START_POINT + i * step, time2 - time1, (time2 - time1)/(START_POINT + i * step));
		close(fd);
	}
	return 0;
}




