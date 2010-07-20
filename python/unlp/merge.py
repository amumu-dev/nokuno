#!/usr/bin/python
#encoding: utf-8
import sys

current = ""
total = 0
for line in sys.stdin:
    (words, freq)  = line.strip().split("\t",2)
    freq = int(freq)
    if words == current:
        total += freq
    else:
        if total != 0:
            print current + "\t" + str(total)
        current = words
        total = freq

