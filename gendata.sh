#!/bin/sh
H0BIN=./build/src/r-spantree_0
H1BIN=./build/src/r-spantree_1
H2BIN=./build/src/r-spantree_2

INPUTSETS=datasets
CALCS=datasetscalc
SOLUTIONS=datasetssolution

function calc () {
echo "$1 for $2"
$1 -in $2 -out $3 | tail -n 1 >> $4
}

for i in $(find $INPUTSETS/*);
do
  calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/$(basename $i).calc;
  calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/$(basename $i).calc;
done;
