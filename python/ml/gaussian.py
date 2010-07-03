#!/usr/bin/python
# Gaussian mixture with EM algorithm
from random import random
from math import log, exp, sqrt, pi

def gauss(x, mu, sigma):
    return 1.0 / sqrt(2.0 * pi * sigma**2) * exp( -(x-mu)**2/(2*sigma**2))

def normalize(p):
    d = sum(p)
    return [e / d for e in p]

#dataset
x_n = [0,5,2,8,-1,9]
N = len(x_n)
print 'x_n = ', x_n

#sigma
sigma = 1.0
   
#initialize
K = 3
mu_k = [random() * 5.0 for k in range(K)]
pi_k = normalize([random() for k in range(K)])

#iteration
for i in range(10):
    #e-step
    gamma = []
    for n in range(N):
        elements = [gauss(x_n[n], mu_k[k], sigma) * pi_k[k] for k in range(K)]
        gamma.append(normalize(elements))

    #log likelyhood
    loglikelyhood = 0
    for n in range(N):
        p = [pi_k[k] * gauss(x_n[n], mu_k[k], sigma) for k in range(K)]
        loglikelyhood += log(sum(p))
    print 'loglikelyhood = ', loglikelyhood,'\t', 

    #m-step
    for k in range(K):
        n_k = sum([gamma[n][k] for n in range(N)])
        elements = [gamma[n][k] * x_n[n] for n in range(N)]
        mu_k[k] = sum(elements) / n_k
        pi_k[k] = sum([gamma[n][k] for n in range(N)])
    pi_k = normalize(pi_k)
    print 'mu_k = ', mu_k
