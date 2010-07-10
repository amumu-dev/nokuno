#!/usr/bin/python
k = 2

def forward(phi, p0):
    alpha = [p0]
    for p in phi:
        alpha.append(
            [sum(p[i][j]*alpha[len(alpha)-1][i]
            for i in range(k))
            for j in range(k)])
    return alpha

def backward(phi):
    beta = [[1] * k]
    for p in phi:
        beta.append(
            [sum(p[j][i]*beta[len(beta)-1][j]
            for i in range(k))
            for j in range(k)])
    return beta

def productsum(phi, p0):
    alpha = forward(phi, p0)
    beta = backward(phi)
    return [[alpha[i][j]*beta[i][j]
        for j in range(k)]
        for i in range(len(phi))]

def productsum2(phi, p0):
    alpha = forward(phi, p0)
    beta = backward(phi)
    return [[[alpha[i][j]*beta[i+1][h]*phi[i][j][h]
        for h in range(k)]
        for j in range(k)]
        for i in range(len(phi))]

def display(result):
    for i in range(len(result)):
        print i, ':', result[i]

if __name__ == '__main__':
    #init and cool down 
    p = [[0, 1],[0.5, 0.5]]
    phi = [p] * 10
    p0 = [0.5, 0.5]
    print "p:", p
    display( productsum(phi, p0) )
    #display( productsum2(phi, p0) )
    print

    #reverse state always
    p = [[0, 1],[1, 0]]
    phi = [p] * 10
    p0 = [0.75, 0.25]
    print "p:", p
    display( productsum(phi, p0) )
    #display( productsum2(phi, p0) )

