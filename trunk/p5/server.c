#include "cs537.h"
#include "request.h"
#include "server.h"
#include <sys/time.h>
#include <assert.h>

// 
// server.c: A very, very simple web server
//
// To run:
//  server [portnum] (above 2000) [threads] [buffers] [schedalg] [N  (for SFF-BS only)]
//
// Repeatedly handles HTTP requests sent to this port number.
// Most of the work is done within routines written in request.c
//

int num_filled = 0;                // number of requests sitting in buffer
pthread_cond_t empty, full;
pthread_mutex_t mutex;             // lock for modifiying buffer atomically
request_type * buffer_ptr;         // pool of requests
int * in_use;                      // indicates if location in buffer is inuse
thread_info_type * threads_ptr;
int policy_int;                    // policy chosen: 0 == FIFO

int buffer_size;// nmbr of request connections that can be accptd at one time. 
int num_threads;// number of worker threads

// routine for parsing arguments
void getargs(int *port, int *num_threads,int *buffer_size, char **policy_ptr, 
                int *N , int argc, char *argv[])
{
    if (argc != 5 && argc != 6) 
    {
        fprintf(stderr, "Usage: %s [portnum] [threads] [buffers] [schedalg] [N  (for SFF-BS only)]\n", argv[0]);
        exit(1);
    }
    *port = atoi(argv[1]);
    *num_threads = atoi(argv[2]);
    *buffer_size = atoi(argv[3]);

    // strncpy is safer than strcpy in case user supplies VERY large argument 
    strncpy(*policy_ptr, argv[4], MAX_STR_SIZE);  

    // check for positivity
    if( *num_threads < 1 || *buffer_size < 1 )
    {
        fprintf(stderr, "Usage: %s [portnum] [threads] [buffers] [schedalg] [N  (for SFF-BS only)]\n", argv[0]);
        fprintf(stderr, "num_threads and buffer_size should be positive\n");
        exit(1);
    }

    if(strcasecmp(*policy_ptr,"SFF-BS") == 0){
        if(argc != 6){
            fprintf(stderr, "Usage: %s [portnum] [threads] [buffers] [schedalg] [N  (for SFF-BS only)]\n", argv[0]);
            exit(1);
        }
        *N = atoi(argv[5]);
        policy_int = 2;
    }else if(strcasecmp(*policy_ptr,"SFF") == 0 ) {
        if(argc != 5){
            fprintf(stderr, "Usage: %s [portnum] [threads] [buffers] [schedalg] [N  (for SFF-BS only)]\n", argv[0]);
            exit(1);
        }
        *N = 0;
        policy_int = 1;
    }else if(strcasecmp(*policy_ptr, "FIFO") == 0){
        if(argc != 5){
            fprintf(stderr, "Usage: %s [portnum] [threads] [buffers] [schedalg] [N  (for SFF-BS only)]\n", argv[0]);
            exit(1);
        }
        *N = 0;
        policy_int = 0;

    }else{
        fprintf(stderr, "policy has to be FIFO, SFF, or SFF-BS\n");
        exit(1);
    }
}

// worker threads live here
void * worker(void *arg){

    // find and save the stat_tid "thread id" of the current thread
    // this is executed one time only
    int stat_tid = 0;
    while(1)
    {
        if(pthread_equal(pthread_self(),threads_ptr[stat_tid].tid) != 0){
            break;
        }
        stat_tid = (stat_tid+1) % num_threads;
    }
    threads_ptr[stat_tid].Stat_thread_id = stat_tid;  

    // workers will never leave this while loop
    while(1){
        Pthread_mutex_lock(&mutex);
        while(num_filled == 0){
            Pthread_cond_wait(&full,&mutex);
        }

        // read a single request from the buffer
        request_type curr_request = get_from_buffer();

        // finished reading from buffer, so wake other threads
        Pthread_cond_signal(&empty);
        Pthread_mutex_unlock(&mutex);

        // do the work requested from curr_request
        int connfd = curr_request.conn_fd;
        double time_picked = GetTime();
        curr_request.Stat_req_dispatch = time_picked - curr_request.Stat_req_arrival;
        requestHandle(curr_request,&threads_ptr[stat_tid]);
        Close(connfd);
    }

}

int main(int argc, char *argv[]) {

    int listenfd, connfd, clientlen;
    struct sockaddr_in clientaddr;

    ///// parse the arguments  /////
    int port, threads, buffers, i;
    char  policy[MAX_STR_SIZE];
    char * p = policy;
    char **policy_ptr = &p;
    int N;
    getargs(&port,&threads,&buffers,policy_ptr,&N,argc, argv);

    // buffers is a bad name, we'll use buffer_size
    // nmbr of request connections that can be accepted at one time. 
    buffer_size = buffers;  

    // number of worker threads
    num_threads = threads;

    // TODO -- replace with a linked list or some other data structure 
    // (need somethine else for SFF queuing)
    buffer_ptr = (request_type *)malloc(sizeof(request_type) * buffer_size);
    if(buffer_ptr == NULL){ unix_error("malloc error\n"); }

    in_use     = (int *)malloc(sizeof(int) * buffer_size);
    if(in_use == NULL){ unix_error("malloc error\n"); }
    for(i = 0; i <= buffer_size; i++ ){
        in_use[i] = 0;  // initially nothing is 'in use'
    }

    threads_ptr = 
            (thread_info_type *) malloc(sizeof(thread_info_type) * threads);
    if(threads_ptr == NULL){ unix_error("malloc error\n"); }

    // Create threads and initialize global condition variables and single
    // lock needed for solving producer/consumer problem
    Pthread_cond_init( &empty, NULL);
    Pthread_cond_init( &full,  NULL);
    Pthread_mutex_init(&mutex, NULL);
    for( i = 0; i < threads; i++){
        threads_ptr[i].Stat_thread_count   = 0;
        threads_ptr[i].Stat_thread_static  = 0;
        threads_ptr[i].Stat_thread_dynamic = 0;

        // this should be performed last ...
        Pthread_create(&(threads_ptr[i].tid),NULL, worker,NULL);
    }
    listenfd = Open_listenfd(port);  // open port

    while (1) {

        // grab a request
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *)&clientaddr, (socklen_t *) &clientlen);

        request_type curr_request;
        curr_request.conn_fd = connfd;
        curr_request.Stat_req_arrival = GetTime();

        ///////////////////////////////////////////////////////////////////////
        // add work to the buffer for a worker to handle
        ///////////////////////////////////////////////////////////////////////
        Pthread_mutex_lock(&mutex);
        while(num_filled == buffer_size){
            Pthread_cond_wait(&empty, &mutex);
        }
        put_in_buffer(curr_request);   
        
        // finished working on the buffer, so free for other
        // producers/consumers to modify
        // TODO -- do we need the condition variable "full" since there is only
        // one producer?  probably....
        Pthread_cond_signal(&full);
        Pthread_mutex_unlock(&mutex);
    }

}

// selects index of array to read from the buffer.
int get_fifo_use_index() {
    static int use = 0;
    int tmp = use;
    use = (use+1) % num_threads;
    return tmp;
}


// returns index that should be filled for the fifo scheduling policy
int get_fifo_fill_index(){

    static int fill = 0;
    int tmp = fill;
    fill = (fill + 1)%buffer_size;  // forced FIFO queue here
    return tmp;
}

int get_sff_fill_index(){

    int i = 0;

    // find first free spot and place it there
    for( i = 0; in_use[i]; i++){;}
    return i;
}

// selects index of array to read from the buffer.
int get_sff_use_index() {

    // find the first available index
    int i = 0;
    for( i = 0; !in_use[i]; i++){;}
    int use = i;

    // check all the other free locations
    while( i < num_threads ) {
        // if file size is smaller ...
        if( 0 ) {
            use = i;
        }
        i++;
    }
    
    return use;

}

void put_in_buffer(request_type request){

    int fill = -1;

    request = requestParse( request );
    if( request.is_static == -1 ) // error occured!
    {
        return;
    }

    switch( policy_int )
    {
        case 0:
        fill = get_fifo_fill_index();
        break;

        case 1:
        fill = get_sff_fill_index();
        break;

        default:
        unix_error("this scheduling policy is not implemented\n");
    }

    buffer_ptr[fill] = request;
    in_use[fill] = 1;
    num_filled++;

}

request_type get_from_buffer(){

    int use = -1;

    switch( policy_int )
    {
        case 0:
        use = get_fifo_use_index();
        break;

        case 1:
        use = get_sff_use_index();
        break;

        default:
        unix_error("this scheduling policy is not implemented\n");
    }
        
    request_type tmp = buffer_ptr[use];  //TODO
    in_use[use] = 0;
    num_filled--;
    return tmp;
}

// simple time function
double GetTime(){
    struct timeval t;
    int rc = gettimeofday(&t,NULL);
    assert(rc==0);
    return t.tv_sec + t.tv_usec/1e6;
}
