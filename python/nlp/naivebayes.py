#!/usr/bin/env python
#encoding: utf-8

from sys import stdin
from optparse import OptionParser
from collections import defaultdict

def sign(x):
    if abs(x) < 1e-10:
        return 0
    elif x > 0:
        return 1
    return -1

def clip(x, c):
    return sign(x) * max(0., abs(x) - c)

def parse(line, bias, discount):
    label, document = line.strip().split(" ", 1)

    features = {}
    for feature in document.split(" "):
        key, value = feature.split(":", 1)
        features[key] = clip(float(value), discount)

    if bias != 0.:
        features[-1] = bias

    return (label, features)

class NaiveBayes:
    def __init__(self):
        self.freq = {}
        self.label = {}

    def train(self, documents, mode, smoothing):
        for label, features in documents:
            if not label in self.freq:
                self.freq[label] = defaultdict(lambda: smoothing)
                self.label[label] = 0.

        for label, features in documents:
            self.label[label] += 1.

            for key, value in features.iteritems(): 
                self.freq[label][key] += value

    def predict(self, feature):
        max_label = None
        prob = {}
        for label, freq in self.freq.iteritems():
            prob[label] = self.label[label] / sum(self.label.values())
            denom = sum(freq.itervalues())
            for key, value in feature.iteritems():
                prob[label] *= (freq[key] / denom) ** value
            if max_label == None or prob[label] > prob[max_label]:
                max_label = label
        return (max_label, prob)

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option("-m", dest="mode", default="basic")
    parser.add_option("-t", dest="test", type="float", default=0.1)
    parser.add_option("-s", dest="smoothing", type="float", default=0.1)
    parser.add_option("-d", dest="discount", type="float", default=0.5)
    parser.add_option("-b", dest="bias", type="float", default=0.)
    (options, args) = parser.parse_args()
    
    # Load file
    documents = []
    for line in stdin:
        documents.append(parse(line, options.bias, options.discount))

    naivebayes = NaiveBayes()

    # Split documents into train and test data
    index = int(len(documents) * options.test)

    # Train
    naivebayes.train(documents[index:], options.mode, options.smoothing)

    # Test prediction
    correct = 0.
    for label, features in documents[:index]:
        prediction, prob = naivebayes.predict(features)
        if prediction == label:
            correct += 1.
    
    # Output accuracy
    print correct / index

