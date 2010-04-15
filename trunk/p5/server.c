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


/*
   int main(int argc, char *argv[])
   {
   int listenfd, connfd, port, clientlen;
   struct sockaddr_in clientaddr;

   getargs(&port, argc, argv);

// 
// CS537: Create some threads...
//

listenfd = Open_listenfd(port);
while (1) 
{
clientlen = sizeof(clientaddr);
connfd = Accept(listenfd, (SA *)&clientaddr, (socklen_t *) &clientlen);

// 
// CS537: In general, don't handle the request in the main thread.
// Save the relevant info in a buffer and have one of the worker threads 
// do the work.
// 
requestHandle(connfd);

Close(connfd);
}

}
 */
