#include "mytime.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sched.h>
#include <stdlib.h>

#define _LARGEFILE64_SOURCE
#define BUF_SIZE 4096

//Directly access disk
//See what the latency will be in the presence of disk cache

int main(){
	int fd;
	double time1, time2;
	int i;
	void *buf_ptr = valloc(BUF_SIZE);
	assert(buf_ptr != NULL);

	get_time_offset();

	assert((fd = open("/dev/sda", O_RDONLY|O_DIRECT)) >= 0);
	time1 = get_time();
	for( i = 0; i < 100; i++){
		//assert(lseek64(fd, rand()% 10737418240, SEEK_SET) > 0);
		assert(lseek64(fd, (rand()% 153741)*BUF_SIZE, SEEK_CUR) >= 0);
		assert(read(fd, buf_ptr, BUF_SIZE) == BUF_SIZE);
	}
	time2 = get_time();

	printf("direct access disk time: %.3f", (time2 - time1)/100);

	close(fd);
	return 0;
}
