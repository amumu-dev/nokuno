#!/usr/bin/python

def binary_search(a,v):
    left = 0
    right = len(a)
    while right - left > 0:
        middle = (left + right) / 2 
        if v == a[middle]:
            return middle
        elif v < a[middle]:
            right = middle
        else:
            left = middle + 1

def sum_search(a,x):
    for i in range(len(a)):
        result = binary_search(a[i+1:],x-a[i])
        if result != None:
            return i, result+i+1

if __name__ == '__main__':
    a = [0,1,2,3,4,5,6]
    print sum_search(a,5)
    a = [0,2,3]
    print sum_search(a,5)
    print sum_search(a,4)
