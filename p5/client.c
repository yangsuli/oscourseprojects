/*
 * client.c: A very, very primitive HTTP client.
 * 
 * To run, try: 
 *      client www.cs.wisc.edu 80 /
 *
 * Sends one HTTP request to the specified HTTP server.
 * Prints out the HTTP response.
 *
 * CS537: For testing your server, you will want to modify this client.  
 * For example:
 * 
 * You may want to make this multi-threaded so that you can 
 * send many requests simultaneously to the server.
 *
 * You may also want to be able to request different URIs; 
 * you may want to get more URIs from the command line 
 * or read the list from a file. 
 *
 * When we test your server, we will be using modifications to this client.
 *
 *  Example of using this is the following -- assuming server is running on
 *  port N
 *
 *  ./client localhost N /output.cgi; ./client localhost N /output.cgi
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
    while (n > 0) {
        printf("%s", buf);
        n = Rio_readlineb(&rio, buf, MAXBUF);
    }
}

// create a bunch of threads that all make the same identical request to the
// server
void * my_client( void * arg ) {

    char ** argv = (char**) arg;

    char *host, *filename;
    int port;
    int clientfd;

    host = argv[1];
    port = atoi(argv[2]);
    filename = argv[3];

    clientfd = Open_clientfd(host, port);
    clientSend(clientfd, filename);  // this is bad?  race for filename??
    clientPrint(clientfd);  // this is bad?
    Close(clientfd);
    return NULL;
}

int main(int argc, char *argv[])
{

    if (argc != 5) {
        fprintf(stderr, "Usage: %s <host> <port> <filename> <num_threads>\n", argv[0]);
        exit(1);
    }
    char *host, *filename;
    int port;
//  int clientfd;

    host = argv[1];
    port = atoi(argv[2]);
    filename = argv[3];


    int num_threads = atoi(argv[4]);
    assert( num_threads <= 500 );

    /* Open a single connection to the specified host and port */
//  clientfd = Open_clientfd(host, port);
//  clientSend(clientfd, filename);
//  clientPrint(clientfd);
//  Close(clientfd);

    pthread_t threads[500];
    int i = 0;
    for( i = 0; i < num_threads; i++ ) {
        Pthread_create(&threads[i], NULL,&my_client, (void*)argv);
    }

    // join all the threads ...
    for( i = 0; i < num_threads; i++) {
        pthread_join( threads[i], NULL );
    }

    return 0;

}
