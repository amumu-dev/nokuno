#!/bin/bash
if [ $# != '2' ]
then
    echo "local.sh input_path output_path"
    exit
fi

for i in `seq 1 10`; do
    cat $1 | ./perceptron.py -w $2/weight`expr $i - 1`.txt | sort | ./reduce.py > $2/weight$i.txt;
done;

