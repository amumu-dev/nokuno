#!/usr/bin/env python
#encoding: utf-8
import sys
from optparse import OptionParser
from format import format

parser = OptionParser()
parser.add_option("-d", dest="dictionary", default="data/dictionary.txt")
parser.add_option("-c", dest="connection", default="data/connection.txt")
parser.add_option("-s", dest="separator", default="\t")
(o, args) = parser.parse_args()

#load dictionary
dictionary = {}
for line in open(o.dictionary):
    (yomi, word, pos, prob) = line.strip().split(o.separator, 3)
    prob = float(prob)
    if not yomi in dictionary:
        dictionary[yomi] = [(word, pos, prob)]
    else:
        dictionary[yomi].append((word, pos, prob))
#print format(dictionary.items()[:10])

#load connection
connection = {}
for line in open(o.connection):
    (left, right, prob) = line.strip().split(o.separator, 2)
    prob = float(prob)
    key = left + "_" + right
    connection[key] = prob
#print format(connection)

#input from stdin
for line in sys.stdin:
    input = line.strip()
    length = len(input)

    #create lattice
    lattice = [None] * (length+1)
    lattice[0] = [('<S>', '<S>', '<S>', 1.0)]
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

