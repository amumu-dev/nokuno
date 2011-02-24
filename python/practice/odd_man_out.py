#!/usr/bin/enb python
import sys

N = int(sys.stdin.readline())
#print "N: ", N

for i in range(1, N+1):
    G = sys.stdin.readline()
    if not G: break
    #print "G: ", G
    dic = {}
    input = sys.stdin.readline().strip().split(" ")
    for C in input:
        C = int(C)
        dic[C] = dic.get(C, 0) + 1
    for C, count in dic.items():
        if count == 1:
            output = C
    print "Case #%d: %d" % (i, output)

