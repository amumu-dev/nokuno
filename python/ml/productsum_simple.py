#!/usr/bin/python
k = 2

def forward(phi, alpha):
    for p in phi:
        alpha = [sum(p[i][j]*alpha[i] for i in range(k)) for j in range(k)]
    return alpha

def backward(phi):
    beta = [1] * k
    for p in phi:
        beta = [sum(p[j][i]*beta[j] for i in range(k)) for j in range(k)]
    return beta

def productsum(phi, alpha, n):
    alpha = forward(phi[:n], alpha)
    beta = backward(phi[n:])
    n = len(alpha)
    return [alpha[i]*beta[i] for i in range(n)]

if __name__ == '__main__':
    p = [[0.25, 0.75],[0.5, 0.5]]
    p = [[0, 1],[1, 0]]
    phi = [p]*100
    alpha = [0.75, 0.25]

    result = productsum(phi, alpha, 5)
    print result

