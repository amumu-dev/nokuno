#!/usr/bin/env python
#encoding: utf-8
import sys
from optparse import OptionParser
from format import format

parser = OptionParser()
parser.add_option("-y", dest="yomi", default="data/word_yomi_unigram.txt")
parser.add_option("-w", dest="word", default="data/pos_word_unigram.txt")
parser.add_option("-p", dest="pos", default="data/pos_bigram.txt")
parser.add_option("-s", dest="separator", default="\t")
(o, args) = parser.parse_args()

#load dictionary
yomi2word = {}
for line in open(o.yomi):
    (word, yomi, prob) = line.strip().split(o.separator, 2)
    prob = float(prob)
    if not yomi in yomi2word:
        yomi2word[yomi] = [(word, prob)]
    else:
        yomi2word[yomi].append((word, prob))
#print format(yomi2word.items()[:10])

word2pos = {}
for line in open(o.word):
    (pos, word, prob) = line.strip().split(o.separator, 2)
    prob = float(prob)
    if not word in word2pos:
        word2pos[word] = [(pos, prob)]
    else:
        word2pos[word].append((pos, prob))
#print format(word2pos.items()[:10])

pos2pos = {}
for line in open(o.pos):
    (left, right, prob) = line.strip().split(o.separator, 2)
    prob = float(prob)
    key = left + "_" + right
    pos2pos[key] = prob
#print format(pos2pos)

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
                (surf, prob) = yomi_word[yomi]
                prob = lattice[i][2] * prob / summation
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
