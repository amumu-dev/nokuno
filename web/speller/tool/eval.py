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
for line in open(options.file):
    line = line.strip().split("\t")
    key = line[0]
    values = line[1:]
    dic[key] = values

# evaluate speller
precision_sum = 0
recall_sum = 0
total_size = 0
max_latency = 0
for key in dic.keys():
    url = options.url + '?' + urllib.urlencode({'q':key})
    precision_numerator = 0.0
    precision_denominator = 0.0
    recall_numerator = 0.0
    recall_denominator = len(dic[key])
    current_start = time.time()
    for line in urllib.urlopen(url):
        total_size += len(line)
        pair = line[:-1].split("\t", 1)
        if len(pair) != 2: continue
        (cand, prob) = pair
        prob = float(prob)
        precision_denominator += prob
        if cand in dic[key]:
            precision_numerator += prob
            recall_numerator += 1.0
            index = dic[key].index(cand)
            dic[key][index] = "___delited___"
    current_latency = time.time() - current_start
    max_latency = max(max_latency, current_latency)
    precision = precision_numerator / precision_denominator
    precision_sum += precision
    recall = recall_numerator / recall_denominator
    recall_sum += recall

# output evaluate
print "total_size(byte):", total_size

average_latency = (time.time() - start) / len(dic)
print "average_latency(s):", average_latency
print "max_latency(s):", max_latency

ep = precision_sum / len(dic)
er = recall_sum / len(dic)

print "EP:", ep
print "ER:", er

ef1 = 1/(0.5*(1/ep+1/er))
print "EF1:", ef1

