#!/usr/bin/env python
from sys import stdin

if __name__ == "__main__":
    for line in stdin:
        words = line.strip().split()
        for word in words:
            print '%s\t%d' % (word, 1)
