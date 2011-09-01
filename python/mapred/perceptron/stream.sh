#!/bin/bash
if [ $# != '2' ]
then
    echo "stream.sh input_path output_path"
    exit
fi

# First iteration
echo "Iteration 1"
hadoop jar \
    $HADOOP_HOME/hadoop-streaming.jar \
    -files perceptron.py,reduce.py \
    -input $1 \
    -output $2/weight1 \
    -mapper ./perceptron.py \
    -reducer ./reduce.py

# Run iteration
for i in `seq 2 10`
do
    echo "Iteration $i"
    hadoop jar \
        $HADOOP_HOME/hadoop-streaming.jar \
        -files perceptron.py,reduce.py,hdfs:///user/yookuno/$2/weight`expr $i - 1`/part-00000 \
        -input $1 \
        -output $2/weight$i \
        -mapper "./perceptron.py -w part-00000" \
        -reducer ./reduce.py
done

