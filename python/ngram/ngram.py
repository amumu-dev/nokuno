#!/usr/bin/python
#encoding: utf-8
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-n", dest="n", type="int", default=3)
(options, args) = parser.parse_args()
n = options.n

for line in sys.stdin:
    words = line.split()
    for i in range(len(words)-n):
        print " ".join(words[i:i+n])

"""
usage:
    cat wakati.txt | ngram.py -n 3 | sort | uniq -c > trigram.txt
"""
