#include "mytime.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define BUF_SIZE 4096
#define MAX_TRY 64

int main(){
	int fd;
	int num_block;
	double time1, time2;
	cpu_set_t run_set;
	struct sched_param param;
	void *buf_ptr = valloc(BUF_SIZE);
	assert(buf_ptr != NULL);

	system("rm -f indirect_file");
	system("hdparm -W0 /dev/sda");
	assert(system("sync;echo 3 > /proc/sys/vm/drop_caches") == 0);

	//attach to one cpu and have the highest priority so that it doesn't get scheduled out
	CPU_ZERO(&run_set);
	CPU_SET(0, &run_set);
	assert(sched_setaffinity(0,sizeof(cpu_set_t),&run_set) == 0);
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	assert(sched_setscheduler(0,SCHED_FIFO,&param) == 0);

	get_realtime_offset();

	fd = open("indirect_file", O_RDWR|O_CREAT|O_SYNC);
	assert(fd >= 0);


	for(num_block = 1; num_block <= MAX_TRY; num_block++){
		time1 = get_realtime();
		assert(write(fd, buf_ptr, BUF_SIZE) == BUF_SIZE);
		assert(fsync(fd) == 0);
		time2 = get_realtime();
		printf("%d %.3f\n", num_block, time2 - time1);
		usleep(10000);
	}

	close(fd);
}
		


