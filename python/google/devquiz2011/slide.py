#!/usr/bin/env python
from copy import deepcopy

def brute_force(board):
    pass

def correct(board):
    result = deepcopy(board)
    num = 1
    for i in len(result):
        for j in len(result[0]):
            if result[i][j] != None:
                result[i][j] = num
                num += 1
    return result

def show(board):
    result = ""
    for row in board:
        result += str(row) + "\n"
    return result

def char2int(c):
    if c == "=":
        return -1
    if ord(c) >= ord("0") and ord(c) <= ord("9"):
        return ord(c) - ord("0")
    return ord(c) - ord("A")

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        file = "data/problems.txt"
    else:
        file = sys.argv[1]

    with open(file) as fp:
        lx, rx, ux, dx = [i for i in fp.readline().strip().split(" ", 3)]
        n = int(fp.readline())

        for line in fp:
            w, h, b = line.strip().split(",",2)
            w, h = int(w), int(h)
            board = [[char2int(b[i*w+j]) for j in range(w)] for i in range(h)]
            if w == 3 and h == 3:
                print show(board)
                print brute_force(board)

