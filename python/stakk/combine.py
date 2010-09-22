#!/usr/bin/env python
#encoding: utf-8
import sys
from optparse import OptionParser
from format import format

parser = OptionParser()
parser.add_option("-y", dest="yomi", default="data/word_yomi_unigram.txt")
parser.add_option("-w", dest="word", default="data/pos_word_unigram.txt")
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

for yomi, words in yomi2word.items():
    for word, prob1 in words:
        if word in word2pos:
            for pos, prob2 in word2pos[word]:
                prob = float(prob1) * float(prob2)
                print o.separator.join([yomi, word, pos, str(prob)])
