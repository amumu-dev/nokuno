#!/usr/bin/python

part = ["", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"]
dict = ["bad"]
keystr = "2230223"

map = {}
for i in range(len(part)):
    for c in part[i]:
        map[c] = i+1
#print map

result = keystr
for word in dict:
    input = ''.join([str(map[c]) for c in word])
    result = result.replace(input, word)

print result
