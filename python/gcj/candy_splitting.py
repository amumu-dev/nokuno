#!/usr/bin/env python
import sys

def is_no(C):
    for i in range(21):
        number_of_one = 0
        for j in range(len(C)):
            if (C[j] >> i) & 1:
                number_of_one += 1
        if number_of_one % 2 == 1:
            return True
    return False

T = int(sys.stdin.readline())

for x in range(1, T+1):
    N = int(sys.stdin.readline())
    C = [int(i) for i in sys.stdin.readline().strip().split(" ")]
    if is_no(C):
        print "Case #%d: NO" % (x)
    else:
        y = sum(C) - min(C)
        print "Case #%d: %d" % (x, y)

