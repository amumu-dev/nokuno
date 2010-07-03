#!/usr/bin/python
#encoding: utf-8
import sys, re
p = re.compile("\[\[.+\]\]\n")
for line in sys.stdin:
    if p.match(line) == None:
        print line
