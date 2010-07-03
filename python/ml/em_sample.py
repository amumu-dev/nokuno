#!/usr/bin/python
# EM algorithm for the 'marble game'
# see 'Data Intensive Text Processing with MapReduce' at p.104-108
# http://www.umiacs.umd.edu/~jimmylin/book.html
from random import random
from math import log

#dataset
(na, nb, nc) = (200, 1, 100)
n = na + nb + nc

#initialize
(p0, p1, p2) = (random(), random(), random())

for i in range(5):
    #log likelyhood
    l = na * log((1-p0)*(1-p1)) + nb * log((1-p0)*p1+p0*(1-p2)) + nc * log(p0*p2)
    print l, p0, p1, p2
    #e-step
    b = (1-p0)*p1 + p0*(1-p2)
    r1 = (1-p0)*p1 / b
    r2 = p0*(1-p2) / b
    #m-step
    p0 = (r2 * nb + nc) / n
    p1 = r1 * nb / (na + r1*nb)
    p2 = nc / (nc + r2*nb)

