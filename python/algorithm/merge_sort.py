#!/usr/bin/python

def merge(left,right):
    result = []
    while left != [] and right != []:
        if left[0] < right[0]:
            result.append(left.pop(0))
        else:
            result.append(right.pop(0))
    result.extend(left)
    result.extend(right)
    return result

def merge_sort(a):
    n = len(a)
    if n == 1:
        return a
    left = merge_sort(a[0:n/2])
    right = merge_sort(a[n/2:n])
    return merge(left,right)


def merge2(a, left, mid, right):
    l = left
    r = mid
    i = 0
    result = [0] * (right-left)
    while l < mid and r < right:
        if a[l] < a[r]:
            result[i] = a[l]
            l += 1
        else:
            result[i] = a[r]
            r += 1
        i += 1
    if l < mid:
        result[i:] = a[l:mid]
    else:
        result[i:] = a[r:right]
    a[left:right] = result

def merge_sort2(a, left, right):
    if right-left == 1:
        return
    mid = (left+right)/2
    merge_sort2(a, left, mid)
    merge_sort2(a, mid, right)
    merge2(a,left,mid,right)

if __name__ == '__main__':
    a = [5,2,4,6,1,3]
    print merge_sort(a)
    merge_sort2(a,0,len(a))
    print a

    import random
    a = [random.randrange(10000) for i in range(100000)]
    merge_sort2(a,0,len(a))
