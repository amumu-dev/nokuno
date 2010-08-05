#!/usr/bin/env python
from random import random
from operator import mul
from math import log, exp, sqrt, pi

def factorial(x):
    return reduce(mul, xrange(1, x+1))

def poisson(x, mu):
    return (mu ** x) / factorial(x) * exp(-mu)

def normalize(p):
    d = sum(p)
    return [e / d for e in p]

# test data
x = [1,2,1,10,11,10]
N = len(x)

#initialize
K = 2
mu = [random() * 10.0 for k in range(K)]
p_c = [0] * N

#iteration
for loop in range(10):
    # e-step
    for i in range(N):
        p_c[i] = normalize([poisson(x[i], mu[k]) for k in range(K)])

    # m-step
    for k in range(K):
        mu[k] = sum([p_c[i][k] * x[i] for i in range(N)]) / sum([p_c[i][k] for i in range(N)])
    
    # log likelihood
    L = 0
    for i in range(N):
        p = [p_c[i][k] * poisson(x[i], mu[k]) for k in range(K)]
        L += log(sum(p))

    print 'mu = ', mu, 'L = ', L

