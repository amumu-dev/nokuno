#!/usr/bin/env python
#encoding: utf-8
import sys
from optparse import OptionParser
from format import format

parser = OptionParser()
parser.add_option("-y", dest="yomi", default="data/yomi_word_unigram.txt")
parser.add_option("-w", dest="word", default="data/word_pos_unigram.txt")
parser.add_option("-p", dest="pos", default="data/pos_bigram.txt")
(o, args) = parser.parse_args()

#load dictionary
dic_yomi_word = {}
dic_word = {}
for line in open(o.yomi):
    (yomi, word, freq) = line.strip().split("\t", 2)
    freq = float(freq)
    if not yomi in dic_yomi_word:
        dic_yomi_word[yomi] = [(word, freq)]
    else:
        dic_yomi_word[yomi].append((word,freq))
    if not word in dic_word:
        dic_word[word] = freq
    else:
        dic_word[word] += freq

for key,value in dic_yomi_word.items():
    for i in range(len(value)):
        word, freq = value[i]
        prob = freq / dic_word[word]
        value[i] = (word, prob)

print format(dic_yomi_word.items()[:10])

#input from stdin
for line in sys.stdin:
    input = line.strip()
    length = len(input)

    #create lattice
    lattice = [None] * (length+1)
    lattice[0] = ('<S>', '', 1.0)
    for i in range(length):
        for j in range(i+1, length+1):
            yomi = input[i:j]
            if yomi in yomi_word and lattice[i] != None:
                (surf, freq) = yomi_word[yomi]
                prob = lattice[i][2] * freq / summation
                if lattice[j] == None or lattice[j][1] < prob:
                    lattice[j] = (surf, yomi, prob)
    #back trace
    i = length
    result = ""
    while i > 0 and lattice[i] != None:
        word = lattice[i]
        result = word[0] + " " + result
        i -= len(word[1])
    print result
