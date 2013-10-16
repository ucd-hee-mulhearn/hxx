#! /bin/tcsh 

setenv NEVENTS  $1
setenv EBEAM    $2
setenv MCHI     $3
setenv RUNNAME  $4

hostname

echo "launch signal job for ebeam=$EBEAM nevents=$NEVENTS and mchi=$MCHI" 
echo "run name is $RUNNAME"

source SETUP

cp Cards/run_card_default.dat Cards/run_card.dat

# set nevents and beam energy
edit_run_card.py --nevents=$NEVENTS --ebeam=$EBEAM

# set mchi parameter:
edit_param_card.py --mchi=$MCHI

# generate partons
./bin/generate_events $RUNNAME -f --laststep=parton

#replace chi particles with neutrinos:
./replace.csh Events/$RUNNAME

# launch pythia to delphes
echo "pythia $RUNNAME" > me.cmd
echo "0" >> me.cmd
echo "0" >> me.cmd
echo "" >> me.cmd
./bin/madevent me.cmd

echo "DONE with signal job for $RUNNAME"
