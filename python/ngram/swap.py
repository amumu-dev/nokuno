#!/usr/bin/python
#encoding: utf-8
import sys

# swap the 'unic -c' command result.
for line in sys.stdin:
    (freq, word) = line.strip().split(" ", 1)
    print "%s\t%s" % (word, freq)
