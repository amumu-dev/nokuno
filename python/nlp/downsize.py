#!/usr/bin/env python
#encoding: utf-8
import sys

for line in sys.stdin:
    splited = line.strip().split("\t")
    if splited[1] == splited[2]:
        print "\t".join(splited[:5])
