#include "hw1.h"
#include <stdio.h>
#include <fcntl.h>

char buf[1024*1024*100];

int main(){
	int fd;
	double time1, time2, time3, time4;
	double seek_time, rotate_time;

	assert((fd = open("/dev/sda2", O_RDONLY|O_DIRECT)) >= 0);
        
        get_time_offset();
	lseek(fd, 0, SEEK_SET);
	time1 = get_time();
	lseek(fd, 4096*1000, SEEK_CUR);
	time2 = get_time();
	//assert(read(fd,buf,1024*1024*100) == 1024*1024*100);
	fprintf(stdout,"%d\n", read(fd,buf,1024*1024*100));
	time3 = get_time();

	seek_time = time2-time1;
	rotate_time = time3-time2;

	fprintf(stdout,"%f\n%f\n", seek_time, rotate_time);

	close(fd);
	return 0;
}

