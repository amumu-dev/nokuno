#!/bin/env python
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
    alpha = forward(X, A, pi, mu)
    return sum(alpha[-1])

def likelyhood2(X, A, pi, mu):
    beta = backward(X, A, mu)
    alpha_0 = [pi[k] * emission(X[0], k, mu) for k in range(K)]
    return sum(alpha_0[k] * beta[0][k] for k in range(K))

def gamma(X, A, pi, mu):
    alpha = forward(X, A, pi, mu)
    beta = backward(X, A, mu)
    L = likelyhood(X, A, pi, mu)
    # (13.33)
    return [[alpha[i][j] * beta[i][j] / L
        for j in range(K)]
        for i in range(len(X))]

def xi(X, A, pi, mu):
    alpha = forward(X, A, pi, mu)
    beta = backward(X, A, mu)
    L = likelyhood(X, A, pi, mu)
    # (13.43)
    return [[[alpha[i][j] * emission(X[i+1], h, mu) * A[j][h] * beta[i+1][h] / L
        for h in range(K)]
        for j in range(K)]
        for i in range(len(X)-1)]

def display(result):
    for i in range(len(result)):
        print i, ':', result[i]

if __name__ == '__main__':
    #test data
    A = [[0, 1],[1, 0]]     # A[i][j] = p(z_n=j|z_{n-1}=i)
    X = [0, 2, 0, 1, 0, 2]  # X[i] = x_i
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
    print 'gamma:', gamma(X, A, pi, mu)
    print 'xi:', xi(X, A, pi, mu)

