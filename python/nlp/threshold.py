#!/usr/bin/python
#encoding: utf-8
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-t", dest="threshold", type="int", default=10)
parser.add_option("-s", dest="separator", default="\t")
parser.add_option("-c", dest="column", type="int", default=-1)
(options, args) = parser.parse_args()

for line in sys.stdin:
    columns = line.strip().split(options.separator)
    freq = int(columns[options.column])
    if freq >= options.threshold:
        print line,
