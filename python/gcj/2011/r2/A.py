#!/usr/bin/env python
import sys

T = int(sys.stdin.readline())

for x in range(1, T+1):
    (X, S, R, t, N) = [float(i) for i in sys.stdin.readline().strip().split(" ")]
    N = int(N)
    walkways = []
    total = 0.
    for i in range(N):
        (B, E, w) = [float(i) for i in sys.stdin.readline().strip().split(" ")]
        walkways.append((E-B, S+w))
        total += E-B
    if X > total:
        walkways.append((X-total, S))
    walkways.sort(key=lambda x: x[1])
    y = 0.0
    run = R-S
    for (length, speed) in walkways:
        t_run = length / (speed + run)
        if t >= t_run:
            y += t_run
            t -= t_run
        elif t == 0.:
            y += length / speed
        else:
            l = (speed+run) * t
            y += l / (speed+run) + (length-l) / speed
            t = 0.
    print "Case #%d: %s" % (x, str(y))
