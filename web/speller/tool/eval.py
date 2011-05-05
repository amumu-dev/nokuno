#!/usr/bin/env python
import sys
import urllib
import optparse
import time

# parse option
base = "http://nokuno.shisobu.in/speller/noop/"
parser = optparse.OptionParser()
parser.add_option("-f", dest="file", default="dataset.txt")
parser.add_option("-u", dest="url", default=base)
(options, args) = parser.parse_args()
start = time.time()

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
precision_sum = 0
recall_sum = 0
for key in dic.keys():
    url = options.url + '?' + urllib.urlencode({'q':key})
    for line in urllib.urlopen(url):
        pair = line.strip().split("\t", 1)
        if len(pair) != 2: continue
        (cand, prob) = pair
        prob = float(prob)
        if cand in dic[key]:
            precision_sum += prob
            recall_sum += 1.0 / len(dic[key])

# output evaluate
latency = (time() - start) / len(dic)
print "latency(s):", latency

ep = precision_sum / len(dic)
er = recall_sum / len(dic)

print "EP:", ep
print "ER:", er

ef1 = 1/(0.5*(1/ep+1/er))
print "EF1:", ef1
