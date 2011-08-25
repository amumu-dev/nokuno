#!/usr/bin/env python
from sys import stdin

def reduce(key, values):
    initial = 1.0
    print "%s\t%f\t%s" % (key, initial, "\t".join(values))

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
