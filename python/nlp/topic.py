#!/usr/bin/python
#encoding: utf-8
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-t", dest="threshold", type="int", default=0)
parser.add_option("-w", dest="words", default="政治,スポーツ,経済")
(o, args) = parser.parse_args()
topic_words = o.words.split(",")

title = ""
bag_of_words = {}
for line in sys.stdin:
    words = line.strip().split(" ")
    if len(words) == 0:
        continue
    elif words[0] == "[[" and words[-1] == "]]": # new title
        if title != "":
            # print bag-of-words
            if o.words == "":
                bow = bag_of_words.items()
                bow = sorted(bow, key=lambda x:x[1])
                print title + "\t",
                for (key, value) in bow:
                    if value > o.threshold:
                        print key + ":" + str(value) + " ",
                print
            # print topic probability
            else:
                total = sum([bag_of_words.setdefault(topic,0) for topic in topic_words])
                if total > o.threshold:
                    prob = [str(float(bag_of_words.setdefault(topic,0)) / float(total)) for topic in topic_words]
                    print title + "\t" + "\t".join(prob)
                    
        title = "".join(words[1:-1])
        bag_of_words = {}
    else: # update bag-of-words
        for word in words:
            count = bag_of_words.setdefault(word, 0)
            bag_of_words[word] = count+1
