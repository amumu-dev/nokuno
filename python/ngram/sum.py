#!/usr/bin/python
#encoding: utf-8
import sys

total = 0
for line in sys.stdin:
    (words, freq) = line.strip().split("\t", 1)
    total += long(freq)

print total

"""
usage:
    cat wakati.txt | ngram.py -n 2 | sort | uniq -c | threshold.py -t 10 | sort -k 2,2 -k 1,1nr | total.py 2 > bigram.txt
"""
