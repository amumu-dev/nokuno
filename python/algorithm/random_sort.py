#!/usr/bin/python
import random

def random_sort(a):
    n = len(a)
    p = [random.random() for i in range(n)]
    def compare(x,y):
        return cmp(p[x],p[y])
    a.sort(cmp = compare)
    return a

def random_sort_orig(a):
    n = len(a)
    result = []
    for i in range(n):
        index = random.randint(0,n-1-i)
        value = a.pop(index)
        result.append(value)
    return result

if __name__ == '__main__':
    print random_sort(range(5))
    print random_sort_orig(range(5))
    print "start sort"
    random_sort(range(100000))
    print "end sort"
    print "start original"
    random_sort_orig(range(100000))
    print "end original"
