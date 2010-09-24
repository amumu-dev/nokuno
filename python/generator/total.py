#!/usr/bin/python
#encoding: utf-8
import sys

if len(sys.argv) > 1:
    n = int(sys.argv[1])
else:
    n = 3

total = 0
prev = None
for line in sys.stdin:
    (freq, words) = line.strip().split(" ", 1)
    ngram = words.split(" ", n)
    context = " ".join(ngram[:-1])
    word = ngram[-1]
    if context != prev:
        total = 0
    total += long(freq)
    print "%s\t%s\t%s\t%d" % (context, word, freq, total)
    prev = context

"""
usage:
    cat wakati.txt | ngram.py -n 2 | sort | uniq -c | threshold.py -t 10 | sort -k 2,2 -k 1,1nr | total.py 2 > bigram.txt
"""
