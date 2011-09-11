#!/usr/bin/env python
from copy import deepcopy

def update(queue, board, w, h, i1, j1, i2, j2, path, type):
    if i2 < 0 or i2 > h-1 or j2 < 0 or j2 > w-1:
        return
    if board[i2][j2] == "=":
        return

    next = deepcopy(board)
    next[i1][j1], next[i2][j2] = next[i2][j2], next[i1][j1]
    queue.append((next, path + type))

def brute_force(b, c, w, h):
    cache = set()

    queue = [(b, "")]

    for loop in range(10000000):
        if len(queue) == 0:
            break

        board, path = queue.pop(0)

        if board == c:
            return path

        t = tuple(tuple(b) for b in board)
        if t in cache:
            continue
        cache.add(t)

        i, j = search(board, w, h)
        update(queue, board, w, h, i, j, i-1, j, path, "U")
        update(queue, board, w, h, i, j, i+1, j, path, "D")
        update(queue, board, w, h, i, j, i, j-1, path, "L")
        update(queue, board, w, h, i, j, i, j+1, path, "R")

    return ""

def correct(board, w, h):
    result = deepcopy(board)
    num = 1
    for i in range(w):
        for j in range(h):
            if result[i][j] != -1:
                result[i][j] = num
            num += 1
    result[-1][-1] = 0
    return result

def search(board, w, h):
    for i in range(w):
        for j in range(h):
            if board[i][j] == 0:
                return (i,j)

def show(board):
    result = ""
    for row in board:
        result += str(row) + "\n"
    return result

def char2int(c):
    if c == "=":
        return -1
    elif ord(c) >= ord("0") and ord(c) <= ord("9"):
        return ord(c) - ord("0")
    elif ord(c) >= ord("A") and ord(c) <= ord("Z"):
        return ord(c) - ord("A")
    return None

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        file = "data/problems.txt"
    else:
        file = sys.argv[1]

    with open(file) as fp:
        lx, rx, ux, dx = [i for i in fp.readline().strip().split(" ", 3)]
        n = int(fp.readline())

        number = 0
        for line in fp:
            number += 1
            w, h, b = line.strip().split(",",2)
            w, h = int(w), int(h)
            board = [[char2int(b[i*w+j]) for j in range(h)] for i in range(w)]

            if w + h <= 6:
                c = correct(board, w, h)

                #print "Input:", number
                #print show(board),
                #print "Correct:"
                #print show(c),

                result = brute_force(board, c, w, h)
                print result
            else:
                print
