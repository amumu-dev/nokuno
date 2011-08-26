#!/usr/bin/env python
# encoding: utf-8

from common import *
from optparse import OptionParser
from sys import *

class Learner:
    def __init__(self, dic, feature_funcs, verbose_mode):
        self.w = defaultdict(float)
        self.dic = dic
        self.decoder = Decoder(feature_funcs)
        self.feature_funcs = feature_funcs
        self.verbose_mode = verbose_mode
        self.learning_rate = 1

    def learn(self, sentence):
        str = "".join(word[1] for word in sentence)
        graph = Graph(self.dic, str)
        result = self.decoder.viterbi(graph, self.w)
        if graph != result:
            self.update_parameters(sentence, result)
        if self.verbose_mode:
            print "result: ", " ".join(word[0] for word in result)

    def convert_to_nodes(self, sentence):
        ret = []
        bos = Node("", "", 0)
        ret += [bos]
        i = 0
        prev = bos

        for x in sentence:
            i += len(x[1])
            node = Node(x[0], x[1], i)
            node.prev = prev
            ret += [node]
            prev = node

        eos = Node("", "", i+1)
        eos.prev = prev
        ret += [eos]

        return ret

    def update_node_score(self, node, diff):
        self.dic.add(node.read, node.word)
        for func in self.feature_funcs.node_features:
            feature = func(node)
            self.w[feature] += diff

    def update_edge_score(self, prev_node, node, diff):
        if not prev_node:
            return
        for func in self.feature_funcs.edge_features:
            feature = func(prev_node, node)
            self.w[feature] += diff

    def update_parameters_body(self, sentence, diff):
        nodes = self.convert_to_nodes(sentence)
        prev_node = False
        for node in nodes:
            self.update_node_score(node, diff)
            self.update_edge_score(prev_node, node, diff)
            prev_node = node

    def update_parameters(self, sentence, result):
        self.update_parameters_body(sentence, self.learning_rate)
        self.update_parameters_body(result, -1 * self.learning_rate)

    def save(self, filename):
        with open(filename, "w") as fp:
            for feature, value in self.w.items():
                if value != 0.:
                    fp.write("%s\t\t%f\n" % (feature, value))

if __name__ == '__main__':
    opt = OptionParser()
    opt.add_option("-m", "--model", dest="model_filename", default="mk.model")
    opt.add_option("-d", "--dic", dest="dic_filename", default="juman.dic")
    opt.add_option("-l", "--learner", dest="learner_type", default="sperceptron")
    opt.add_option("-i", "--iteration", dest="iteration_num", type="int", default=1)
    opt.add_option("-v", "--verbose", dest="verbose_mode", action="store_true") 
    (options, args) = opt.parse_args()

    print "loading.."

    dic = Dic(options.dic_filename)
    feature_funcs = FeatureFuncs()
    learner = Learner(dic, feature_funcs, options.verbose_mode)

    if len(args) == 0: 
        stderr.write("corpus filename not found")
        exit(-1)

    corpus_filename = args.pop()
    corpus_lines = open(corpus_filename).readlines()

    print "learning.."

    for i in range(options.iteration_num):
        for line in corpus_lines:
            if options.verbose_mode:
                print "gold: ", line,
            sentence = [word.split("/") for word in line.strip().split(" ") if len(word.split("/")) == 2]
            learner.learn(sentence)

    learner.save(options.model_filename)

