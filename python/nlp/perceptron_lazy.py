#!/usr/bin/env python
#encoding: utf-8

from sys import stdin
from optparse import OptionParser
from collections import defaultdict
from random import shuffle, seed
from math import sqrt

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


def dot(x, y):
    return sum(x.get(i, 0.) * y[i] for i in y.iterkeys())

def norm(x):
    return dot(x, x)

class Perceptron:
    def __init__(self):
        self.weight = {}
        self.weight_all = {}
        self.last_update = defaultdict(int)
        self.time = 1

    def train(self, documents, mode, iteration, eta, gamma, regularization, c):
        self.regularization = regularization
        self.c = c
        for label, features in documents:
            if not label in self.weight:
                self.weight[label] = defaultdict(float)
        for i in range(iteration):
            shuffle(documents)
            for label, features in documents:
                # prediction
                prediction, scores = self.predict(features)

                # update
                if prediction != label or scores[prediction] < gamma:
                    if mode == "basic":
                        learn = 1. / (self.time * eta + 1.)
                    elif mode == "pegasos":
                        learn = 1. / (self.time * eta)
                    elif mode == "sqrt":
                        learn = 1. / (self.time * sqrt(eta))
                    elif mode == "constant":
                        learn = eta
                    elif mode.startswith("pa"):
                        loss = max(0, 1. + scores[prediction] - scores[label])
                        if mode == "pa":
                            learn = loss / norm(features)
                        elif mode == "pa1":
                            learn = min(c, loss / (norm(features) + 1. / (2. * c)))
                        elif mode == "pa2":
                            learn = loss / (norm(features) + 1. / (2. * c))
                    for key, value in features.iteritems(): 
                        self.weight[label][key] += learn * value
                        self.weight[prediction][key] -= learn * value

                self.time += 1.

    def regularize(self, features):
        for label in self.weight.iterkeys():
            for key in features.iterkeys(): 
                times = self.time - self.last_update[key]
                self.last_update[key] = self.time
                if self.regularization == "l2":
                    self.weight[label][key] *= (1 - self.c) ** times
                elif self.regularization == "l1":
                    self.weight[label][key] = clip(self.weight[label][key], self.c * times)

    def train_average(self, documents, iteration, eta, gamma):
        for label, features in documents:
            if not label in self.weight:
                self.weight[label] = defaultdict(float)
                self.weight_all[label] = defaultdict(float)

        for i in range(iteration):
            shuffle(documents)
            for label, features in documents:

                # prediction
                prediction, scores = self.predict(features)

                # update
                if prediction != label or  scores[prediction] < gamma:
                    for key, value in features.iteritems(): 
                        self.weight[label][key] += eta * value
                        self.weight_all[label][key] += self.time * eta * value
                        self.weight[prediction][key] -= eta * value
                        self.weight_all[prediction][key] -= self.time * eta * value
                    self.time += 1

        # average
        for label, weight in self.weight.iteritems():
            for key in weight.iterkeys():
                weight[key] -= self.weight_all[label][key] / self.time


    def predict(self, features):
        # lazy regularization
        self.regularize(features)

        max_label = None
        scores = {}
        for label, weight in self.weight.iteritems():
            scores[label] = dot(weight, features)
            if max_label == None or scores[label] > scores[max_label]:
                max_label = label
        return (max_label, scores)

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option("-m", dest="mode", default="basic")
    parser.add_option("-r", dest="regularization", default="l2")
    parser.add_option("-t", dest="test", type="float", default=0.1)
    parser.add_option("-s", dest="seed", type="int", default=0)

    # Training parameters
    parser.add_option("-i", dest="iteration", type="int", default=10)
    parser.add_option("-b", dest="bias", type="float", default=1.)
    parser.add_option("-e", dest="eta", type="float", default=0.001)
    parser.add_option("-g", dest="gamma", type="float", default=0.)
    parser.add_option("-c", dest="c", type="float", default=0.)
    parser.add_option("-d", dest="discount", type="float", default=0.)

    (options, args) = parser.parse_args()
    seed(options.seed)
    
    # Load file
    documents = []
    for line in stdin:
        documents.append(parse(line, options.bias, options.discount))

    perceptron = Perceptron()

    # Split documents into train and test data
    index = int(len(documents) * options.test)

    # Train perceptron
    if options.mode == "average":
        perceptron.train_average(documents[index:], options.iteration, options.eta, options.gamma)
    else:
        perceptron.train(documents[index:], options.mode, options.iteration, options.eta, options.gamma, options.regularization, options.c)

    # Test prediction
    correct = 0.
    for label, features in documents[:index]:
        prediction, scores = perceptron.predict(features)
        if prediction == label:
            correct += 1.
    
    # Output accuracy
    print correct / index

