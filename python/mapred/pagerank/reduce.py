#!/usr/bin/env python
from sys import stdin

def reduce(key, values):
    graph = None
    total = 0.

    for value in values:
        splited = value.strip().split("\t", 1)

        if len(splited) == 2:   # graph case
            graph = splited[1]
        else:   # pagerank case
            total += float(splited[0])

    if total > 0.:
        print "%s\t%f\t%s" % (current, total, graph)

if __name__ == "__main__":
    current = None
    values = []

    for line in stdin:
        splited = line.strip().split("\t", 1)
        if len(splited) != 2:
            continue
        key, value = splited

        if current != None and current != key:
            reduce(current, values)
            values = []

        current = key
        values += [value]

    reduce(current, values)
