/*
 * client1.c: A modified version of client.c
 *
 * Runs two different types of requests to the server simultaneously.  If it
 * crashes, it's your fault for not giving good parameters.
 * 
 * Example:
 *
 * ./client1 localhost 5111 /testdata/file-sff-large.txt 3 /testdata/file-sff-small.txt 1
 *
 */

#include <assert.h>
#include "cs537.h"

/*
 * Send an HTTP request for the specified file 
 */
void clientSend(int fd, char *filename)
{
    char buf[MAXLINE];
    char hostname[MAXLINE];

    Gethostname(hostname, MAXLINE);

    /* Form and send the HTTP request */
    sprintf(buf, "GET %s HTTP/1.1\n", filename);
    sprintf(buf, "%shost: %s\n\r\n", buf, hostname);
    Rio_writen(fd, buf, strlen(buf));
}

/*
 * Read the HTTP response and print it out
 */
void clientPrint(int fd)
{
    rio_t rio;
    char buf[MAXBUF];  
    int length = 0;
    int n;

    Rio_readinitb(&rio, fd);

    /* Read and display the HTTP Header */
    n = Rio_readlineb(&rio, buf, MAXBUF);
    while (strcmp(buf, "\r\n") && (n > 0)) {
        printf("Header: %s", buf);
        n = Rio_readlineb(&rio, buf, MAXBUF);

        /* If you want to look for certain HTTP tags... */
        if (sscanf(buf, "Content-Length: %d ", &length) == 1) {
            printf("Length = %d\n", length);
        }
    }

    /* Read and display the HTTP Body */
    n = Rio_readlineb(&rio, buf, MAXBUF);
    printf("%c\n",buf[0]);  // print only the first line...
    while (n > 0) {
//      printf("%s", buf);
        n = Rio_readlineb(&rio, buf, MAXBUF);
    }
}

// create a bunch of threads that all make the same identical request to the
// server
void * my_client1( void * arg ) {

    char ** argv = (char**) arg;

    char *host, *filename;
    int port;
    int clientfd;

    host = argv[1];
    port = atoi(argv[2]);
    filename  = argv[3];

    clientfd = Open_clientfd(host, port);
    clientSend(clientfd, filename);  // this is bad?  race for filename??
    clientPrint(clientfd);  // this is bad?
    Close(clientfd);
    return NULL;
}

// create a bunch of threads that all make the same identical request to the
// server
void * my_client2( void * arg ) {

    char ** argv = (char**) arg;

    char *host, *filename;
    int port;
    int clientfd;

    host = argv[1];
    port = atoi(argv[2]);
    filename = argv[5];

    clientfd = Open_clientfd(host, port);
    clientSend(clientfd, filename);
    clientPrint(clientfd);
    Close(clientfd);
    return NULL;
}
int main(int argc, char *argv[])
{

    if (argc != 7) {
        fprintf(stderr, "Usage: %s <host> <port> <filename1> <num_threads1> <filename2> <num_threads2>\n", argv[0]);
        exit(1);
    }

    int num_threads1 = atoi(argv[4]);
    int num_threads2 = atoi(argv[6]);
    int num_threads  = num_threads1 + num_threads2;
    assert( num_threads <= 500 );
    assert( num_threads1 > 0 );
    assert( num_threads2 > 0 );

    pthread_t threads[500];
    int i = 0;
    for( i = 0; i < num_threads1; i++ ) {
        Pthread_create(&threads[i], NULL,&my_client1, (void*)argv);
    }

    while( i < num_threads )
    {
        Pthread_create(&threads[i], NULL,&my_client2, (void*)argv);
        i++;
    }

    // join all the threads ...
    for( i = 0; i < num_threads1 + num_threads2; i++) {
        pthread_join( threads[i], NULL );
    }

    return 0;

}
