#!/usr/bin/env python
from sys import stdin
from optparse import OptionParser

if __name__ == "__main__":
    parser = OptionParser()
    parser.add_option("-t", dest="threshold", type="int", default=10)
    (options, args) = parser.parse_args()
    
    current_word = None
    current_freq = 0
    for line in stdin:
        splited = line.strip().split("\t", 1)
        if len(splited) == 2:
            word = splited[0]
            freq = int(splited[1])
            if current_word == None:
                current_word = word
            if current_word == word:
                current_freq += freq
            else:
                if current_freq >= options.threshold:
                    print current_word + "\t" + str(current_freq)
                current_word = word
                current_freq = freq

    if current_word != None:
        if current_freq >= options.threshold:
            print current_word + "\t" + str(current_freq)
