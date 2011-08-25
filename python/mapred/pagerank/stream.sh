#!/bin/bash
if [ $# != '2' ]; then echo "run.sh input_path output_path"; exit; fi;

echo "Initialize: ";

hadoop jar $HADOOP/hadoop-streaming.jar \
    -numReduceTasks 50 \
    -input $1 \
    -output $2/0 \
    -mapper cat \
    -reducer init.py \
    -file init.py \

for i in `seq 1 10`; do
    echo "Sequence $i:";

    hadoop jar $HADOOP/hadoop-streaming.jar \
        -numReduceTasks 50 \
        -input $2/`expr $i - 1` \
        -output $2/$i \
        -mapper map.py \
        -reducer reduce.py \
        -file map.py \
        -file reduce.py;
done;
