CC   = gcc
# Useful opts are -Wall, -ggdb, ...
OPTS = -Wall

ALL_SERVER_SOURCES = server.c udp.c
ALL_CLIENT_SOURCES = client.c udp.c

SERVER_OBJS = server.o udp.o
CLIENT_OBJS = client.o udp.o

ALL_LIB_SOURCES = $(ALL_SERVER_SOURCES) $(ALL_CLIENT_SOURCES)

all: server client

# this generates the target executables
server: $(SERVER_OBJS)
	$(CC) -o server $(SERVER_OBJS)

client: $(CLIENT_OBJS)
	$(CC) -o client $(CLIENT_OBJS)

# this is a generic rule for .o files 
%.o: %.c 
	$(CC) $(OPTS) -c $< -o $@

clean:
	rm -f server.o udp.o client.o server client

tags:
	ctags $(ALL_LIB_SOURCES)

