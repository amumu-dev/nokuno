#!/usr/bin/python

def linear_search(a,v):
    for i in range(len(a)):
        if a[i] == v:
            return i

if __name__ == '__main__':
    a = [8,1,3,4,9,0,2]
    print linear_search(a,9)
    print linear_search(a,-1)

    import random
    a = [random.randrange(100) for i in range(100)]
    print a
    print linear_search(a,1)

