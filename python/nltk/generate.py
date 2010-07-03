#!/usr/bin/python
#encoding: utf-8
import nltk, sys

raw = sys.stdin.read()
words = raw.split();
text = nltk.Text(words)
gen = text.generate(300)
print gen
