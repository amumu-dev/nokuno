#!/usr/bin/env python
import sys

T = int(sys.stdin.readline())

for x in range(1, T+1):
    # parse
    row = sys.stdin.readline().strip().split(" ")
    C = int(row.pop(0))
    combine = row[:C]
    row = row[C:]
    D = int(row.pop(0))
    opposed = row[:D]
    row = row[D:]
    N = int(row.pop(0))
    input = row[-1]
    
    # preprocess
    cdic = {}
    for c in combine:
        cdic[c[0]+c[1]] = c[2]
        cdic[c[1]+c[0]] = c[2]
    oset = set()
    for o in opposed:
        oset.add(o[0]+o[1])
        oset.add(o[1]+o[0])
    # process input
    result = ""
    for i in range(N):
        result += input[i]
        #search combine
        if len(result) > 1 and result[-2:] in cdic:
            result = result[:-2] + cdic[result[-2:]]
        #search opposed
        if len(result) > 0:
            for j in range(0, len(result)-1):
                if (result[-1] + result[j]) in oset:
                    result = ""
                    break

    print "Case #%d: [%s]" % (x, ', '.join(result))

