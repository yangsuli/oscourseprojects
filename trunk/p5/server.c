#include "cs537.h"
#include "request.h"

// 
// server.c: A very, very simple web server
//
// To run:
//  server <portnum (above 2000)>
//
// Repeatedly handles HTTP requests sent to this port number.
// Most of the work is done within routines written in request.c
//

//
// CS537: Parse the new arguments too
//

#define MAXSIZE 256

int num_filled = 0;
pthread_cond_t empty, full;
pthread_mutex_t mutex;
request_type * buffer_ptr;
pthread_t * threads_ptr;
int fill = 0;
int use = 0;
int buffer_size;

typedef __request_type{
	int conn_fd;
} request_type;


void getargs(int *port, int *num_threads,int *buffer_size, char **policy_ptr, int *N , int argc, char *argv[])
{
    if (argc != 5 && argc != 6) 
    {
        //      fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        fprintf(stderr, "Usage: %s [portnum] [threads] [buffers] [schedalg] [N  (for SFF-BS only)]\n", argv[0]);

        exit(1);
    }
    *port = atoi(argv[1]);
    *num_threads = atoi(argv[2]);
    *buffer_size = atoi(argv[3]);
    strcpy(*policy_ptr, argv[4]);

    if(strcasecmp(*policy_ptr,"SFF-BS") == 0){
        if(argc != 6){
             fprintf(stderr, "Usage: %s [portnum] [threads] [buffers] [schedalg] [N  (for SFF-BS only)]\n", argv[0]);
            exit(1);
        }
        *N = atoi(argv[5]);
    }else if(strcasecmp(*policy_ptr,"SFF") == 0 || strcasecmp(*policy_ptr, "FIFO") == 0){
        if(argc != 5){
              fprintf(stderr, "Usage: %s [portnum] [threads] [buffers] [schedalg] [N  (for SFF-BS only)]\n", argv[0]);
             exit(1);
        }
        *N = 0;
    }else{
        fprintf(stderr, "policy has to be FIFO, SFF, or SFF-BS\n");
        exit(1);
    }
}

///////////  test argument stuff ////
/*
int main(int argc, char *argv[]){
    int port, threads, buffers;
    char  policy[MAXSIZE];
    char * p = policy;
    char **policy_ptr = &p;
    int N;

    getargs(&port,&threads,&buffers,policy_ptr,&N,argc, argv);

    fprintf(stdout,"%d, %d, %d, %s, %d\n",port, threads, buffers, policy, N);

    return 0;
}
*/

int main(int argc, char *argv[])
{
    int listenfd, connfd, clientlen;
    struct sockaddr_in clientaddr;

    ///// parse the arguments  /////
    int port, threads, buffers;
    char  policy[MAXSIZE];
    char * p = policy;
    char **policy_ptr = &p;
    int N;
    getargs(&port,&threads,&buffers,policy_ptr,&N,argc, argv);

    buffer_size = buffers;

    buffer_ptr = (request_type *)malloc(sizeof(request_type) * buffers);
    if(buffer_ptr == NULL){
	    unix_error("malloc error\n");
    }

    threads_ptr = (pthread_t *) malloc(sizeof(pthread_t) * threads);
    if(threads_ptr == NULL){
	    unix_error("mallock error\n");
    }

    int i;
    for( i = 0; i < threads; i++){
	    Pthread_create(&threads_ptr[i],NULL, worker,NULL);
    }

 //   pthread_cond_t empty, full;
 //   pthread_mutex_t mutex;

    Pthread_cond_init(&empty, NULL);
    Pthread_cond_init(&full,NULL);
    Pthread_mutex_init(&mutex,NULL);

    listenfd = Open_listenfd(port);

    // 
    // CS537: Create some threads...
    //

    while (1) 
    {

        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, (socklen_t *) &clientlen);

        // 
        // CS537: In general, don't handle the request in the main thread.
        // Save the relevant info in a buffer and have one of the worker threads 
        // do the work.
        // 
	
	request_type curr_request;
	curr_request.conn_fd = connfd;

	Pthread_mutex_lock(&mutex);
	while(num_filled == buffers){
		Pthread_cond_wait(&empty, &mutex);
	}
	put_in_buffer(curr_request);
	Pthread_cond_signal(&fill);
	Pthread_mutex_unlock(&mutex);
/*
    worker should handle the request
        requestHandle(connfd);

        Close(connfd);

	*/
    }

}


void put_in_buffer(request_type request){
	buffer[fill] = request;
	fill = (fill + 1)%buffer_size;
	numfilled++;
}

request_type get_from_buffer(){
	request_type tmp = buffer[use];
	use = (use + 1) % MAX;
	numfilled--;
	return tmp;



