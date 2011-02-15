#!/usr/bin/env python
import sys
import optparse

# parse option
parser = optparse.OptionParser()
parser.add_option("-f", dest="file", default="dataset.txt")
(options, args) = parser.parse_args()

# load dictionary
for line in open(options.file):
    line = line.strip().split("\t")
    key = line[0]
    values = line[1:]
    for value in values:
        if key != value:
            print key + "\t" + value
