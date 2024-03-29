//
// request.c: Does the bulk of the work for the web server.
// 

#include "cs537.h"
#include "request.h"
#include "server.h"

void requestError(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg) 
{
    char buf[MAXLINE], body[MAXBUF];
    
    printf("Request ERROR\n");
    
    // Create the body of the error message
    sprintf(body, "<html><title>CS537 Error</title>");
    sprintf(body, "%s<body bgcolor=""fffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr>CS537 Web Server\r\n", body);
    
    // Write out the header information for this response
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    printf("%s", buf);
    
    sprintf(buf, "Content-Type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    printf("%s", buf);
    
    sprintf(buf, "Content-Length: %d\r\n\r\n", (int) strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    printf("%s", buf);
    
    // Write out the content
    Rio_writen(fd, body, strlen(body));
    printf("%s", body);
    
}


//
// Reads and discards everything up to an empty text line
//
void requestReadhdrs(rio_t *rp)
{
    char buf[MAXLINE];
    
    Rio_readlineb(rp, buf, MAXLINE);
    while (strcmp(buf, "\r\n")) {
        Rio_readlineb(rp, buf, MAXLINE);
    }
    return;
}

//
// Return 1 if static, 0 if dynamic content
// Calculates filename (and cgiargs, for dynamic) from uri
//
int requestParseURI(char *uri, char *filename, char *cgiargs) 
{
    char *ptr;
    
    if (!strstr(uri, "cgi")) {
        // static
        strcpy(cgiargs, "");
        sprintf(filename, ".%s", uri);
        if (uri[strlen(uri)-1] == '/') {
            strcat(filename, "home.html");
        }
        return 1;
    } else {
        // dynamic
        ptr = index(uri, '?');
        if (ptr) {
            strcpy(cgiargs, ptr+1);
            *ptr = '\0';
        } else {
            strcpy(cgiargs, "");
        }
        sprintf(filename, ".%s", uri);
        return 0;
    }
}

//
// Fills in the filetype given the filename
//
void requestGetFiletype(char *filename, char *filetype)
{
    if (strstr(filename, ".html")) 
        strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif")) 
        strcpy(filetype, "image/gif");
    else if (strstr(filename, ".jpg")) 
        strcpy(filetype, "image/jpeg");
    else 
        strcpy(filetype, "test/plain");
}

void requestServeDynamic(request_type request, char *filename, char *cgiargs, thread_info_type* thread_info)
{
        int fd = request.conn_fd;
    char buf[MAXLINE], *emptylist[] = {NULL};
    
    // The server does only a little bit of the header.  
    // The CGI script has to finish writing out the header.
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%s Server: Tiny Web Server\r\n", buf);
    
    /* CS537: Your statistics go here -- fill in the 0's with something useful! */

    sprintf(buf, "%s Stat-req-arrival: %d\r\n", buf, request.Stat_req_arrival);
    sprintf(buf, "%s Stat-req-dispatch: %d\r\n", buf, request.Stat_req_dispatch);
    sprintf(buf, "%s Stat-req-age: %d\r\n", buf, request.Stat_req_age);
    sprintf(buf, "%s Stat-thread-id: %d\r\n", buf, thread_info -> Stat_thread_id);
    sprintf(buf, "%s Stat-thread-count: %d\r\n", buf, thread_info -> Stat_thread_count);
    sprintf(buf, "%s Stat-thread-static: %d\r\n", buf, thread_info -> Stat_thread_static);
    sprintf(buf, "%s Stat-thread-dynamic: %d\r\n", buf, thread_info -> Stat_thread_dynamic);
    
    Rio_writen(fd, buf, strlen(buf));
    
    if (Fork() == 0) {
        /* Child process */
        Setenv("QUERY_STRING", cgiargs, 1);
        /* When the CGI process writes to stdout, it will instead go to the socket */
        Dup2(fd, STDOUT_FILENO);
        Execve(filename, emptylist, environ);
    }
    Wait(NULL);
}


void requestServeStatic(request_type request, char *filename, int filesize, thread_info_type* thread_info) 
{
    int fd = request.conn_fd;
    int srcfd;
    char *srcp, filetype[MAXLINE], buf[MAXBUF];
    char tmp = 0;
    int i;
    
    requestGetFiletype(filename, filetype);
    
    srcfd = Open(filename, O_RDONLY, 0);
    
    double read_start_time = GetTime();
    // Rather than call read() to read the file into memory, 
    // which would require that we allocate a buffer, we memory-map the file
    srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    Close(srcfd);
    
    // The following code is only needed to help you time the "read" given 
    // that the file is memory-mapped.  
    // This code ensures that the memory-mapped file is brought into memory 
    // from disk.
    
    // When you time this, you will see that the first time a client 
    //requests a file, the read is much slower than subsequent requests.
    for (i = 0; i < filesize; i++) {
        tmp += *(srcp + i);
    }
    double read_end_time = GetTime();
    request.Stat_req_read = read_end_time - read_start_time;

    double write_start_time = GetTime();
    request.Stat_req_complete = write_start_time - request.Stat_req_arrival;
    
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%s Server: CS537 Web Server\r\n", buf);
    
    // CS537: Your statistics go here -- fill in the 0's with something useful!
    sprintf(buf, "%s Stat-req-arrival: %d\r\n", buf, request.Stat_req_arrival);
    sprintf(buf, "%s Stat-req-dispatch: %d\r\n", buf, request.Stat_req_dispatch);
    sprintf(buf, "%s Stat-req-read: %d\r\n", buf, request.Stat_req_read);
    sprintf(buf, "%s Stat-req-complete: %d\r\n", buf, request.Stat_req_complete);
    sprintf(buf, "%s Stat-req-age: %d\r\n", buf, request.Stat_req_age);
    sprintf(buf, "%s Stat-thread-id: %d\r\n", buf, thread_info -> Stat_thread_id);
    sprintf(buf, "%s Stat-thread-count: %d\r\n", buf, thread_info -> Stat_thread_count);
    sprintf(buf, "%s Stat-thread-static: %d\r\n", buf, thread_info -> Stat_thread_static);
    sprintf(buf, "%s Stat-thread-dynamic: %d\r\n", buf, thread_info -> Stat_thread_dynamic);
    
    sprintf(buf, "%s Content-Length: %d\r\n", buf, filesize);
    sprintf(buf, "%s Content-Type: %s\r\n\r\n", buf, filetype);
    
    Rio_writen(fd, buf, strlen(buf));
    
    //  Writes out to the client socket the memory-mapped file 
    Rio_writen(fd, srcp, filesize);
    Munmap(srcp, filesize);

}

// handle a request
void requestHandle(request_type request, thread_info_type* thread_info)
{

    thread_info -> Stat_thread_count ++;
    if ( request.is_static) {
        thread_info -> Stat_thread_static ++;
        requestServeStatic(request, request.filename, request.sbuf.st_size, thread_info);
    } else {
        thread_info -> Stat_thread_dynamic ++;
            requestServeDynamic(request, request.filename, request.cgiargs, thread_info);
    }
}

// parse the request 
// the variable request.is_static is set to -1 if there is an error -- this
// means we don't need to put it in the queue for handling
request_type requestParse(request_type request)
{

    int fd = request.conn_fd;    
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, fd);
    Rio_readlineb(&rio, buf, MAXLINE);

    sscanf(buf, "%s %s %s", method, uri, version);
    
    printf("%s %s %s\n", method, uri, version);
    
    if (strcasecmp(method, "GET")) {
        requestError(fd, method, "501", "Not Implemented", 
                     "CS537 Server does not implement this method");
        request.is_static = -1;
        return request;
    }
    requestReadhdrs(&rio);

    is_static = requestParseURI(uri, filename, cgiargs);

    if (stat(filename, &sbuf) < 0) {
        requestError(fd, filename, "404", "Not found", "CS537 Server could not find this file");
        request.is_static = -1;
        return request;
    }
    
    if (is_static) {
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
            requestError(fd, filename, "403", "Forbidden", "CS537 Server could not read this file");
            request.is_static = -1;
            return request;
        }
    } else {
        if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
            requestError(fd, filename, "403", "Forbidden", "CS537 Server could not run this CGI program");
            request.is_static = -1;
            return request;
        }
    }

    // save relevant information for handling the request later
    strcpy( request.filename, filename );
    strcpy( request.cgiargs,  cgiargs  );
    request.sbuf       = sbuf;
    request.is_static  = is_static;
    request.file_size  = sbuf.st_size;

//  printf("   filename = %s,   request.filename = %s\n", filename, request.filename);
//  printf("   cgiargs  = %s,   request.cgiargs  = %s\n", cgiargs, request.cgiargs);

    return request;

}
