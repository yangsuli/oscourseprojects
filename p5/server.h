
#define MAXSIZE 256

typedef struct __request_type{
	int conn_fd;
} request_type;


void put_in_buffer(request_type request);

request_type get_from_buffer();
