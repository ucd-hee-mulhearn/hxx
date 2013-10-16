#!/usr/bin/python

import fileinput
import sys, getopt
from subprocess import call



def usage():
    print 'edit_param_card.py:  help not implementeded yet...'
    sys.exit()

def main(argv):
   file="Cards/param_card.dat"

   mchi = ''

   try:
      opts, args = getopt.getopt(argv,"h",["mchi="]) # ["ebeam=","min_mll=","max_mll="]
   except getopt.GetoptError:
      usage()
      sys.exit(2)
   for opt, arg in opts:
      if opt == '-h':
         usage()
      elif opt in ("--mchi"):
         mchi = arg

   if mchi != "":
       print "setting mass of chi to:  ", mchi

#  9000006 1.000000e+02 # Mchi 

   for line in fileinput.input(file, inplace=1):
       if mchi != "":
           if "Mchi" in line:
               line = "  9000006 " + mchi + " # Mchi\n"
       sys.stdout.write(line)

   call(["grep","Mchi",file])   

if __name__ == "__main__":
   main(sys.argv[1:])






















VALUE = "TEST2"


