#!/usr/bin/python
#encoding: utf-8

def insertion_sort(a):
    n = len(a)
    for j in range(1,n):
        key = a[j]
        i = j - 1
        while i >= 0 and a[i] > key:
            a[i+1] = a[i]
            i = i-1
        a[i+1] = key
    return a

if __name__ == '__main__':
    a = [5,2,4,6,1,3]
    print insertion_sort(a)

    import random
    a = [random.randrange(1000) for i in range(1000)]
    print insertion_sort(a)

