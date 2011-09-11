#!/usr/bin/env python

def update(queue, board, w, h, i1, j1, i2, j2, path, type):
    if i2 < 0 or i2 > w-1 or j2 < 0 or j2 > h-1:
        return
    if board[i2+j2*w] == "=":
        return
    a = i1 + j1 * w
    b = i2 + j2 * w
    next = list(board)
    next[a], next[b] = next[b], next[a]
    queue.append(("".join(next), path + type))

def brute_force(b, c, w, h):
    cache = set()

    # breath first search with cache
    queue = [(b, "")]

    for loop in range(10000000):
        if len(queue) == 0:
            break
        board, path = queue.pop(0)

        if board == c:
            return path

        if board in cache:
            continue

        cache.add(board)

        index = board.find("0")
        i = index % w
        j = index / w

        update(queue, board, w, h, i, j, i-1, j, path, "L")
        update(queue, board, w, h, i, j, i+1, j, path, "R")
        update(queue, board, w, h, i, j, i, j-1, path, "U")
        update(queue, board, w, h, i, j, i, j+1, path, "D")

    return ""

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

            if w + h <= 6:
                #sys.stderr.write("Number: %d" % (number))
                c = correct(b)

                #print show(b, w, h),
                #print "Correct:"
                #print show(c, w, h)

                result = brute_force(b, c, w, h)
                print result
            else:
                print

