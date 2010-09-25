#include <sched.h>
#include <sys/time.h>
#include <assert.h>


int main(){
	struct sched_param param;
	asse
	if(sched_setscheduler(0, SCHED_FIFO,
