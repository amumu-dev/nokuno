#!/usr/bin/env python
# encoding: utf-8
import sys, json

for line in sys.stdin:
    if len(line) > 3:
        twit = json.loads(line)
        #print twit['user']['screen_name'], twit['text']
        print twit['text'].encode('utf-8')

