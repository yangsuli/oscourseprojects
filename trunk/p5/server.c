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

int num_filled = 0;             // number of requests sitting in buffer
int total_num_filled = 0;       // total number of requests served
int new_epoch  = 0;             // flag to indicate a new epoch
int N;                          // epoch division
pthread_cond_t empty, full;     // condition variables for producer/consumer
pthread_mutex_t mutex;          // lock for modifiying buffer atomically
request_type * buffer_ptr;      // pool of requests
int * in_use;                   // size of request.  == 0 if not in use
thread_info_type * threads_ptr; // array of all the threads

// policy chosen: 0 == FIFO : 1 == SFF : 2 == SFF-BS
int policy_int = -1; 

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

    // check for positivity
    if( *num_threads < 1 || *buffer_size < 1 )
    {
        fprintf(stderr, "Usage: %s [portnum] [threads] [buffers] [schedalg] [N  (for SFF-BS only)]\n", argv[0]);
        fprintf(stderr,"  num_threads = %d,  buffer_size = %d\n", *num_threads, *buffer_size );
        fprintf(stderr, "num_threads and buffer_size should be positive\n");
        exit(1);
    }


    // strncpy is safer than strcpy in case user supplies VERY large argument 
    strncpy(*policy_ptr, argv[4], MAX_STR_SIZE);  

    if(strcasecmp(*policy_ptr,"SFF-BS") == 0){
        if(argc != 6){
            fprintf(stderr, "Usage: %s [portnum] [threads] [buffers] [schedalg] [N  (for SFF-BS only)]\n", argv[0]);
            exit(1);
        }
        *N = atoi(argv[5]);
        // check for positivity
        if( !( *N > 0) ) {
            fprintf(stderr, "Usage: %s [portnum] [threads] [buffers] [schedalg] [N  (for SFF-BS only)]\n", argv[0]);
            fprintf(stderr, "N should be positive\n");
            exit(1);
        }
        policy_int = 2;
    }else if(strcasecmp(*policy_ptr,"SFF") == 0 ) {
        if(argc != 5){
            fprintf(stderr, "Usage: %s [portnum] [threads] [buffers] [schedalg] [N  (for SFF-BS only)]\n", argv[0]);
            exit(1);
        }
        policy_int = 1;
    }else if(strcasecmp(*policy_ptr, "FIFO") == 0){
        if(argc != 5){
            fprintf(stderr, "Usage: %s [portnum] [threads] [buffers] [schedalg] [N  (for SFF-BS only)]\n", argv[0]);
            exit(1);
        }
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
        if( new_epoch && num_filled == 0 ){ new_epoch = 0; }
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
    getargs(&port,&threads,&buffers,policy_ptr,&N,argc, argv);

    // buffers is a bad name, we'll use buffer_size
    // nmbr of request connections that can be accepted at one time. 
    buffer_size = buffers;  

    // number of worker threads
    num_threads = threads;

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
        while(num_filled == buffer_size || new_epoch ){
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
    use = (use+1) % buffer_size;
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

    // find first free spot
    int i = 0;
    while( in_use[i] ){ i++; }
    return i;
}

// selects index of array to read from the buffer.
int get_sff_use_index() {

    // find the first available index
    int i = 0;
    while( !in_use[i] ){
printf("  in_use[i] = %d\n", in_use[i] );
        i++;
    }

    int use = i;
    int curr_size = in_use[i];
int debug_count = 1;  // we will always fine one candidate here!

    // check all the other free locations
printf("   curr_size = %d\n", curr_size );
    for( i = i + 1; i < buffer_size; i++ ) {
printf("  in_use[i] = %d\n", in_use[i] );
        // if file size is smaller ...
        if( in_use[i] > 0 && in_use[i] < curr_size ) {
            use = i;
            curr_size = in_use[i];
printf("   curr_size = %d\n", curr_size );
        }
        if( in_use[i] > 0 ){ debug_count++; }
        i++;
    }
printf(" found %d files in use\n", debug_count ); 
    return use;

}

void put_in_buffer(request_type request){

    int fill = -1;

    request = requestParse( request );

    if( request.is_static == -1 ) 
    {
        // one of the standard errors occured while parsing arguments -- no
        // need to put this in the shared buffer
//      printf("  found an error, is_static is set to -1\n");
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

        case 2:
        fill = get_sff_fill_index();

        // check for new epoch
        if( (++total_num_filled % N) == 0 )
        { new_epoch = 1; }
       
        break;

        default:
        unix_error("this scheduling policy is not implemented\n");
    }
//printf("  fill = %d\n", fill);
    buffer_ptr[fill] = request;
    in_use[fill]     = request.file_size;
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

        case 2:
        use = get_sff_use_index();
        break;

        default:
        unix_error("this scheduling policy is not implemented\n");
    }
        
    request_type tmp = buffer_ptr[use];
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
