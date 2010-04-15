#ifndef __SERVER_H__
#define __SERVER_H__
#define MAXSIZE 256

typedef struct __request_type{
	int conn_fd;
	double Stat_req_arrival;
	double Stat_req_dispatch;
	double Stat_req_read;
	double Stat_req_complete;
	double Stat_req_age;
} request_type;

typedef struct __thread_info{
	pthread_t tid;
	int Stat_thread_id;
	int Stat_thread_count;
	int Stat_thread_static;
	int Stat_thread_dynamic;
} thread_info_type;


void put_in_buffer(request_type request);

request_type get_from_buffer();
double GetTime();

#endif
