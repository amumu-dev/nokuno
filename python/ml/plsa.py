#!/usr/bin/env python
from random import random
from math import log, exp

def normalize(P):
    return [p / sum(P) for p in P]

# test data
D = [[2,10,0],[1,5,0],[0,0,8],[0,1,9]]
N = len(D)
W = len(D[0])
print 'D = ', D

#initialize
K = 5
Q = [normalize([random() for n in range(N)]) for k in range(K)]
R = [normalize([random() for w in range(W)]) for k in range(K)]
P = normalize([random() for k in range(K)])

print 'Q = ', Q
print 'R = ', R

#iteration
for loop in range(10):
    # e-step
    C = [[normalize([Q[k][w] * R[k][w] * P[k] for k in range(K)]) for w in range(W)] for n in range(N)]

    # m-step
    for k in range(K):
        Q[k] = normalize([sum([C[n][w][k] * D[n][w] for w in range(W)]) for n in range(N)])
        R[k] = normalize([sum([C[n][w][k] * D[n][w] for n in range(N)]) for w in range(W)])
    P = normalize([sum(D[n][w] * C[n][w][k] for w in range(W) for n in range(N)) for k in range(K)])

    # log likelihood
    L = sum(D[n][w] * log(sum(Q[k][n] * R[k][w] for k in range(K))) for n in range(N) for w in range(W))
    print 'L = ', L

