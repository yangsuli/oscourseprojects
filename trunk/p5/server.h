#ifndef __SERVER_H__
#define __SERVER_H__
#define MAX_STR_SIZE 256

typedef struct __request_type{
	int conn_fd;

    // every field that starts with Stat has to do with collecting statistics
	double Stat_req_arrival;
	double Stat_req_dispatch;
	double Stat_req_read;
	double Stat_req_complete;
	double Stat_req_age;

    // scheduling policy fields
    unsigned int file_size;
    unsigned int epoch_num;

    // everything used in parsing arguments
    int fd;
    int is_static;
    struct stat sbuf;
    char filename[MAXLINE], cgiargs[MAXLINE];

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
