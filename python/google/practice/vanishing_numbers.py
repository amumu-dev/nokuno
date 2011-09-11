#!/usr/bin/env python
import sys

def eliminate_stage(num):

def eliminate_order(numbers):
    result = []
    update = True
    while update:
        update = False
        for num in numbers:
            if eliminate_stage(num):
                result.append(num)
    return result

T = int(sys.stdin.readline())

for i in range(1, T+1):
    #read
    N = int(sys.stdin.readline())
    numbers = []
    for j in range(0,N):
        num = float(sys.stdin.readline())
        numbers.append(num)
    numbers.sort()
    result = eliminate_order(numbers)

    #output
    print "Case #%d:" % (i)
    for num in result:
        print num
