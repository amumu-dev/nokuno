#!/usr/bin/env python
import sys

T = int(sys.stdin.readline())

def contain(word, character):
    for c in word:
        if c == character:
            return True
    return False

def consistent(word, current, previous):
    if len(word) != len(current):
        return False
    for i in range(len(current)):
        if current[i] != '_' and current[i] != word[i]:
            return False
        if current[i] == '_' and word[i] in previous:
            return False
    return True

def valid(character, dictionary, current, index, previous):
    if character in index:
        for i in index[character]:
            if consistent(dictionary[i], current, previous):
                return True
    return False

def score(word, dictionary, list, index):
    current = '_' * len(word)
    result = 0
    previous = []
    for character in list:
        if valid(character, dictionary, current, index, previous):
            previous.append(character)
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
    index = {}
    for i in range(N):
        for c in dictionary[i]:
            if c in index:
                index[c].append(i)
            else:
                index[c] = [i]
    result = []
    for l in range(M):
        list = sys.stdin.readline().strip()
        answer = max(dictionary, key=lambda x: score(x, dictionary, list, index))
        result.append(answer)
    print "Case #%d: %s" % (x, ' '.join(result))
