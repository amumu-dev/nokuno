#!/usr/bin/python
#encoding: utf-8
#文字コード認識用
from sys    import stdin
from math   import log
from optparse import OptionParser

def pmi(left, right, collocation):
    return -log( left * right / collocation )

def emi(left, right, collocation):
    return -log( left * right / collocation ) * collocation

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option("-t", dest="threshold", type="float", default=5.0)
    parser.add_option("-e", dest="expect", action="store_true", default=False)
    parser.add_option("-f", dest="file", default="unigram.txt")
    (o, args) = parser.parse_args()

    #load unigram
    total = 0
    unigram = {}
    for line in open(o.file):
        (word, freq) = line.strip().split()
        freq = float(freq)
        total += freq
        unigram[word] = freq

    #calculate pmi from co-occurence
    for line in stdin:
        (left, right, freq) = line.split()
        l = unigram.get(left, 0)
        r = unigram.get(right, 0)
        cooccurnece = float(freq)
        if l == 0 or r == 0:
            continue
        lp = l / total
        rp = r / total
        if o.expect:
            score = emi(l/total, r/total, cooccurnece)
        else:
            score = pmi(l/total, r/total, cooccurnece)
        if score >= o.threshold:
            print "%s %s\t%f" % (left, right, score)

