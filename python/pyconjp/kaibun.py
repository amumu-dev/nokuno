#!/usr/bin/env python
#encoding: utf-8
from MeCab import *
from sys import *

def is_kaibun(text):
    for i in range(len(text)/2):
        if text[i] != text[len(text)-i-1]:
            return False
    return True

if __name__ == '__main__':

    tagger = Tagger("-Oyomi")
    for line in stdin:
        yomi = tagger.parse(line)
        yomi = yomi.strip().decode('utf-8')
        if len(yomi) >= 4 and is_kaibun(yomi):
            print line,
"""
    tagger = Tagger()
    for line in stdin:
        node = tagger.parseToNode(line.strip())

        surface = ""
        pronunciation = ""

        while node:
            features = node.feature.split(",")
            if (len(features) < 8):
                break
            if (features[7] != "*"):
                pronunciation += features[7]
                surface += node.surface
            node = node.next

        if is_kaibun(pronunciation.decode('utf-8')):
            print "%s\t%s" % (surface, pronunciation)
"""
