#!/bin/sh
H0BIN=./build/src/r-spantree_0
H1BIN=./build/src/r-spantree_1
H2BIN=./build/src/r-spantree_2

INPUTSETS=datasets
CALCS=datasetscalc
SOLUTIONS=datasetssolution

function calc () {
echo "$1 for $2"
$1 -in $2 -out $3 | tail -n 1 | tr -d '\n' >> $4
}

#for i in $(find $INPUTSETS/ -name "sym*_2" | sort);
#do
  #echo -n $(basename $i | cut -c 4-5) >> $CALCS/sym_2;
  #echo -n " " >> $CALCS/sym_2;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/sym_2;
  #echo -n " " >> $CALCS/sym_2;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/sym_2;
  #echo >> $CALCS/sym_2;
#done;

#for i in $(find $INPUTSETS/ -name "sym*_3" | sort);
#do
  #echo -n $(basename $i | cut -c 4-5) >> $CALCS/sym_3;
  #echo -n " " >> $CALCS/sym_3;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/sym_3;
  #echo -n " " >> $CALCS/sym_3;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/sym_3;
  #echo >> $CALCS/sym_3;
#done;

#for i in $(find $INPUTSETS/ -name "sym*_4" | sort);
#do
  #echo -n $(basename $i | cut -c 4-5) >> $CALCS/sym_4;
  #echo -n " " >> $CALCS/sym_4;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/sym_4;
  #echo -n " " >> $CALCS/sym_4;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/sym_4;
  #echo >> $CALCS/sym_4;
#done;

#for i in $(find $INPUTSETS/ -name "sym*_5" | sort);
#do
  #echo -n $(basename $i | cut -c 4-5) >> $CALCS/sym_5;
  #echo -n " " >> $CALCS/sym_5;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/sym_5;
  #echo -n " " >> $CALCS/sym_5;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/sym_5;
  #echo >> $CALCS/sym_5;
#done;

#for i in $(find $INPUTSETS/ -name "str*_2" | sort);
#do
  #echo -n $(basename $i | sed -e 's/str\(.*\)_\(.*\)/\1/'| sed s'/.$//') >> $CALCS/str_2;
  #echo -n " " >> $CALCS/str_2;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/str_2;
  #echo -n " " >> $CALCS/str_2;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/str_2;
  #echo >> $CALCS/str_2;
#done;

#for i in $(find $INPUTSETS/ -name "str*_3" | sort);
#do
  #echo -n $(basename $i | sed -e 's/str\(.*\)_\(.*\)/\1/'| sed s'/.$//') >> $CALCS/str_3;
  #echo -n " " >> $CALCS/str_3;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/str_3;
  #echo -n " " >> $CALCS/str_3;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/str_3;
  #echo >> $CALCS/str_3;
#done;

#for i in $(find $INPUTSETS/ -name "str*_4" | sort);
#do
  #echo -n $(basename $i | sed -e 's/str\(.*\)_\(.*\)/\1/'| sed s'/.$//') >> $CALCS/str_4;
  #echo -n " " >> $CALCS/str_4;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/str_4;
  #echo -n " " >> $CALCS/str_4;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/str_4;
  #echo >> $CALCS/str_4;
#done;

#for i in $(find $INPUTSETS/ -name "str*_5" | sort);
#do
  #echo -n $(basename $i | sed -e 's/str\(.*\)_\(.*\)/\1/'| sed s'/.$//') >> $CALCS/str_5;
  #echo -n " " >> $CALCS/str_5;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/str_5;
  #echo -n " " >> $CALCS/str_5;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/str_5;
  #echo >> $CALCS/str_5;
#done;

#for i in $(find $INPUTSETS/ -name "shrd*_2" | sort);
#do
  #echo -n $(basename $i | sed -e 's/shrd\(.*\)_\(.*\)/\1/'| sed s'/.$//') >> $CALCS/shrd_2;
  #echo -n " " >> $CALCS/shrd_2;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/shrd_2;
  #echo -n " " >> $CALCS/shrd_2;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/shrd_2;
  #echo >> $CALCS/shrd_2;
#done;

#for i in $(find $INPUTSETS/ -name "shrd*_3" | sort);
#do
  #echo -n $(basename $i | sed -e 's/shrd\(.*\)_\(.*\)/\1/'| sed s'/.$//') >> $CALCS/shrd_3;
  #echo -n " " >> $CALCS/shrd_3;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/shrd_3;
  #echo -n " " >> $CALCS/shrd_3;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/shrd_3;
  #echo >> $CALCS/shrd_3;
#done;

#for i in $(find $INPUTSETS/ -name "shrd*_4" | sort);
#do
  #echo -n $(basename $i | sed -e 's/shrd\(.*\)_\(.*\)/\1/'| sed s'/.$//') >> $CALCS/shrd_4;
  #echo -n " " >> $CALCS/shrd_4;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/shrd_4;
  #echo -n " " >> $CALCS/shrd_4;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/shrd_4;
  #echo >> $CALCS/shrd_4;
#done;

#for i in $(find $INPUTSETS/ -name "shrd*_5" | sort);
#do
  #echo -n $(basename $i | sed -e 's/shrd\(.*\)_\(.*\)/\1/'| sed s'/.$//') >> $CALCS/shrd_5;
  #echo -n " " >> $CALCS/shrd_5;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/shrd_5;
  #echo -n " " >> $CALCS/shrd_5;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/shrd_5;
  #echo >> $CALCS/shrd_5;
#done;

#for i in $(find $INPUTSETS/ -name "crd*_2" | sort);
#do
  #echo -n $(basename $i | sed -e 's/crd\(.*\)_\(.*\)/\1/'| sed s'/.$//') >> $CALCS/crd_2;
  #echo -n " " >> $CALCS/crd_2;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/crd_2;
  #echo -n " " >> $CALCS/crd_2;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/crd_2;
  #echo >> $CALCS/crd_2;
#done;

#for i in $(find $INPUTSETS/ -name "crd*_3" | sort);
#do
  #echo -n $(basename $i | sed -e 's/crd\(.*\)_\(.*\)/\1/'| sed s'/.$//') >> $CALCS/crd_3;
  #echo -n " " >> $CALCS/crd_3;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/crd_3;
  #echo -n " " >> $CALCS/crd_3;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/crd_3;
  #echo >> $CALCS/crd_3;
#done;

#for i in $(find $INPUTSETS/ -name "crd*_4" | sort);
#do
  #echo -n $(basename $i | sed -e 's/crd\(.*\)_\(.*\)/\1/'| sed s'/.$//') >> $CALCS/crd_4;
  #echo -n " " >> $CALCS/crd_4;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/crd_4;
  #echo -n " " >> $CALCS/crd_4;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/crd_4;
  #echo >> $CALCS/crd_4;
#done;

#for i in $(find $INPUTSETS/ -name "crd*_5" | sort);
#do
  #echo -n $(basename $i | sed -e 's/crd\(.*\)_\(.*\)/\1/'| sed s'/.$//') >> $CALCS/crd_5;
  #echo -n " " >> $CALCS/crd_5;
  #calc $H1BIN $i $SOLUTIONS/$(basename $i).solution1 $CALCS/crd_5;
  #echo -n " " >> $CALCS/crd_5;
  #calc $H2BIN $i $SOLUTIONS/$(basename $i).solution2 $CALCS/crd_5;
  #echo >> $CALCS/crd_5;
#done;
