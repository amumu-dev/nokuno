#!/usr/bin/python
#encoding: utf-8
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-n", dest="n", type="int", default=3)
parser.add_option("-s", dest="separator", default="\t")
(options, args) = parser.parse_args()
n = options.n

for line in sys.stdin:
    words = line.split(options.separator)
    for i in range(len(words)-n):
        print options.separator.join(words[i:i+n])
