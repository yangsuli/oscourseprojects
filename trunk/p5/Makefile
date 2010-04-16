#
# To compile, type "make" or make "all"
# To remove files, type "make clean"
#
OBJS = server.o request.o cs537.o
TARGET = server

CC = gcc
CFLAGS = -g -Wall

LIB_FLAG = -lpthread
#LIBS     = -lpthread  # i don't like this name...
LIBS     = -lpthread -ggdb

.SUFFIXES: .c .o 

all: server client simple_client output.cgi

server: server.o request.o cs537.o
	$(CC) $(CFLAGS) -o server server.o request.o cs537.o $(LIBS)

client: client.o cs537.o
	$(CC) $(CFLAGS) -o client client.o cs537.o $(LIBS)

simple_client: simple_client.o cs537.o
	$(CC) $(CFLAGS) -o  simple_client simple_client.o cs537.o $(LIBS)

output.cgi: output.c
	$(CC) $(CFLAGS) -o output.cgi output.c $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

#clean:
#	-rm -f $(OBJS) server client output.cgi
clean:
	-rm -f *.o server client output.cgi tags

tags:
	ctags *.c *.h

