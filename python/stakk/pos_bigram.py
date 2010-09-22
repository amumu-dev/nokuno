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
        dictionary[yomi] = [[yomi, word, pos, prob]]
    else:
        dictionary[yomi].append([yomi, word, pos, prob])
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
    lattice = [[] for i in range(length+2)]
    lattice[0].append(['', '<S>', 'その他', 1.0])
    lattice[-1].append(['', '</S>', 'その他', 1.0])
    for i in range(length):
        for j in range(i+1, length+1):
            yomi = input[i:j]
            if yomi in dictionary:
                for item in dictionary[yomi]:
                    lattice[j].append(item)
    #print format(lattice)

    #forward search
    for i in range(1, length+2):
        for right in lattice[i]:
            (yomi, word, pos, prob) = right
            j = i - len(yomi)
            def func(x):
                k = x[2]+"_"+pos
                if k in connection:
                    return x[3]*connection[k]
                else:
                    return 0.0
            best = max(lattice[j], key=func)
            right[3] = best[3] * func(best)

    for node in lattice: print format(node)

"""
    #back trace
    i = length
    result = ""
    while i > 0 and lattice[i] != None:
        word = lattice[i]
        result = word[0] + " " + result
        i -= len(word[1])
    print result
"""
