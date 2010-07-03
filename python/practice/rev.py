#!/usr/bin/python
import math

def revstr(num):
    lnum = list(str(num))
    lnum.reverse()
    return int(''.join(lnum))

def revnum(num):
    m = int(math.log10(num)) + 1
    result = 0
    for k in range(0,m):
        base = 10 ** k
        knum = int(num % (base*10) / base)
        nbase = 10 ** (m-k-1)
        result += knum * nbase
    return result

print revstr(123)
print revnum(123)
