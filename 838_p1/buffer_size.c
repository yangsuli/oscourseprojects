#include "mytime.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define NUM_TRY 100
#define READ_COUNT 1000
#define READ_SIZE (1024*1024*32) //Randomly read 64M of data
#define MIN_SIZE 512
#define FILE_SIZE (1024*1024*512) //512M at least


//type 1: same count of reads
//type 2: same data size
int main(int argc, char** argv){
	int fd;
	int i, j;
	double time1, time2;
	int buf_size;
	int seek_pos;
	cpu_set_t run_set;
	struct sched_param param;
	int actual_count = 0;
	int type;

	if(argc != 3){
		printf("Usage buffer_size file_to_read type\n");
		exit(-1);
	}

	char* file = argv[1];
	type = atoi(argv[2]);


	//attach to one cpu and have the highest priority so that it doesn't get scheduled out
	CPU_ZERO(&run_set);
	CPU_SET(0, &run_set);
	assert(sched_setaffinity(0,sizeof(cpu_set_t),&run_set) == 0);
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	assert(sched_setscheduler(0,SCHED_FIFO,&param) == 0);

	get_realtime_offset();



	for(i = 1; i <= NUM_TRY; i++){
		buf_size = i * 	MIN_SIZE;
		void *buf_ptr = malloc(buf_size);
		assert(buf_ptr != NULL);
		assert(system("sync;echo 3 > /proc/sys/vm/drop_caches") == 0);

		fd = open(file, O_RDONLY|O_LARGEFILE);
		assert(fd > 0);

		if(type == 1){
			actual_count = READ_COUNT;
		}else if(type == 2){
			actual_count = READ_SIZE/buf_size;
		}

		time1 = get_realtime();
		for(j = 0; j < actual_count; j++){
			seek_pos = rand() % FILE_SIZE;
			assert(lseek(fd, seek_pos, SEEK_SET) == seek_pos);
			assert(read(fd, buf_ptr, buf_size) == buf_size);
		}
		time2 = get_realtime();
		printf("%.6f\n", time2 - time1);
		close(fd);
	}

	return 0;
}

