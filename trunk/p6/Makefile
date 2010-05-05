CC   = gcc
# Useful opts are -Wall, -ggdb, ...
OPTS = -Wall -ggdb

ALL_SERVER_SOURCES = server.c udp.c mssg.c
ALL_CLIENT_SOURCES = client.c udp.c mssg.c
ALL_TEST_MSSG_SOURCES = testmssg.c mssg.c

SERVER_OBJS = server.o udp.o mssg.o
CLIENT_OBJS = client.o udp.o mssg.o
TEST_MSSG_OBJS = mssg.o testmssg.o

ALL_LIB_SOURCES = $(ALL_SERVER_SOURCES) $(ALL_CLIENT_SOURCES)


TEST = testcases/test6.c
TEST = testmssg.c

#all: server client
all: client server

test: $(TEST) all
	gcc -Wall -ggdb -c $(TEST) -o testclient.o
	gcc -ggdb -o testclient testclient.o udp.o -L. -lmfs

#client: $(ALL_CLIENT_SOURCES)
#	gcc -c -fPIC $(ALL_CLIENT_SOURCES) ;
#	gcc -shared -o libmfs.so $(CLIENT_OBJS)

# this section works!
client: $(ALL_CLIENT_SOURCES)
	gcc -c -g -fPIC client.c mssg.c udp.c ;
	gcc -shared -o libmfs.so client.o mssg.o udp.o

#client: $(ALL_CLIENT_SOURCES)
#	$(CC) -c -fPIC $(ALL_CLIENT_SOURCES);
#	$(CC) -shared -o -libmfss.so $(CLIENT_OBJS)

server: $(ALL_SERVER_SOURCES)
	$(CC) $(OPTS) -o server $(ALL_SERVER_SOURCES)

#	gcc -c -g -fpic $(ALL_LIB_SOURCES);
#	gcc -shared -g -o liblist.so $(ALL_LIB_OBJECTS);
test_mssg: $(TEST_MSSG_OBJS)
	$(CC) -o test_mssg $(TEST_MSSG_OBJS)

# this is a generic rule for .o files 
#%.o: %.c 
#	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -f *.o *.so server test_mssg

tags: $(ALL_LIB_SOURCES) $(ALL_TEST_MSSG_SOURCES)
	ctags $(ALL_LIB_SOURCES)

