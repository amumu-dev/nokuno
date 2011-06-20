#!/usr/bin/env python
import random

def random_sampling_no_duplicate(a, n):
    for i in range(n):
        index = random.randint(i,len(a)-1)
        a[i],a[index] = a[index],a[i]
    return a[:n]

def random_sampling_with_duplicate(a, n):
    result = []
    for i in range(n):
        index = random.randint(0,len(a)-1)
        result.append(a[index])
    return result

if __name__ == '__main__':
    print random_sampling_no_duplicate(range(20), 10)
    print random_sampling_with_duplicate(range(20), 10)
