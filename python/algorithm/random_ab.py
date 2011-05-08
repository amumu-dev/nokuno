#!/usr/bin/env python
import random

def random_ab(a, b):
    result = 0
    for i in range(32):
        result += (random.randint(0,1) << i)
    return result % (b-a+1) + a

if __name__ == '__main__':
    print random_ab(1, 10)
