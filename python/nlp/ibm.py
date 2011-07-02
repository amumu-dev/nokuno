#!/usr/bin/env python
from collections import defaultdict

def train(corpus):
    pair = defaultdict(float)
    for english, forein in corpus:
        for e in english.split(" "):
            for f in forein.split(" "):
                pair[(e,f)] += 1.
    print 'pair:', pair

    t = defaultdict(float)
    for e,f in pair.keys():    
        t[(e,f)] = 0.25
    for loop in range(1000):
        count = defaultdict(float)
        total = defaultdict(float)
        s_total = defaultdict(float)
        for e,f in pair.keys():
            s_total[e] += t[(e,f)]
        for e,f in pair.keys():    
            count[(e,f)] = t[(e,f)] * pair[(e,f)] / s_total[e]
            total[f] += count[(e,f)]
        for e,f in pair.keys():    
            t[(e,f)] = count[(e,f)] / total[f]
    print 'table:', t

if __name__ == '__main__':
    corpus = [("the house", "das Haus"), 
            ("the book", "das Buch"),
            ("a book", "ein Buch")]
    train(corpus)
