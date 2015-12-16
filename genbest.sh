#!/bin/sh
INPUT=bestSolutions.txt
CALCS=datasetscalc

cat $INPUT | grep "sym" | grep " 2 " | awk '{print $3}' >> $CALCS/sym_2.best
cat $INPUT | grep "sym" | grep " 3 " | awk '{print $3}' >> $CALCS/sym_3.best
cat $INPUT | grep "sym" | grep " 4 " | awk '{print $3}' >> $CALCS/sym_4.best
cat $INPUT | grep "sym" | grep " 5 " | awk '{print $3}' >> $CALCS/sym_5.best

cat $INPUT | grep "str" | grep " 2 " | awk '{print $3}' >> $CALCS/str_2.best
cat $INPUT | grep "str" | grep " 3 " | awk '{print $3}' >> $CALCS/str_3.best
cat $INPUT | grep "str" | grep " 4 " | awk '{print $3}' >> $CALCS/str_4.best
cat $INPUT | grep "str" | grep " 5 " | awk '{print $3}' >> $CALCS/str_5.best

cat $INPUT | grep "shrd" | grep " 2 " | awk '{print $3}' >> $CALCS/shrd_2.best
cat $INPUT | grep "shrd" | grep " 3 " | awk '{print $3}' >> $CALCS/shrd_3.best
cat $INPUT | grep "shrd" | grep " 4 " | awk '{print $3}' >> $CALCS/shrd_4.best
cat $INPUT | grep "shrd" | grep " 5 " | awk '{print $3}' >> $CALCS/shrd_5.best

cat $INPUT | grep "crd" | grep " 2 " | awk '{print $3}' >> $CALCS/crd_2.best
cat $INPUT | grep "crd" | grep " 3 " | awk '{print $3}' >> $CALCS/crd_3.best
cat $INPUT | grep "crd" | grep " 4 " | awk '{print $3}' >> $CALCS/crd_4.best
cat $INPUT | grep "crd" | grep " 5 " | awk '{print $3}' >> $CALCS/crd_5.best
