#!/usr/bin/env python
#encoding: utf-8

from perceptron import *

if __name__ == '__main__':
    parser = OptionParser()
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

    perceptron = Perceptron(weight)

    # Test prediction
    correct = 0.
    for label, features in documents:
        prediction, scores = perceptron.predict(features)
        if prediction == label:
            correct += 1.
    
    # Output accuracy
    print correct / len(documents)

