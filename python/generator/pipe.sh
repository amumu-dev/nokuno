#!/bin/bash
ngram.py -n $1 \
| sort \
| uniq -c \
| threshold.py -t $2 \
| sort -k 2,$1 -k 1,1nr \
| total.py $1 \
| tac \
| prob.py

# usage:
# cat wakati.txt | ./pipe.sh 3 10 > trigram.txt
