#!/usr/bin/env python
#encoding: utf-8
from sys import stdin
from optparse import OptionParser
from format import format
from inspect import getmembers

parser = OptionParser()
parser.add_option("-d", dest="dictionary", default="data/dictionary.txt")
parser.add_option("-c", dest="connection", default="data/connection.txt")
parser.add_option("-s", dest="separator", default="\t")
parser.add_option("-o", dest="output", action="store_true")
(o, args) = parser.parse_args()

#lattice node
class Node:
    def __init__(self, yomi, word, pos, prob, index, total=0.0, back=None):
        self.yomi = yomi
        self.word = word
        self.pos = pos
        self.prob = prob
        self.index = index
        self.total = total
        self.back = back
    def __str__(self):
        return format((self.yomi, self.word, self.pos, self.prob, self.total,self.index,self.back))

#load dictionary
dictionary = {}
for line in open(o.dictionary):
    (yomi, word, pos, prob) = line.strip().split(o.separator, 3)
    prob = float(prob)
    dictionary.setdefault(yomi, [])
    dictionary[yomi].append([yomi, word, pos, prob])

#load connection
connection = {}
for line in open(o.connection):
    (left, right, prob) = line.strip().split(o.separator, 2)
    prob = float(prob)
    key = left + "_" + right
    connection[key] = prob

#input from stdin
for line in stdin:
    input = line.strip()
    length = len(input)

    #create lattice
    lattice = [[] for i in range(length+2)]
    lattice[0].append(Node(' ', '<S>', 'その他', 1.0, 0, 1.0))
    lattice[-1].append(Node(' ', '</S>', 'その他', 1.0, 0))
    for i in range(length):
        for j in range(i+1, length+1):
            yomi = input[i:j]
            for yomi, word, pos, prob in dictionary.get(yomi, []):
                index = len(lattice[j])
                node = Node(yomi, word, pos, prob, index)
                lattice[j].append(node)

    #forward search
    for i in range(1, length+2):
        for right in lattice[i]:
            j = i - len(right.yomi)
            if len(lattice[j]) == 0:
                break
            def score(left):
                return left.total * connection.get(left.pos+"_"+right.pos, 0.0)
            best = max(lattice[j], key=score)
            right.total = right.prob * score(best)
            right.back = best.index
    if o.output:
        for node in lattice: print format(node)

    #back trace
    current = length
    position = 0
    result = ""
    while current > 0:
        node = lattice[current][position]
        result = node.word + " " + result
        position = node.index
        current -= len(node.yomi)
    print result

