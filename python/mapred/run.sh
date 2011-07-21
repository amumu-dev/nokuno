#!/bin/bash
if [ $# != '2' ]; then echo "run.sh input_path output_path"; exit; fi;

hadoop jar $HADOOP/hadoop-streaming.jar \
 -D mapred.output.key.comparator.class=org.apache.hadoop.mapred.lib.KeyFieldBasedComparator \
 -D mapred.text.key.comparator.options=-k1,1nr \
 -input $1 \
 -output $2 \
 -mapper map.py \
 -reducer cat \
 -file map.py

