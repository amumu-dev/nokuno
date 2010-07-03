# encoding: utf-8
import json, sys

for line in sys.stdin:
    data = json.loads(line)
    print data[u'text']
    #print data
