#!/usr/bin/env python
# encoding: utf-8
import sys, json

for line in sys.stdin:
    tweet = json.loads(line)
    if 'text' in tweet:
        print tweet['text'].encode('utf-8')

