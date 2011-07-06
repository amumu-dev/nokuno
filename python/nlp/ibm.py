#!/usr/bin/env python
from collections import defaultdict
from optparse import OptionParser

def em_algorithm(pair, number, size):
    t = defaultdict(float)
    for e,f in pair.keys():    
        t[(e,f)] = 1. / size
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

def train(corpus, number, mode, length):
    pair = defaultdict(float)
    vocabulary = set()
    for english, foreign in corpus:
        foreign_split = foreign.split(" ")
        english_split = english.split(" ")
        if mode == "normal":
            for e in english_split:
                for f in foreign_split:
                    pair[(e,f)] += 1.
                    vocabulary.add(e)
        elif mode == "restrict":
            l = min(len(english_split),len(foreign_split))
            for i in range(l):
                e = english_split[i]
                for j in range(max(0,i-length),min(len(foreign_split),i+1+length)):
                    f = foreign_split[j]
                    pair[(e,f)] += 1.
                vocabulary.add(e)
        elif mode == "phrase":
            for l in range(length):
                for i in range(len(english_split)-l):
                    for j in range(len(foreign_split)-l):
                        e = " ".join(english_split[i:i+1+l])
                        f = " ".join(foreign_split[j:j+1+l])
                        pair[(e,f)] += 1.
                        vocabulary.add(e)
        elif mode == "pronunciation":
            l = min(len(english_split),len(foreign_split))
            buffer = abs(len(english_split) - len(foreign_split)) + 1
            for i in range(l):
                e = english_split[i]
                for j in range(max(0,i),min(len(foreign_split),i+buffer)):
                    f = foreign_split[j]
                    pair[(e,f)] += 1.
                vocabulary.add(e)
               
    return em_algorithm(pair, number, len(vocabulary))

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option("-e", dest="english", default="data/english.txt")
    parser.add_option("-f", dest="foreign", default="data/foreign.txt")
    parser.add_option("-t", dest="test", action="store_true")
    parser.add_option("-n", dest="number", type="int", default=10)
    parser.add_option("-p", dest="probability", type="float", default=0.01)
    parser.add_option("-m", dest="mode", default="normal")
    parser.add_option("-l", dest="length", type="int", default=2)
    parser.add_option("-b", dest="bigram")
    (options, args) = parser.parse_args()

    if options.bigram:
        bigram = {}
        vocabulary = set()
        for line in open(options.bigram):
            (word1, word2, freq) = line.strip().split()
            bigram[(word1, word2)] = float(freq)
            vocabulary.add(word1)
        t = em_algorithm(bigram, options.number, len(vocabulary))

    else:
        if options.test:
            corpus = [("the house", "das Haus"), 
                    ("the book", "das Buch"),
                    ("a book", "ein Buch")]
        else:
            english = [line.strip() for line in open(options.english)]
            foreign = [line.strip() for line in open(options.foreign)]
            corpus = zip(english, foreign)

        t = train(corpus, options.number, options.mode, options.length)

    for (e,f),p in sorted(t.items(), key=lambda x:-x[1]):
        if p >= options.probability:
            print "%s\t%s\t%f" % (e, f, p)

