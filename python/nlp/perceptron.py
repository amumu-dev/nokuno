#!/usr/bin/env python
#encoding: utf-8

from sys import stdin
from optparse import OptionParser
from collections import defaultdict

def parse(text, bias):
    splited = text.strip().split(" ", 1)
    if splited == None or len(splited) != 2:
        return None
    label = splited[0]

    features = {}
    for feature in splited[1].split(" "):
        pair = feature.split(":", 1)
        if pair == None or len(pair) != 2:
            continue
        features[pair[0]] = float(pair[1])
    if bias:
        features[-1] = 1.

    return (label, features)

class Perceptron:
    def __init__(self):
        self.weight = {}

    def train(self, documents, iteration, eta):
        for i in range(iteration):
            for label, features in documents:
                if not label in self.weight:
                    self.weight[label] = defaultdict(float)

                prediction = self.predict(features)
                if prediction != label:
                    for key, value in features.items(): 
                        self.weight[label][key] += eta * value
                    for label in self.weight.keys():
                        for key, value in features.items(): 
                            self.weight[label][key] -= eta * value

    def predict(self, feature):
        max_label = None
        max_output = 0.
        for label, weight in self.weight.items():
            output = sum(weight[key] * feature[key] for key in feature.keys())
            if max_label == None or output > max_output:
                max_label = label
                max_output = output
        return max_label

if __name__ == '__main__':
    # Parse options
    parser = OptionParser()
    parser.add_option("-1", dest="train", default="train.txt")
    parser.add_option("-2", dest="test", default="test.txt")
    parser.add_option("-i", dest="iteration", type="int", default=10)
    parser.add_option("-e", dest="eta", type="float", default=0.1)
    parser.add_option("-r", dest="rate", type="float", default=0.1)
    parser.add_option("-b", dest="bias", action="store_true")
    (options, args) = parser.parse_args()
    
    # Load file
    documents = []
    for line in stdin:
        document = parse(line, options.bias)
        if document != None and len(document) == 2:
            documents.append(document)

    perceptron = Perceptron()

    # Split data into train and test data
    index = int(len(documents) * options.rate)
    perceptron.train(documents[index:], options.iteration, options.eta)

    correct = 0.
    for document in documents[:index]:
        prediction = perceptron.predict(document[1])
        if prediction == document[0]:
            correct += 1.
    print correct / index

