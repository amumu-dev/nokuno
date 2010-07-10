#!/bin/env python
import random
K = 2

def emission(x, z, mu):
    return mu[z][x]

def forward(X, A, pi, mu):
    l = len(X)
    # \alpha(z_1=k) = \pi_k * p(x_1|\phi_k) (13.37)
    alpha = [[pi[k] * emission(X[0], k, mu) for k in range(K)]]
    for x in X[1:]:
        # \alpha(z_n) = p(x_n|z_n) \sum_{z_{n-1}} \alpha(z_{n-1}) p(z_n|z_{n-1}) (13.36)
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
        # \beta(z_n) = \sum_{z_{n+1}} \beta(z_{n+1}) p(x_{n+1}|z_{n+1}) p(z_{n+1}|z_n) (13.38)
        beta.insert(0,
            [sum(beta[0][i] * emission(x, i, mu) * A[j][i]
            for i in range(K))
            for j in range(K)])
    return beta

def likelyhood(X, A, pi, mu):
    # (13.42)
    alpha = forward(X, A, pi, mu)
    return sum(alpha[-1])

def likelyhood2(X, A, pi, mu):
    beta = backward(X, A, mu)
    alpha_0 = [pi[k] * emission(X[0], k, mu) for k in range(K)]
    return sum(alpha_0[k] * beta[0][k] for k in range(K))

def get_gamma(X, A, pi, mu):
    alpha = forward(X, A, pi, mu)
    beta = backward(X, A, mu)
    L = likelyhood(X, A, pi, mu)
    # (13.33)
    return [[alpha[i][j] * beta[i][j] / L
        for j in range(K)]
        for i in range(len(X))]

def get_xi(X, A, pi, mu):
    alpha = forward(X, A, pi, mu)
    beta = backward(X, A, mu)
    L = likelyhood(X, A, pi, mu)
    # (13.43)
    return [[[alpha[i][j] * emission(X[i+1], h, mu) * A[j][h] * beta[i+1][h] / L
        for h in range(K)]
        for j in range(K)]
        for i in range(len(X)-1)]

def test(X):
    A = [[0, 1],[1, 0]]     # A[i][j] = p(z_n=j|z_{n-1}=i)
    pi = [0.75, 0.25]       # pi[i] = p(z_0=i)
    mu = [[1, 0, 0],[0, 0.5, 0.5]]  # mu[i][j] = p(x_n=j|z_n=i)
    print 'A:', A
    print 'X:', X
    print 'pi:', pi
    print 'mu:', mu
    print 'alpha:', forward(X, A, pi, mu)
    print 'beta:', backward(X, A, mu)
    print 'likelyhood:', likelyhood(X, A, pi, mu)
    print 'likelyhood2:', likelyhood2(X, A, pi, mu)
    print 'gamma:', get_gamma(X, A, pi, mu)
    print 'xi:', get_xi(X, A, pi, mu)

def init(d):
    p = [random.random() for i in range(d)]
    return normalize(p)

def normalize(p):
    d = len(p)
    s = sum(p)
    result = [p[i] / s for i in range(d)]
    for i in range(len(result)):
        if result[i] < 0.00001:
            result[i] = 0
        if result[i] > 0.99999:
            result[i] = 1

    return result

def em_algorithm(X):
    # init
    pi = init(K)       # pi[i] = p(z_0=i)
    A = [init(K) for k in range(K)]     # A[i][j] = p(z_n=j|z_{n-1}=i)
    D = 3
    mu = [init(D) for k in range(K)]    # mu[i][j] = p(x_n=j|z_n=i)
    N = len(X)
    print 'X:', X
    print 'A:', A
    print 'pi:', pi
    print 'mu:', mu
    print 'likelyhood:', likelyhood(X, A, pi, mu)
    for loop in range(10):
        # E-step
        gamma = get_gamma(X, A, pi, mu)
        xi = get_xi(X, A, pi, mu)

        # M-step
        pi = normalize([gamma[0][k] for k in range(K)])
        A = [normalize([sum([xi[n][j][k] for n in range(N-1)]) for j in range(K)]) for k in range(K)]
        mu = [normalize([sum([gamma[n][k] for n in range(N) if X[n] == i]) for i in range(D)]) for k in range(K)] 
        print 'likelyhood:', likelyhood(X, A, pi, mu)
    
    print 'pi:', pi
    print 'A:', A
    print 'mu:', mu

if __name__ == '__main__':
    #test data
    X = [0, 2, 0, 1, 0, 2]  # X[i] = x_i
    em_algorithm(X)

