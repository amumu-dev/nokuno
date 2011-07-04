#!/usr/bin/env python
from collections import defaultdict
from optparse import OptionParser

def train(corpus, number):
    pair = defaultdict(float)
    vocabulary = set()
    for english, forein in corpus:
        for e in english.split(" "):
            for f in forein.split(" "):
                pair[(e,f)] += 1.
                vocabulary.add(e)

    t = defaultdict(float)
    for e,f in pair.keys():    
        t[(e,f)] = 1. / len(vocabulary)
    for loop in range(number):
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
    return t

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option("-e", dest="english", default="data/english.txt")
    parser.add_option("-f", dest="foreign", default="data/foreign.txt")
    parser.add_option("-t", dest="test", action="store_true")
    parser.add_option("-n", dest="number", type="int", default=10)
    parser.add_option("-p", dest="probability", type="float", default=0.01)
    (options, args) = parser.parse_args()

    if options.test:
        corpus = [("the house", "das Haus"), 
                ("the book", "das Buch"),
                ("a book", "ein Buch")]
    else:
        english = [line.strip() for line in open(options.english)]
        foreign = [line.strip() for line in open(options.foreign)]
        corpus = zip(english, foreign)

    t = train(corpus, options.number)

    for (e,f),p in sorted(t.items(), key=lambda x:-x[1]):
        if p >= options.probability:
            print "%s\t%s\t%f" % (e, f, p)

