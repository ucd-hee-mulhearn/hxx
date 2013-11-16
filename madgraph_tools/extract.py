#!/usr/bin/python

import sys
import os
from subprocess import call



#print ("The total numbers of args passed to the script: %d " % total)

total = len(sys.argv)

dir = sys.argv[1]

if not os.path.exists(dir):
    print "creating directory ", dir
    call(["mkdir", dir])

for  i in range(2,total):
    file = sys.argv[i]
    print "info processing file ", file;    
    call("tar -xf" + file, shell=True)
    call("mv Events/run_* " + dir, shell=True)                
    call("rm -fr Events", shell=True)
