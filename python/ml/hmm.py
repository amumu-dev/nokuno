#!/bin/env python
K = 2

def emission(x, z, mu):
    return mu[z][x]

def forward(X, A, pi, mu):
    l = len(X)
    alpha = [pi]
    for x in X:
        alpha.append(
            [emission(x, j, mu) *
            sum(A[i][j]*alpha[-1][i]
            for i in range(K))
            for j in range(K)])
    return alpha

def backward(X, A, mu):
    beta = [[1] * K]
    for x in X:
        beta.append(
            [sum(A[j][i]*beta[-1][j]*emission(X[i], i, mu)
            for i in range(K))
            for j in range(K)])
    return beta

def likelyhood(X, A, pi, mu):
    alpha = forward(X, A, pi, mu)
    return sum(alpha[-1])

def baum_welch(X, A, pi, mu):
    alpha = forward(X, A, pi, mu)
    beta = backward(X, A, mu)
    return [[alpha[i][j]*beta[i][j]
        for j in range(K)]
        for i in range(len(X))]

def baum_welch2(X, A, pi, mu):
    alpha = forward(X, A, pi, mu)
    beta = backward(X, A, mu)
    L = likelyhood(X, A, pi, mu)
    return [[[alpha[i][j]*beta[i+1][h]*A[j][h]*emission(X[i], h, mu)
        for h in range(K)]
        for j in range(K)]
        for i in range(len(X))]

def display(result):
    for i in range(len(result)):
        print i, ':', result[i]

if __name__ == '__main__':
    #test data
    A = [[0, 1],[1, 0]]
    X = [0, 2, 0, 1, 0, 2]
    pi = [0.75, 0.25]
    mu = [[1, 0, 0],[0, 0.5, 0.5]]
    print "A:", A
    print "X:", X
    print "pi:", pi
    print "mu:", mu
    result = baum_welch(X, A, pi, mu)
    result = baum_welch2(X, A, pi, mu)
    display(result)
    L = likelyhood(X, A, pi, mu)
    print "likelyhood:", L

