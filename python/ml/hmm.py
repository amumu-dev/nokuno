#!/bin/env python
import random
K = 2

def emission(x, z, mu):
    return mu[z][x]

def forward(X, A, pi, mu):
    l = len(X)
    # (13.37)
    alpha = [[pi[k] * emission(X[0], k, mu) for k in range(K)]]
    for x in X[1:]:
        # (13.36)
        alpha.append(
            [emission(x, j, mu) *
            sum(A[i][j]*alpha[-1][i]
            for i in range(K))
            for j in range(K)])
    return alpha

def backward(X, A, mu):
    l = len(X)
    beta = [[1] * K]    # \beta(z_N) = 1
    for x in reversed(X[1:]):
        # (13.38)
        beta.insert(0,
            [sum(beta[0][i] * emission(x, i, mu) * A[j][i]
            for i in range(K))
            for j in range(K)])
    return beta

def likelyhood(X, A, pi, mu):
    # (13.42)
    alpha = forward(X, A, pi, mu)
    return sum(alpha[-1])

def forward_backward(X, A, pi, mu):
    alpha = forward(X, A, pi, mu)
    beta = backward(X, A, mu)
    L = likelyhood(X, A, pi, mu)

    # (13.33)
    gamma = [[alpha[i][j] * beta[i][j] / L
        for j in range(K)]
        for i in range(len(X))]

    # (13.43)
    xi = [[[alpha[i][j] * emission(X[i+1], h, mu) * A[j][h] * beta[i+1][h] / L
        for h in range(K)]
        for j in range(K)]
        for i in range(len(X)-1)]
    return gamma, xi, L

def init(d):
    p = [random.random() for i in range(d)]
    return normalize(p)

def normalize(p):
    d = len(p)
    s = sum(p)
    if s != 0.0:
        result = [p[i] / s for i in range(d)]
    else:
        result = [1.0 / d] * d
    return result

def display_param(A, pi, mu):
    print 'A:', A
    print 'pi:', pi
    print 'mu:', mu

def em_algorithm(X):
    # init
    pi = init(K)       # pi[i] = p(z_0=i)
    A = [init(K) for k in range(K)]     # A[i][j] = p(z_n=j|z_{n-1}=i)
    D = 3
    mu = [init(D) for k in range(K)]    # mu[i][j] = p(x_n=j|z_n=i)
    N = len(X)
    print 'X:', X
    display_param(A, pi, mu)
    for loop in range(10):
        # E-step
        (gamma, xi, L) = forward_backward(X, A, pi, mu)

        # M-step
        pi = normalize([gamma[0][k] for k in range(K)])
        A = [normalize([sum([xi[n][j][k] for n in range(N-1)]) for j in range(K)]) for k in range(K)]
        mu = [normalize([sum([gamma[n][k] for n in range(N) if X[n] == i]) for i in range(D)]) for k in range(K)] 
        print 'likelyhood:', L
    
    print 'likelyhood:', likelyhood(X, A, pi, mu)
    display_param(A, pi, mu)

if __name__ == '__main__':
    #test data
    X = [0, 2, 0, 1, 0, 2]  # X[i] = x_i
    em_algorithm(X)

