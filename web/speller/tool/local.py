#!/usr/bin/env python
import sys
import urllib
import optparse

# parse option
parser = optparse.OptionParser()
parser.add_option("-f", dest="file", default="dataset.txt")
(options, args) = parser.parse_args()

# load dictionary
dic = {}
correct_num = 0
for line in open(options.file):
    line = line.strip().split("\t")
    key = line[0]
    values = line[1:]
    dic[key] = values
    correct_num += len(values)

# evaluate speller
precision_sum = 0.0
recall_sum = 0.0
for line in sys.stdin:
    line = line.strip().split("\t")
    if len(line) < 2: continue
    key = line[0]
    values = line[1:]
    #update precision
    if values[0] in dic[key]:
        precision_sum += 1.0
    #update recall
    for value in values:
        if value in dic[key]:
            recall_sum += 1.0 / len(dic[key])

# output evaluate
ep = precision_sum / len(dic)
er = recall_sum / len(dic)

print "EP:", ep
print "ER:", er

ef1 = 1/(0.5*(1/ep+1/er))
print "EF1:", ef1
