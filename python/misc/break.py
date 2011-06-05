#!/usr/bin/env python
from sys import stdin
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-n", dest="number", type="int", default=76)
parser.add_option("-e", dest="encoding", default="utf-8")
(options, args) = parser.parse_args()

for line in stdin:
    code = line.decode(options.encoding)
    while len(code.encode(options.encoding)) > options.number:
        for i in range(len(code)):
            if code[:i].encode(options.encoding) > options.number:
                break
        print code[:i]
        code = code[i:]
    if len(code) > 0:
        print code,
