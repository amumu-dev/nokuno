#!/usr/bin/python
import sys

if len(sys.argv) > 1:
    n = int(sys.argv[1])
else:
    n = 3

for line in sys.stdin:
    splited = line.strip().split(" ")
    ngram = " ".join(splited[:n])
    rest = "\t".join(splited[n:])
    print "%s\t%s" % (ngram, rest)

