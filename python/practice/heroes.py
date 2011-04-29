#!/usr/bin/env python
import sys
import copy

def combination(depth = 6):
    if depth < 0:
        return [([],[],[])]

    result = []
    for cand in combination(depth - 1):
        for i in range(3):
            temp = copy.deepcopy(cand)
            temp[i].append(depth)
            result.append(temp)
    return result

def compare(a, b, pairs, exps):
    pass

def solve(pairs, exps):
    print pairs
    print exps
    for cand in combination():

if __name__ == '__main__':
    heros = {"Anka":0, "Chapay":1, "Cleo":2, "Troll":3, "Dracul":4, "Snowy":5, "Hexadecimal":6}
    number = int(sys.stdin.readline())

    pairs = set()
    for i in range(number):
        row = sys.stdin.readline().strip().split(" ")
        pair = (heros[row[0]], heros[row[2]])
        pairs.add(pair)
        
    row = sys.stdin.readline().strip().split(" ")
    exps = [int(e) for e in row]
    solve(pairs, exps)

