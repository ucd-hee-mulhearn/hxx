#! /bin/tcsh 

setenv NEVENTS  $1
setenv EBEAM    $2
setenv RUNNAME  $3

hostname

echo "launch background job for ebeam=$EBEAM nevents=$NEVENTS" 
echo "run name is $RUNNAME"

cp Cards/run_card_default.dat Cards/run_card.dat

# set nevents and beam energy
edit_run_card.py --nevents=$NEVENTS --ebeam=$EBEAM

# generate partons
./bin/generate_events $RUNNAME -f --laststep=delphes

echo "DONE with background job $RUNNAME"
