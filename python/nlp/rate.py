#!/usr/bin/python
#encoding: utf-8
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-1", dest="file1")
parser.add_option("-2", dest="file2")
(o, args) = parser.parse_args()

ngram1 = {}
total1 = 0
for line in open(o.file1):
    (words, freq)  = line.strip().split("\t",2)
    freq = int(freq)
    ngram1[words] = freq
    total1 += freq

ngram2 = {}
total2 = 0
for line in open(o.file2):
    (words, freq)  = line.strip().split("\t",2)
    freq = int(freq)
    ngram2[words] = freq
    total2 += freq

for (words, freq) in ngram1.items():
    prob1 = float(freq) / total1
    if words in ngram2:
        prob2 = float(ngram2[words]) / total2
        diff = prob1 / prob2
        print words + "\t" + str(diff)
