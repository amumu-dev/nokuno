#!/usr/bin/env python
from sys import stdin

if __name__ == "__main__":
    for line in stdin:
        splited = line.strip().split("\t", 1)
        if len(splited) == 2:
            print splited[1] + "\t" + splited[0]
