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

#all: server client
all: server client test_mssg

# this generates the target executables
server: $(SERVER_OBJS)
	$(CC) -o server $(SERVER_OBJS)

client: $(CLIENT_OBJS)
	$(CC) -o client $(CLIENT_OBJS)

test_mssg: $(TEST_MSSG_OBJS)
	$(CC) -o test_mssg $(TEST_MSSG_OBJS)

# this is a generic rule for .o files 
%.o: %.c 
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -f server.o udp.o client.o server client *.o

tags:
	ctags $(ALL_LIB_SOURCES)

