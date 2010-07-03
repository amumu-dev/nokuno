#!/usr/bin/python
#encoding: utf-8
import sys

for line in sys.stdin:
    (freq, word) = line.strip().split(" ", 1)
    print "%s\t%s" % (word, freq)

"""
usage:
    cat wakati.txt | ngram.py -n 3 | sort | uniq -c | threshold.py -t 10 | sort -nr | swap.py > trigram.txt

"""
