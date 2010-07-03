#!/usr/bin/python
#encoding: utf-8
import random

def matrix_multiply(a,b):
    n = len(a)
    result = [0] * n
    for i in range(n):
        result[i] = [0] * n
        for j in range(n):
            result[i][j] = 0
            for k in range(n):
                result[i][j] += a[i][k] * b[k][j]
    return result

if __name__ == '__main__':
    a = [[1,0],[0,1]]
    b = [[5,1],[2,1]]
    print matrix_multiply(a,b)

