#!/usr/bin/python

def binary_search_recursive(a,v):
    if a == []:
        return
    middle = len(a) / 2
    if v == a[middle]:
        return middle
    elif v < a[middle]:
        return binary_search_recursive(a[0:middle],v)
    else:
        return middle + binary_search_recursive(a[middle:len(a)],v)

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

if __name__ == '__main__':
    a = [0,1,2,3,4,8,9]
    print binary_search(a,4)
    print binary_search(a,-1)
    print binary_search(range(100),90)

    print binary_search_recursive(a,9)
    print binary_search_recursive(a,-1)
    print binary_search_recursive(range(100),90)
