#!/usr/bin/env python
import os
import sys
import commands
import time
import thread
import threading
from threading import Thread


import util

########################################
# check if you implement FIFO correctly
########################################


# this is ugly, should customize server startup parameters also
NUM_CLIENT = 4
CGI_SPIN_TIME = 2
EXPECTED_TIME = 2
NUM_LOOPS = 10

tmpfile = "/tmp/p5.result"

expected = []
got = []
lock = threading.Lock()

def test(cmd):
    global expected
    global got
    util.info("")
    util.info("- Starting " + cmd)
    util.info("")
    util.run(cmd)

    start = time.time()

    # reset for multiple test
    expected = []
    got = []

    for i in range(1, NUM_CLIENT):
        expected.append(commands.getoutput("cat ./testdata/file%s.txt" % str(i)))

    commands.getoutput("rm -rf %s" % tmpfile)
    clientlist = []

    for i in range(0, NUM_CLIENT):
        client = testit("Client-" + str(i), i)
        clientlist.append(client)
        client.start()
        time.sleep(0.3)

    for client in clientlist:
        client.join()


    end = time.time()
    util.info("Elapsed time (in seconds): " + str(end-start))

    if util.is_server_alive(cmd) == -1:
        util.error("Ouch! Server is dead!"
                   " Your bounded buffered may not be well protected");

    time.sleep(CGI_SPIN_TIME + 2)
    res = commands.getoutput("cat %s" % tmpfile)

    if util.is_server_alive(cmd) == -1:
        util.error("Ouch! Server is dead!"
                   " Your bounded buffered may not be well protected");

    pos0 = res.find(expected[0])
    pos1 = res.find(expected[1])
    pos2 = res.find(expected[2])
    passed = pos0 > 0 and pos1 > 0 and pos2 > 0 and pos0 < pos1 and pos1 < pos2
    
    util.info(res)


class testit(Thread):
    def __init__ (self,clientname, id):
        Thread.__init__(self)
        self.clientname = clientname
        self.id = id

    def run(self):
        clientcmd = "./testclient localhost 2010 "
        if self.id == 0:
            file = "/output.cgi"
        else:
            file = "/testdata/file%s.txt" % str(self.id)
        
        clientcmd = clientcmd + file + " >> " + tmpfile + " &"
        util.info(self.clientname + ": " + clientcmd)

        os.system(clientcmd)



util.make()

for i in range(0, NUM_LOOPS):
    print ""
    print "#############################"
    print "- %s iteration" % str(i)
    print "#############################"
    print ""
    
    test("./server 2010 1 4 FIFO")

sys.exit(0)


