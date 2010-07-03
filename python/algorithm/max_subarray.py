#!/usr/bin/python
import random

def max_subarray_linear(a):
    n = len(a)
    e = [0] * n
    s = [0] * n
    l = [0] * n
    r = [0] * n
    m = [0] * n
    for i in range(0,n):
        if i == 0 or s[i-1] <= 0:
            e[i] = i
            s[i] = a[i]
        else:
            e[i] = e[i-1]
            s[i] = s[i-1] + a[i]

        if i == 0:
            l[i] = i
            r[i] = i+1
            m[i] = a[i]
        elif m[i-1] > s[i]:
            l[i] = l[i-1]
            r[i] = r[i-1]
            m[i] = m[i-1]
        else:
            l[i] = e[i]
            r[i] = i+1
            m[i] = s[i]
    return a[l[n-1]:r[n-1]]

def max_subarray_recursive(a):
    n = len(a)
    if n <= 1:
        return a
    left = max_subarray_recursive(a[0:n/2])
    right = max_subarray_recursive(a[n/2:n])
    crossing = max_crossing_subarray(a)
    return max_subarray_three(left,right,crossing)

def max_crossing_subarray(a):
    n = len(a)
    left = n/2
    left_sum = -1000
    right = n/2
    right_sum = -1000
    sum = 0
    for i in range(0,n/2):
        index = n/2-i-1
        sum += a[index]
        if sum > left_sum:
            left_sum = sum
            left = index
    sum = 0
    for i in range(n/2,n):
        sum += a[i]
        if sum > right_sum:
            right_sum = sum
            right = i
    return a[left:right+1]

def max_subarray_three(a,b,c):
    sum_a = sum(a)
    sum_b = sum(b)
    sum_c = sum(c)
    sum_max = max(sum_a, sum_b, sum_c)    
    if sum_max == sum_a:
        return a
    elif sum_max == sum_b:
        return b
    else:
        return c

def max_subarray_all(a):
    max = -1
    result = []
    for i in range(len(a)):
        sum = 0
        for j in range(i, len(a)):
            sum += a[j]
            if sum > max:
                max = sum
                result = a[i:j+1]
    return result

if __name__ == '__main__':
    a = [1,-4,3,-4]
    a = [13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7]
    for i in range(10):
        a = [random.randrange(-10,10) for i in range(10)]
        print a
        #print "original: \t", max_subarray_original(a)
        print "linear: \t", max_subarray_linear(a)
        #print "crossing: \t", max_crossing_subarray(a)
        print "recursive: \t", max_subarray_recursive(a)
        print "all:\t\t", max_subarray_all(a)

    """
    a = [random.randrange(-100,100) for i in range(1000000)]
    print "start linear"
    max_subarray_linear(a)
    print "end linear"
    print "start recursive"
    max_subarray_recursive(a)
    print "end recursive"
    """


"""
def max_subarray_linear(a):
    n = len(a)
    e = [[] for i in range(0,n)]
    s = [0 for i in range(0,n)]
    m = [[] for i in range(0,n)]
    r = [0 for i in range(0,n)]
    for i in range(0,n):
        if i == 0 or s[i-1] <= 0:
            e[i] = [a[i]]
            s[i] = a[i]
        else:
            e[i] = e[i-1][:]
            e[i].append(a[i])
            s[i] = s[i-1] + a[i]

        if i == 0:
            m[i] = [a[i]]
            r[i] = a[i]
        elif r[i-1] > s[i]:
            m[i] = m[i-1]
            r[i] = r[i-1]
        else:
            m[i] = e[i]
            r[i] = s[i]
    return m[n-1]
"""
"""
def max_subarray(a):
    n = len(a)
    if n <= 1:
        return a
    left = max_subarray(a[0:n-1])
    right = max_subarray(a[1:n])
    return max_subarray_three(left,right,a)
"""
"""
class Result:
    def __init__(self, sum, array):
        self.sum = sum
        self.array = array
        
def max_subarray(a):
    n = len(a)
    if n == 1:
        return Result(a[0], a)
    left = max_subarray(a[0:n-1])
    right = max_subarray(a[1:n])
    sum_this = sum(a)
    sum_max = max(sum_this, left.sum, right.sum)
    if sum_max == sum_this:
        return Result(sum_this, a)
    elif sum_max == left.sum:
        return left
    else:
        return right
"""
"""
def max_subarray_original(a):
    n = len(a)
    max_left = 0
    max_right = 0
    max_sum = 0
    left = 0
    sum = 0
    for i in range(n-1):
        if a[i] > 0:
            sum += a[i]
            if i == n-1 or a[i+1] <= 0:
                if sum > max_sum:
                    max_left = left
                    max_right = i + 1
                    max_sum = sum
                    sum = 0
        else:
            left = i
            if i != n-1 and a[i+1] > 0:
                left = i+1

    return a[max_left:max_right]
"""
