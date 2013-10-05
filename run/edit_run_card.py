#!/usr/bin/python

import fileinput
import sys, getopt
from subprocess import call



def usage():
    print 'edit_run_card.py:  help not implementeded yet...'
    sys.exit()

def main(argv):
   file="Cards/run_card.dat"

   nevents = ''
   ebeam   = ''
   min_mll = ''
   max_mll = ''
   try:
      opts, args = getopt.getopt(argv,"h",["nevents=","ebeam=","min_mll=","max_mll="])
   except getopt.GetoptError:
      usage()
      sys.exit(2)
   for opt, arg in opts:
      if opt == '-h':
         usage()
      elif opt in ("--nevents"):
         nevents = arg
      elif opt in ("--ebeam"):
         ebeam = arg
      elif opt in ("--min_mll"):
         min_mll = arg
      elif opt in ("--max_mll"):
         max_mll = arg

   if nevents != "":
       print "setting nevents to:  ", nevents
   if ebeam != "":
       print "setting ebeam to:    ", ebeam
   if min_mll != "":
       print "setting min_mll to:  ", min_mll
   if max_mll != "":
       print "setting max_mll to:  ", max_mll

   for line in fileinput.input(file, inplace=1):
       if nevents != "":
           if "nevents" in line:
               line = "   " + nevents + " = nevents ! Number of unweighted events requested\n";
       if ebeam != "":
           if "ebeam1" in line:
               line = "   " + ebeam + "     = ebeam1  ! beam 1 total energy in GeV\n"
           if "ebeam2" in line:
               line = "   " + ebeam + "     = ebeam2  ! beam 2 total energy in GeV\n"
       if min_mll != "":
           if "mmll " in line:
               line = "   " + min_mll + "= mmll    ! min invariant mass of l+l- (same flavour) lepton pair\n"
       if max_mll != "":
           if "mmllmax " in line:
               line = "   " + max_mll + "= mmllmax ! max invariant mass of l+l- (same flavour) lepton pair\n"
       sys.stdout.write(line)

   call(["grep","nevents",file])   
   call(["grep","ebeam",file])   
   call(["grep","mll",file])   

if __name__ == "__main__":
   main(sys.argv[1:])






















VALUE = "TEST2"


