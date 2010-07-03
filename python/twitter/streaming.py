#!/usr/local/bin/python
# encoding: utf-8
import sys
import json

for line in sys.stdin:
    if len(line) > 3:
        twit = json.loads(line)
        print twit['user']['screen_name'], twit['text']

