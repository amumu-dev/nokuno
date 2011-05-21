#!/usr/bin/env python
import sys

T = int(sys.stdin.readline())

for x in range(1, T+1):
    N = int(sys.stdin.readline())
    A = [int(i) for i in sys.stdin.readline().strip().split(" ")]
    y = 0.0
    for i in range(N):
        if A[i] != i+1:
            y += 1.0
    print "Case #%d: %f" % (x, y)

