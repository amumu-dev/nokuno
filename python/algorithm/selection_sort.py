#!/usr/bin/python

def selection_sort(a):
    n = len(a)
    for j in range(0,n-1):
        k = j;
        for i in range(j+1,n):
            if a[k] > a[i]:
                k = i
        min = a[k]
        a[k] = a[j]
        a[j] = min
    return a

if __name__ == '__main__':
    a = [5,2,4,6,1,3]
    print selection_sort(a)

    import random
    a = [random.randrange(1000) for i in range(1000)]
    print selection_sort(a)

