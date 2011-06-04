#!/usr/bin/env python
import sys

T = int(sys.stdin.readline())

def is_valid(map):
    x = 0
    y = 0
    size = len(map)
    c = (size-1.) / 2.
    for i in range(size):
        for j in range(size):
            if (i==0 or i==size-1) and (j==0 or j==size-1):
                continue
            x += map[i][j] * (j - c)
            y += map[i][j] * (i - c)
    if x == 0. and y== 0.:
        return True
    return False

def solve(map):
    for y in range(min(R,C), 2, -1):
        for i in range(R-y+1):
            for j in range(C-y+1):
                submap = [line[j:j+y] for line in map[i:i+y]]
                if is_valid(submap):
                    return y
    return 0

for x in range(1, T+1):
    (R,C,D) = [int(i) for i in sys.stdin.readline().strip().split(" ")]
    map = []
    for i in range(R):
        line = [int(i) for i in sys.stdin.readline().strip()]
        map.append(line)

    y = solve(map)

    if y == 0:
        print "Case #%d: IMPOSSIBLE" % (x)
    else:
        print "Case #%d: %d" % (x, y)
