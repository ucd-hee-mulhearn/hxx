#!/bin/tcsh

set FILE="$1/unweighted_events.lhe.gz"
set ORIG=$FILE.orig

if (! -e $FILE) then
    echo "usage:  replace.csh <dir>"
    exit
endif

echo " replacing PIDs in $FILE according to:  "
cat Cards/replace_card*.dat

echo $ORIG

#you can comment this to live dangerously:
cp $FILE $ORIG

mv $FILE ./tmpa.lhe.gz
gunzip tmpa.lhe.gz
cat Cards/replace_card*.dat | ./bin/internal/Gridpack/replace.pl tmpa.lhe tmpb.lhe
gzip tmpb.lhe
rm tmpa.lhe
mv tmpb.lhe.gz $FILE

echo "BEFORE:"
zcat $ORIG | tail -n 20
echo "AFTER:"
zcat $FILE | tail -n 20

echo "DONE!"
echo "Don't like what you see?  Original file is at:   $ORIG\n".

