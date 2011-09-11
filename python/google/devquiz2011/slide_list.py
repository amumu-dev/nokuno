#!/usr/bin/env python
from copy import deepcopy

def cached_brute_force(input):
    cache = set()

    queue = [(input, "")]
    while len(queue) > 0:
        board, path = queue.pop(0)
        if board == correct(input):
            return path
        t = tuple(tuple(b) for b in board)
        if t in cache:
            continue
        cache.add(t)
        i, j = search(board)
        if i > 0 and board[i-1][j] != -1:
            copy = deepcopy(board)
            copy[i][j], copy[i-1][j] = copy[i-1][j], copy[i][j]
            queue.append((copy, path + "U"))
        if i < len(input) - 1 and board[i+1][j] != -1:
            copy = deepcopy(board)
            copy[i][j], copy[i+1][j] = copy[i+1][j], copy[i][j]
            queue.append((copy, path + "D"))
        if j > 0 and board[i][j-1] != -1:
            copy = deepcopy(board)
            copy[i][j], copy[i][j-1] = copy[i][j-1], copy[i][j]
            queue.append((copy, path + "L"))
        if j < len(input[0]) - 1 and board[i][j+1] != -1:
            copy = deepcopy(board)
            copy[i][j], copy[i][j+1] = copy[i][j+1], copy[i][j]
            queue.append((copy, path + "R"))

def brute_force(input):
    queue = [(input, "")]
    while len(queue) > 0:
        board, path = queue.pop(0)
        if board == correct(input):
            return path
        i, j = search(board)
        if i > 0 and board[i-1][j] != -1:
            copy = deepcopy(board)
            copy[i][j], copy[i-1][j] = copy[i-1][j], copy[i][j]
            queue.append((copy, path + "U"))
        if i < len(input) - 1 and board[i+1][j] != -1:
            copy = deepcopy(board)
            copy[i][j], copy[i+1][j] = copy[i+1][j], copy[i][j]
            queue.append((copy, path + "D"))
        if j > 0 and board[i][j-1] != -1:
            copy = deepcopy(board)
            copy[i][j], copy[i][j-1] = copy[i][j-1], copy[i][j]
            queue.append((copy, path + "L"))
        if j < len(input[0]) - 1 and board[i][j+1] != -1:
            copy = deepcopy(board)
            copy[i][j], copy[i][j+1] = copy[i][j+1], copy[i][j]
            queue.append((copy, path + "R"))

def correct(board):
    result = deepcopy(board)
    num = 1
    for i in range(len(result)):
        for j in range(len(result[0])):
            if result[i][j] != -1:
                result[i][j] = num
            num += 1
    result[-1][-1] = 0
    return result

def search(board):
    for i in range(len(board)):
        for j in range(len(board[0])):
            if board[i][j] == 0:
                return (i,j)
    return result

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
            print "Number:", number
            number += 1
            w, h, b = line.strip().split(",",2)
            w, h = int(w), int(h)
            board = [[char2int(b[i*w+j]) for j in range(w)] for i in range(h)]

            if w == 3 and h == 3:
                print "Input:"
                print show(board)
                print "Start:", search(board)
                print "Correct:"
                print show(correct(board))
                print "Solution:", cached_brute_force(board)

