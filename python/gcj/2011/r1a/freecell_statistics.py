#!/usr/bin/env python
import sys

T = int(sys.stdin.readline())

for x in range(1, T+1):
    (N, PD, PG) = [int(i) for i in sys.stdin.readline().strip().split(" ")]
    if (PG == 0 and PD != 0) or (PG == 100 and PD != 100):
        print "Case #%d: Broken" % (x)
        continue
    y = False
    for i in range(1, 101):
        if PD % i == 0 and 100 % i == 0 and 100 / i <= N:
            y = True
            break
    if y:
        print "Case #%d: Possible" % (x)
    else:
        print "Case #%d: Broken" % (x)
