#!/usr/bin/env python
from random import random

#data set
x = [0,5,2,8,-1,9]
N = len(x)
print 'x = ', x

#initialize
K = 2
m = [random() * 10.0 for k in range(K)]
c = [0] * N
print 'm = ', m

#iteration
for loop in range(10):
    for i in range(N):
        c[i] = min([(abs(m[k]-x[i]), k) for k in range(K)])[1]
    for k in range(K):
        s = [x[i] for i in range(N) if c[i] == k]
        m[k] = sum(s) / len(s)
    print 'm = ', m, 'c = ', c

