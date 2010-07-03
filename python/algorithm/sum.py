#!/usr/bin/python

def sum(a,b):
    n = len(a)
    carry = 0
    c = range(n+1)
    for i in range(n):
        c[i] = (a[i] + b[i] + carry) % 2
        carry = (a[i] + b[i] + carry) / 2
    c[n] = carry
    return c

if __name__ == '__main__':
    a = [0,1,0]
    b = [1,0,1]
    print sum(a,b)

    a = [1,0,1]
    b = [1,1,1]
    print sum(a,b)
