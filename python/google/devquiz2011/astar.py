#!/usr/bin/env python

from heapq import *

def evaluate(b, c, w, h):
    result = 0
    for i in range(len(b)):
        if b[i] != "=" and b[i] != "0":
            j = c.find(b[i])
            result +=  abs(i % w - j % w) + abs(i / w - j / w)
    return result

def astar(b, c, w, h, s, num):
    cache = {}

    # breath first search with cache
    queue = [(s, b, "")]

    for loop in range(num):
        if len(queue) == 0:
            break
        cost, board, path = heappop(queue)

        if board == c:
            return path

        if board in cache and cache[board] <= cost:
            continue

        cache[board] = cost

        index = board.find("0")
        i = index % w
        j = index / w

        update(queue, board, w, h, i, j, i-1, j, path, "L", c)
        update(queue, board, w, h, i, j, i+1, j, path, "R", c)
        update(queue, board, w, h, i, j, i, j-1, path, "U", c)
        update(queue, board, w, h, i, j, i, j+1, path, "D", c)

    return ""

def update(queue, board, w, h, i1, j1, i2, j2, path, type, c):
    if i2 < 0 or i2 > w-1 or j2 < 0 or j2 > h-1:
        return
    if board[i2+j2*w] == "=":
        return
    a = i1 + j1 * w
    b = i2 + j2 * w
    next = list(board)
    next[a], next[b] = next[b], next[a]
    n = "".join(next)
    path += type
    heappush(queue, (evaluate(n, c, w, h) + len(path), n, path))

def correct(b):
    result = ""
    for i in range(len(b)-1):
        if b[i] == "=":
            result += "="
        elif i+1 < 10:
            result += chr(i+1 + ord("0"))
        else:
            result += chr(i+1-10 + ord("A"))
    result += "0"
    return result

def show(b, w, h):
    result = ""
    for i in range(h):
        result += b[i*w:(i+1)*w] + "\n"
    return result

if __name__ == "__main__":
    import sys
    from optparse import OptionParser

    opt = OptionParser()
    opt.add_option("-t", dest="threshold", type="int", default=50)
    opt.add_option("-f", dest="file", default="data/problems.txt")
    opt.add_option("-n", dest="num", type="int", default=10000)
    options, argv = opt.parse_args()

    with open(options.file) as fp:
        lx, rx, ux, dx = [i for i in fp.readline().strip().split(" ", 3)]
        n = int(fp.readline())

        number = 0
        for line in fp:
            number += 1
            w, h, b = line.strip().split(",",2)
            w, h = int(w), int(h)

            c = correct(b)
            s = evaluate(b, c, w, h)

            if s < options.threshold:
                #print "Input:"
                #print show(b, w, h),
                #print "Correct:"
                #print show(c, w, h)

                result = astar(b, c, w, h, s, options.num)
                print result
            else:
                print

