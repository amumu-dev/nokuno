#!/usr/bin/python
#encoding: utf-8
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-t", dest="threshold", type="int", default=10)
parser.add_option("-s", dest="separator", default="\t")
(options, args) = parser.parse_args()

# swap the 'unic -c' command result.
for line in sys.stdin:
    (freq, word) = line.strip().split(" ", 1)
    freq = int(freq)
    if freq >= options.threshold:
        print "%s\t%s" % (word, freq)
