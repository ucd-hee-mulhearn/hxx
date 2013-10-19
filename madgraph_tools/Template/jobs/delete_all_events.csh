#! /bin/tcsh

find ./Events | grep \\.root    | xargs ls -l
#find ./Events | grep \\.lhe.gz  | xargs ls -l
#find ./Events | grep \\.lhco.gz | xargs ls -l
#find ./Events | grep \\.hep.gz  | xargs ls -l

echo "Go ahead and delete? Y [N]:  "
set input = $<

switch ($input)
       case [Y]:
        echo "DELETING FILES!"

find Events | grep \\.root    | xargs rm
#find Events | grep \\.lhe.gz  | xargs rm
#find Events | grep \\.lhco.gz | xargs rm
#find Events | grep \\.hep.gz  | xargs rm

        breaksw 
       default:
        echo "delete aborted..."
endsw
