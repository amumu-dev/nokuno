#!/usr/bin/env python
import sys

T = int(sys.stdin.readline())

def contain(word, character):
    for c in word:
        if c == character:
            return True
    return False

def consistent(word, current):
    if len(word) != len(current):
        return False
    for i in range(len(current)):
        if current[i] != '_' and current[i] != word[i]:
            return False
        if current[i] == '_' and word[i] in previous:
            return False
    return True

def valid(character, dictionary, current):
    for word in dictionary:
        if contain(word, character) and consistent(word, current):
            return True
    return False

def score(word, dictionary, list):
    current = '_' * len(word)
    result = 0
    for character in list:
        if valid(character, dictionary, current):
            reveal = False
            for i in range(len(word)):
                if word[i] == character:
                    current = current[:i] + character + current[i+1:]
                    reveal = True
                    if current == word:
                        return result
            if not reveal:
                result += 1
    #print word, dictionary, list, result
    return result

for x in range(1, T+1):
    (N, M) = [int(i) for i in sys.stdin.readline().strip().split(" ")]
    dictionary = []
    for i in range(N):
        word = sys.stdin.readline().strip()
        dictionary.append(word)
    result = []
    for l in range(M):
        list = sys.stdin.readline().strip()
        maximum = -1
        answer = max(dictionary, key=lambda x: score(x, dictionary, list))
        result.append(answer)
    print "Case #%d: %s" % (x, ' '.join(result))
