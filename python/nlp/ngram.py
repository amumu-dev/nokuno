#!/usr/bin/python
#encoding: utf-8
from sys import stdin
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-n", dest="n", type="int", default=3)
parser.add_option("-s", dest="separator", default="\t")
parser.add_option("-o", dest="output", action="store_true")
(options, args) = parser.parse_args()
n = options.n

for line in stdin:
    words = line.strip().split(options.separator)
    if options.output and len(words) > 1:
        words.insert(0, "<S>")
        words.append("</S>")
    for i in range(len(words)-n+1):
        print options.separator.join(words[i:i+n])

