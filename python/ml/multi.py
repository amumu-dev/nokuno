#!/usr/bin/env python
from random import random
from operator import mul
from math import log, exp

def factorial(x):
    if x == 0: return 1
    return reduce(mul, xrange(1, x+1))

def prod(x):
    return reduce(mul, x)

def normalize(P):
    return [p / sum(P) for p in P]

def multi(d, q):
    return prod([q[w] ** d[w] for w in range(W)])

def multinomial(d, q):
    return factorial(sum(d)) / prod([factorial(d[w]) for w in range(W)]) * multi(d,q)

# test data
D = [[8,2,0],[9,1,0],[0,2,8],[0,1,9]]
N = len(D)
print 'D = ', D

#initialize
W = 3
K = 2
Q = [normalize([random() for w in range(W)]) for k in range(K)]
C = [None] * N
print 'Q = ', Q

#iteration
for loop in range(10):
    # e-step
    for n in range(N):
        C[n] = normalize([multi(D[n], Q[k]) for k in range(K)])

    # m-step
    for k in range(K):
        Q[k] = normalize([sum([C[n][k] * D[n][w] for n in range(N)]) for w in range(W)])

    # log likelihood
    L = 0
    for n in range(N):
        p = [C[n][k] * multinomial(D[n], Q[k]) for k in range(K)]
        L += log(sum(p))

    print 'L = ', L, 'C = ', C

