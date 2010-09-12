#!/usr/bin/python
#encoding: utf-8
import sys

title = ""
current = []
for line in sys.stdin:
    words = line.strip().split(" ")
    if len(words) == 0:
        continue
    elif words[0] == "[[" and words[-1] == "]]":
        if title != "":
            print title + "\t" + " ".join(current)
        title = "".join(words[1:-1])
        current = []
    else:
        current.extend(words)
