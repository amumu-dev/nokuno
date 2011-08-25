#!/usr/bin/env python
from sys import stdin

if __name__ == "__main__":
    for line in stdin:
        splited = line.strip().split("\t", 2)
        if len(splited) != 3:
            continue

        (nid, pagerank, adjacency) = splited

        adjacency = adjacency.split("\t")
        pagerank = float(pagerank)

        if pagerank == 0. or len(adjacency) == 0:
            continue

        print line,

        value = pagerank / len(adjacency)

        for node in adjacency:
            print "%s\t%f" % (node, value)
