#!/usr/bin/python
import random

def hire_assistant(n):
    best = 0
    max_score = 0
    for i in range(n):
        #interview candidate i
        score = random.randint(0,10)
        if score > best:
            best = i
            max_score = score
    return best, max_score

if __name__ == '__main__':
    print hire_assistant(5)

