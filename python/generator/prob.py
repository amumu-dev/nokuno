#!/usr/bin/python
#encoding: utf-8
import sys

current = 0
prev = None
for line in sys.stdin:
    (context, word, freq, total) = line.strip().split("\t", 3)
    if context != prev:
        current = total
    prob = float(total) / float(current)
    print "%s\t%s\t%s\t%s\t%f" % (context, word, freq, total, prob)
    prev = context

"""
usage:
    cat wakati.txt | ngram.py -n 2 | sort | uniq -c | threshold.py -t 10 | sort -k 2,2 -k 1,1nr | total.py 2 | tac | prob.py > bigram.txt
"""
