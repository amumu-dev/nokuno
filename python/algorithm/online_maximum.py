#!/usr/bin/env python
import random

def online_maximum(k, score):
    bestscore = -1000
    for i in range(1, k+1):
        if score[i] > bestscore:
            bestscore = score[i]
    for i in range(k+1, len(score)):
        if score[i] > bestscore:
            return i
    return len(score)-1

if __name__ == '__main__':
    for k in range(100):
        n = 0.
        total = 0.
        for i in range(1000):
            score = range(100)
            random.shuffle(score)
            result = online_maximum(k, score)
            total += score[result]
            if score[result] == 99:
                n += 1
        print '%d,%f,%f' % (k, n / 1000., total / 1000.)

