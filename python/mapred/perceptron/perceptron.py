#!/usr/bin/env python
#encoding: utf-8

from sys import stdin
from optparse import OptionParser
from collections import defaultdict
from random import shuffle, seed


def parse(line):
    pair = line.strip().split(" ", 1)
    if len(pair) != 2: return None
    label, document = pair

    features = defaultdict(float)
    for feature in document.split(" "):
        key, value = feature.split(":", 1)
        features[key] = float(value)

    return (label, features)

def dot(x, y):
    return sum(x.get(i, 0.) * y[i] for i in y.iterkeys())

class Perceptron:
    def __init__(self, weight):
        self.weight = weight

    def train(self, documents, iteration, learn):
        for label, features in documents:
            if not label in self.weight:
                self.weight[label] = defaultdict(float)
        for i in range(iteration):
            shuffle(documents)
            for label, features in documents:
                # prediction
                prediction, scores = self.predict(features)

                # update
                if prediction != label:
                    for key, value in features.iteritems(): 
                        self.weight[label][key] += learn * value
                        self.weight[prediction][key] -= learn * value


    def predict(self, features):
        max_label = None
        scores = {}
        for label, weight in self.weight.iteritems():
            scores[label] = dot(weight, features)
            if max_label == None or scores[label] > scores[max_label]:
                max_label = label
        return (max_label, scores)

    def output(self):
        result = ""
        for label, weight in self.weight.iteritems():
            weight_str = " ".join(key + ":" + str(value) for key, value in weight.iteritems())
            result += label + " " + weight_str + "\n"
        return result

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option("-i", dest="iteration", type="int", default=1)
    parser.add_option("-e", dest="eta", type="float", default=0.001)
    parser.add_option("-w", dest="weight")
    (options, args) = parser.parse_args()
    
    # Load file
    documents = []
    for line in stdin:
        documents.append(parse(line))

    # Load weights from Distributed Cache
    weight = defaultdict(lambda: defaultdict(float))
    if options.weight != None:
        for line in open(options.weight):
            parsed = parse(line)
            if parsed == None: continue
            key, value = parsed
            weight[key] = value

    # Train perceptron
    perceptron = Perceptron(weight)
    perceptron.train(documents, options.iteration, options.eta)

    # Output weight file
    print perceptron.output(),

