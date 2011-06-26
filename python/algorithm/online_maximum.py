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

score = range(100)
random.shuffle(score)
print online_maximum(len(score)/2, score)

for k in range(100):
    n = 0.
    for i in range(1000):
        score = range(100)
        random.shuffle(score)
        result = online_maximum(k, score)
        if score[result] == 99:
            n += 1
    print k, n / 1000.
