#include "hw1.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sched.h>

#define BUFSIZE 1024*1024*100 //100M
#define SECTOR_SIZE 512
#define SECTORS_PER_TRACK 63
#define TRACK_SIZE SECTORS_PER_TRACK*SECTOR_SIZE
#define HEADS 255
#define CYLINDER_SIZE TRACK_SIZE*HEADS
//TODO UNITS??

char buf[BUFSIZE];

int main(){
	struct sched_param param;
	int fd;
	double time1, time2;
	double seek_time;
	cpu_set_t run_set;

	CPU_ZERO(&run_set);
	CPU_SET(0,&run_set);
	assert(sched_setaffinity(0,sizeof(cpu_set_t),&run_set) == 0);
	assert(sched_getparam(0,&param) == 0);
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	assert(sched_setscheduler(0,SCHED_FIFO,&param) == 0);


	assert((fd = open("/dev/sda", O_RDONLY|O_DIRECT)) >= 0);
        get_time_offset();

	fprintf(stdout,"%d\n",lseek(fd, 0, SEEK_SET));
	time1 = get_time();
	fprintf(stdout,"%d\n",lseek(fd, 4096*1000, SEEK_CUR));
	time2 = get_time();
	//assert(read(fd,buf,1024*1024*100) == 1024*1024*100);
	fprintf(stdout,"%d %d %d\n", read(fd,buf,SECTOR_SIZE), errno, EINVAL);

	seek_time = time2-time1;

	fprintf(stdout,"%f\n", seek_time);

	close(fd);
	return 0;
}

