#!/usr/bin/python
#encoding: utf-8
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-t", dest="threshold", type="int", default=10)
(options, args) = parser.parse_args()

for line in sys.stdin:
    (freq, word) = line.strip().split(" ", 1)
    if int(freq) >= options.threshold:
        print "%s %s" % (freq, word)

"""
usage:
    cat wakati.txt | ngram.py -n 3 | sort | uniq -c | threshold.py -t 10 | sort -nr > trigram.txt
    cat wakati.txt | ngram.py -n 2 | sort | uniq -c | threshold.py -t 10 | sort -k 2,2 -k 1,1nr > bigram.txt

"""
