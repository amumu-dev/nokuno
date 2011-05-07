#!/usr/bin/env python
import sys

test_size = int(sys.stdin.readline())

for x in range(1, test_size+1):
    row = sys.stdin.readline().strip().split(" ")
    number = int(row[0])
    pairs = []
    for i in range(1, 1+number*2, 2):
        color = 0 if row[i] == 'O' else 1
        position = int(row[i+1])
        pairs.append((color, position))
    status = [1, 1]
    y = 0
    for i in range(len(pairs)):
        turn = pairs[i][0]
        rev = int(not turn)
        term = abs(pairs[i][1] - status[turn]) + 1
        y += term
        status[turn] = pairs[i][1]
        for j in range(i+1, len(pairs)):
            if pairs[j][0] == rev:
                if pairs[j][1] > status[rev]:
                    status[rev] = min(pairs[j][1], status[rev]+term)
                else:
                    status[rev] = max(pairs[j][1], status[rev]-term)
                break

    print "Case #%d: %d" % (x, y)

