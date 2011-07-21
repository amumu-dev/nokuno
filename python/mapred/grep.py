#!/usr/bin/env python
#encoding: utf-8
from sys import stdin, exit
from optparse import OptionParser
from re import compile

if __name__ == "__main__":
    parser = OptionParser()
    parser.add_option("-r", dest="regex", default="日本の..")
    (options, args) = parser.parse_args()
    if options.regex == None:
        exit("-r regular expression is required.")

    regex = compile(options.regex.decode('utf-8'))
    for line in stdin:
        matches = regex.findall(unicode(line.strip(), 'utf-8'))
        for match in matches:
            print match.encode('utf-8') + "\t1"
