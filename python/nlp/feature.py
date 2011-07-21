#!/usr/bin/python
#encoding: utf-8

from sys import stdin
from MeCab import Tagger
from optparse import OptionParser

parser = OptionParser()

class FeatureExtractor:
    def __init__(self):
        self.dictionary = {}
        self.categories = {}
        self.tagger = Tagger()

    def parse_document(self, text):
        document = text.split("\t", 4)

        if len(document) != 5:
            return None

        category_name = document[0]
        if not category_name in self.categories:
            self.categories[category_name] = len(self.categories)
        category_id = self.categories[category_name]

        return (category_id, document[-1])

    def feature_extract(self, text):
        morphology = self.tagger.parseToNode(text)
        bag_of_words = {}
        while morphology:
            features = morphology.feature.split(",")
            surface = morphology.surface

            if len(features) > 0 and features[0] == "名詞":
                if not surface in self.dictionary:
                    self.dictionary[surface] = len(self.dictionary)
                word_id = self.dictionary[surface]
                bag_of_words[word_id] = bag_of_words.get(word_id, 0) + 1

            morphology = morphology.next
        return bag_of_words

def to_string(category_id, bag_of_words):
    result = ""
    result += str(category_id) + " "
    words = bag_of_words.items()
    words.sort()
    for key,value in words:
        result += "%d:%d " % (key, value)
    return result

def output_file(filename, documents):
    file = open(filename, "w")
    for category_id, bag_of_words in documents:
        file.write(to_string(category_id, bag_of_words) + "\n")
    file.close()

if __name__ == '__main__':
    # Parse options
    parser = OptionParser()
    parser.add_option("-1", dest="train", default="train.txt")
    parser.add_option("-2", dest="test", default="test.txt")
    parser.add_option("-r", dest="rate", type="float", default=0.1)
    (options, args) = parser.parse_args()

    extractor = FeatureExtractor()
    documents = []

    # Parse documents and extract featues
    for line in stdin:
        document = extractor.parse_document(line.strip())
        if document != None and len(document) == 2:
            bag_of_words = extractor.feature_extract(document[1])
            documents.append((document[0], bag_of_words))
    
    # Split data into train and test file
    index = int(len(documents) * options.rate)
    output_file(options.train, documents[index:])
    output_file(options.test, documents[:index])

