#!/usr/bin/python
import sys

table = {}
for line in sys.stdin:
    key = line.strip()
    if key in table:
        table[key] += 1
    else:
        table[key] = 1

items = sorted(table.items(), key=lambda x:x[1], reverse=True)
for i in range(min(5,items)):
    print items[i]
