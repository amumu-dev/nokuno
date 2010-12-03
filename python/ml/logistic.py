#!/usr/bin/env python
import math

eta0 = 0.1      # Initial learning rate; change this if desired.
num = 10000    # number of iteration

def update(W, X, l, eta):
    D = len(X)

    # Compute the inner product of features and their weights.
    a = sum(W[i] * X[i] for i in range(D))

    # Compute the gradient of the error function
    g = (1 / (1 + math.exp(-a))) - l

    # Update the feature weights by Stochastic Gradient Descent.
    for i in range(D):
        W[i] -= eta * g * X[i]

def train(dataset):
    t = 1
    W = [0] * (len(dataset[0])-1)
    # Loop for instances.
    for i in range(num):
        for data in dataset:
            update(W, data[1:], data[0], eta0 / (1 + t / len(dataset)))
            t += 1
    return W

if __name__ == '__main__':
    # data format: (label, feature1, featrue2, ..)
    dataset = [(0,0,0,1), (0,1,0,1), (1,0,1,0), (1,1,1,0)]
    W = train(dataset)
    print W
