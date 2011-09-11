#!/usr/bin/env python

def show(board):
    result = ""
    for row in board:
        result += "".join(row) + "\n"
    return result

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        file = "data/problems.txt"
    else:
        file = argv[0]

    with open(file) as fp:
        lx, rx, ux, dx = [int(i) for i in fp.readline().strip().split(" ", 4)]
        n = int(fp.readline())

        for line in fp:
            w, h, b = line.strip().split(",",2)
            w, h = int(w), int(h)
            board = [[b[i*w+j] for j in range(w)] for i in range(h)]
            print w, h
            print show(board)
