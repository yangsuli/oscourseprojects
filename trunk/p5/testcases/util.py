#!/usr/bin/env python
import os
import sys
import commands
import time

def info(message):
    print "%s" % message
    sys.stdout.flush()
    
def error(message):
    print "ERROR: %s\n" % message
    sys.stdout.flush()
    sys.exit(1)

def make():
    """make sure a make file exists, and make generate server."""
    if not (os.path.exists("Makefile") or os.path.exists("makefile")):
        error("missing Makefile or makefile")

    # delete server if any and do a make clean
    commands.getoutput("make clean")
    commands.getoutput("rm -rf server")

    # now do a make
    commands.getoutput("make")
    if not os.path.exists("server"):
        error("make does not generate an excutable server file")
        
    #    sys.exit(0)

def kill():
    commands.getoutput("killall -9 server")
    time.sleep(0.5)



#########################################
# i need to provide a *raw* commands here
# e.g ./server 2010 2 4 FIFO
# any redirection is done by this method
#########################################
def run(cmd):
    """ run a server with given parameters."""
    kill()
    os.system(cmd + " > /dev/null &")
    # check if server actually run
    ps = commands.getoutput("ps -a")
    if ps.find(cmd) == -1:
        error("Server can not start when runing the command: " + cmd)

    time.sleep(1)
    # If You reach here, your server is up

def run2(cmd):
    """ run a server with given parameters."""
    kill()
    os.system(cmd + " > /dev/null &")

    time.sleep(1)

# check if the server is still alive
# return -1 if server is dead
def is_server_alive(cmd):
    ps = commands.getoutput("ps -a")
    return ps.find(cmd)
    
def good(message):
    print ""
    print "#########################################"
    print "GOOD! " + message
    print "#########################################"
    print ""
