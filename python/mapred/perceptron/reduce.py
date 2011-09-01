#!/usr/bin/env python
from sys import stdin
from optparse import OptionParser
from collections import defaultdict

def reduce(label, values):
    weight = defaultdict(float)

    # summation
    for value in values:
        for feature in value.split(" "):
            pair = feature.split(":")
            if len(pair) != 2: continue
            k, v = pair
            weight[k] += float(v)

    # averaging
    for k in weight.iterkeys():
        weight[k] /= len(values)

    weight_str = " ".join(k + ":" + str(v) for k, v in weight.iteritems())
    print "%s %s" % (label, weight_str)

if __name__ == "__main__":
    current = None
    values = []

    for line in stdin:
        splited = line.strip().split(" ", 1)
        if len(splited) != 2:
            continue
        key, value = splited

        if current != None and current != key:
            reduce(current, values)
            values = []

        current = key
        values += [value]

    reduce(current, values)
