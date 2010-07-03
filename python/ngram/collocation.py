#!/usr/bin/python
#encoding: utf-8
#文字コード認識用
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-l", dest="left")
parser.add_option("-r", dest="right")
parser.add_option("-w", dest="width", type="int", default=10)
parser.add_option("-d", dest="dist", type="int", default=5)
(o, args) = parser.parse_args()

for line in sys.stdin:
    words = line.split()
    length = len(words)
    for i in range(length):
        if o.left == None or words[i] == o.left:
            for j in range(i+o.dist, min(i+o.dist+o.width,length)):
                if o.right == None or words[j] == o.right:
                    print words[i], words[j]

"""
usage:
    cat wakati.txt | collocation.py | sort | uniq -c > collocation.txt
"""
