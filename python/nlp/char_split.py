#!/usr/bin/env python
#encoding: utf-8
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-w", dest="word", default="data/word.txt")
parser.add_option("-r", dest="read", default="data/read.txt")
(options, args) = parser.parse_args()

file_word = open(options.word, "w")
file_read = open(options.read, "w")

for line in sys.stdin:
    splited = line.strip().split("\t")
    if len(splited) < 5: continue
    (read, lid, rid, cost, word) = splited[:5]
    read_u = u" ".join(read.decode('utf-8')).encode('utf-8')
    word_u = u" ".join(word.decode('utf-8')).encode('utf-8')
    file_read.write(read_u + "\n")
    file_word.write(word_u + "\n")
