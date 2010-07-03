#!/usr/bin/python

class Heap:
    def __init__(self, a):
        self.a = a
        self.size = len(a)

    def max_heapify(self, i):
        while 1:
            l = i * 2 + 1
            r = i * 2 + 2
            largest = i
            if l < self.size and self.a[l] > self.a[i]:
                largest = l
            if r < self.size and self.a[r] > self.a[largest]:
                largest = r

            if largest != i:
                self.a[i], self.a[largest] = self.a[largest], self.a[i]
                i = largest
            else:
                break

    def build_max_heap(self):
        for i in range(len(self.a)/2-1, -1, -1):
            self.max_heapify(i)

    def heapsort(self):
        self.build_max_heap()
        for i in range(len(self.a)-1, 0, -1):
            self.a[0], self.a[i] = self.a[i], self.a[0]
            self.size -= 1
            self.max_heapify(0)

if __name__ == '__main__':
    heap = Heap([16,4,10,14,7,9,3,2,8,1])
    heap.max_heapify(1)
    print heap.a

    heap = Heap([1,2,3,4,5,6,7])
    heap.build_max_heap()
    print heap.a

    heap = Heap([4,1,3,2,16,9,10,14,8,7])
    heap.heapsort()
    print heap.a

    import random
    a = [random.randrange(10000) for i in range(100000)]
    heap = Heap(a)
    heap.heapsort()

