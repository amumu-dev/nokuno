#!/usr/bin/python
import sys

word = ""
count = 0

for line in sys.stdin:
  wordcount = line.strip().split("\t", 1)
  if len(wordcount) != 2: continue
  if wordcount[0] != word and word != "":
    print '%s\t%s' % (word, count)
    count = 0
  word = wordcount[0]
  count += int(wordcount[1])

print '%s\t%s' % (word, count)

