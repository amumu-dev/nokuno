#!/usr/bin/python

def parent(i):
    return (i - 1) / 2

def left(i):
    return i * 2 + 1
    
def right(i):
    return i * 2 + 2

def max_heapify(a, heap_size, i):
    l = left(i)
    r = right(i)
    largest = i
    if l < heap_size and a[l] > a[largest]:
        largest = l
    if r < heap_size and a[r] > a[largest]:
        largest = r
    if largest != i:
        a[i], a[largest] = a[largest], a[i]
        max_heapify(a, heap_size, largest)

def min_heapify(a, heap_size, i):
    l = left(i)
    r = right(i)
    smallest = i
    if l < heap_size and a[l] < a[smallest]:
        smallest = l
    if r < heap_size and a[r] < a[smallest]:
        smallest = r
    if smallest != i:
        a[i], a[smallest] = a[smallest], a[i]
        min_heapify(a, heap_size, smallest)

def max_heapify_loop(a, heap_size, i):
    while 1:
        l = left(i)
        r = right(i)
        largest = i
        if l < heap_size and a[l] > a[i]:
            largest = l
        if r < heap_size and a[r] > a[largest]:
            largest = r

        if largest != i:
            a[i], a[largest] = a[largest], a[i]
            i = largest
        else:
            break

def build_max_heap(a):
    for i in range(len(a)/2-1, -1, -1):
        max_heapify(a, len(a), i)

def heapsort(a):
    build_max_heap(a)
    heap_size = len(a)
    for i in range(len(a)-1, 0, -1):
        a[0], a[i] = a[i], a[0]
        heap_size -= 1
        max_heapify(a, heap_size, 0)

if __name__ == '__main__':
    print parent(1), parent(2), parent(3)
    print left(0), left(1), left(2)
    print right(0), right(1), right(2)

    a = [16,4,10,14,7,9,3,2,8,1]
    max_heapify(a, len(a), 1)
    print a

    a = [16,4,10,14,7,9,3,2,8,1]
    max_heapify_loop(a, len(a), 1)
    print a

    a = [5,1,2,3,4]
    min_heapify(a, len(a), 0)
    print a

    a = [1,2,3,4,5,6,7]
    build_max_heap(a)
    print a

    a = [4,1,3,2,16,9,10,14,8,7]
    heapsort(a)
    print a
