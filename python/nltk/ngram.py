#!/usr/bin/python
#encoding: utf-8
import sys, nltk

if len(sys.argv) > 1:
    n = int(sys.argv[1])
else:
    n = 3

raw = sys.stdin.read()
words = raw.split()
ngrams = nltk.ngrams(words, n)
fd = nltk.FreqDist(ngrams)
for ngram in fd:
    print "%s\t%s" % (" ".join(ngram), fd[ngram])

