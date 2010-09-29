#include "hw1.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sched.h>
#include <stdlib.h>

#define SECTOR_SIZE 512
#define SECTORS_PER_TRACK 63
#define TRACK_SIZE SECTORS_PER_TRACK*SECTOR_SIZE
#define HEADS 16 //TODO: ?
#define CYLINDER_SIZE TRACK_SIZE*HEADS
#define CYLINDERS 60801

//Disk Info:
//Nominal Media Rotation Rate: 5400
//cache/buffer size = 8192 KBytes

#define BUFSIZE SECTOR_SIZE * 2
#define SEEK_TIME 100
#define ROTATION_TIME 100
//#define SEEK_SIZE CYLINDER_SIZE*CYLINDERS/(SEEK_TIME + 10)
#define SEEK_SIZE CYLINDER_SIZE*1000

/*
   potential problems:
   1. hard disk drive cache
   2. other overhead (sys call, trans rate etc.)
   3. bus contention/ other transmission time
   4. acceleartion, costing, settling simplified
   5. skew parameters (rotational delay)
 */


int main(){
	struct sched_param param;
	int fd;
	double time1, time2, time3, time4;
	double seek_time, total_time, rotation_time, rotation_time2;
	double time[SEEK_TIME];
	cpu_set_t run_set;
	void *buf_ptr = valloc(SECTOR_SIZE);
	assert(buf_ptr != NULL);
	int i;

	//disable look-ahead cache
	assert(system("hdparm -A0 /dev/sda") == 0);

	CPU_ZERO(&run_set);
	CPU_SET(0,&run_set);
	assert(sched_setaffinity(0,sizeof(cpu_set_t),&run_set) == 0);
	assert(sched_getparam(0,&param) == 0);
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	assert(sched_setscheduler(0,SCHED_FIFO,&param) == 0);
	
	get_time_offset();
	assert((fd = open("/dev/sda", O_RDONLY|O_DIRECT)) >= 0);
	assert(lseek64(fd, CYLINDER_SIZE*100, SEEK_SET) > 0);
	assert(read(fd,buf_ptr,SECTOR_SIZE) == SECTOR_SIZE);

	//measure rotation time
	time3 = get_time();
	for(i = 0; i < ROTATION_TIME; i++){
		time1 = get_time();
		assert(lseek64(fd,-SECTOR_SIZE,SEEK_CUR) > 0);
		assert(read(fd,buf_ptr,SECTOR_SIZE) == SECTOR_SIZE);
		time2 = get_time();
		time[i] = time2 - time1;
	}
	time4 = get_time();

	total_time = time4 - time3;
	rotation_time = total_time/ROTATION_TIME; 


	fprintf(stdout,"rotation average: %f\n", rotation_time);
	
	time3 = get_time();
	for(i = 0; i < SEEK_TIME; i++){
		time1 = get_time();
		assert(lseek64(fd,SEEK_SIZE,SEEK_CUR) > 0);
		assert(read(fd,buf_ptr,SECTOR_SIZE) == SECTOR_SIZE);
		time2 = get_time();
		time[i] = time2-time1;
	}
	time4 = get_time();

	total_time = time4 - time3;
	seek_time = total_time/SEEK_TIME;


	for(i=0; i < SEEK_TIME; i++){
		fprintf(stdout,"%f\n",time[i]);
	}
	fprintf(stdout,"average: %f\n", seek_time);

	close(fd);
	free(buf_ptr);
	//enable look-ahead cache
	system("hdparm -A1 /dev/sda");
	return 0;
}

