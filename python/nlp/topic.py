#!/usr/bin/python
#encoding: utf-8
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-t", dest="threshold", type="int", default=0)
parser.add_option("-w", dest="words", default="政治,スポーツ,経済")
parser.add_option("-f", dest="format", default="title")
(o, args) = parser.parse_args()
topic_words = o.words.split(",")

if o.format == "title":
    print "タイトル\t" + "\t".join(topic_words)
else:
    print "\t".join(topic_words)

title = ""
bag_of_words = {}
for line in sys.stdin:
    words = line.strip().split(" ")
    if len(words) == 0:
        continue
    elif words[0] == "[[" and words[-1] == "]]": # new title
        if title != "":
            # print topic probability
            total = sum([bag_of_words.setdefault(topic,0) for topic in topic_words])
            if total > o.threshold:
                prob = [str(float(bag_of_words.setdefault(topic,0)) / float(total)) for topic in topic_words]
                if o.format == "title":
                    print title + "\t",
                print "\t".join(prob)
                    
        title = "".join(words[1:-1])
        bag_of_words = {}
    else: # update bag-of-words
        for word in words:
            count = bag_of_words.setdefault(word, 0)
            bag_of_words[word] = count+1
