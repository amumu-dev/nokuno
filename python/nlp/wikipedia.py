#!/usr/bin/python
#encoding: utf-8
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-t", dest="threshold", type="int", default=0)
(o, args) = parser.parse_args()

title = ""
bag_of_words = {}

#parse wikipedia corpus processed by mecab with document unit
for line in sys.stdin:
    words = line.strip().split(" ")
    if len(words) == 0:
        continue
    elif words[0] == "[[" and words[-1] == "]]":
        if title != "":
            bow = bag_of_words.items()
            bow = sorted(bow, key=lambda x:-x[1])
            print title + "\t",
            for (key, value) in bow:
                if value > o.threshold:
                    print key + ":" + str(value) + " ",
            print
        title = "".join(words[1:-1])
        bag_of_words = {}
    else:
        for word in words:
            count = bag_of_words.setdefault(word, 0)
            bag_of_words[word] = count+1
