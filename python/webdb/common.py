#!/usr/bin/env python
# encoding: utf-8

from collections import defaultdict
from optparse import OptionParser
from sys import stdin, exit

class Dic:
    def __init__(self, filename):
        self.ht = defaultdict(list)
        for line in open(filename):
            read, word = line.strip().split("\t")[:2]
            self.ht[read] += [word]
    
    def lookup(self, string, maximum):
        result = defaultdict(list)

        for i in range(len(string)-1):
            for j in range(i+1, min(len(string)+1, i+maximum)):
                read = string[i:j]
                for word in dic.ht[read]:
                    node = Node(word, read, j)
                    result[j] += [node]

        return result

    def find(string):
        return self.ht[string]

class Node:
    def __init__(self, word, read, endpos):
        self.word = word
        self.read = read
        self.endpos = endpos
        self.score = 0.0
        self.prev = False

    def is_bos(self):
        return self.endpos == 0

    def is_eos(self):
        return len(self.read) == 0 and self.endpos != 0

    def __repr__(self):
        return "(%s, %s, %s)" % (self.word, self.read, self.score)

class Graph:
    def __init__(self, dic, string):
        self.nodes = defaultdict(list)

        # lookup dictionary
        self.nodes = dic.lookup(string, 16)

        # push BOS
        bos = Node("BOS", "", 0)
        self.nodes[0] = [bos]

        # push EOS
        self.eos = Node("EOS", "", len(string)+1)
        self.nodes[len(string)+1] = [self.eos]


    def get_prevs(self, node):
        if node.is_eos():
            # eosは長さが0なので特殊な処理が必要
            startpos = node.endpos - 1
            return self.nodes[startpos]
        elif node.is_bos():
            # bosはそれより前のノードがないので特殊な処理が必要
            return []
        else:
            startpos = node.endpos - len(node.read)
            return self.nodes[startpos]

class FeatureFuncs:
    def __init__(self): 
        self.node_features = []
        self.edge_features = []

        node_feature_surface = lambda node: "S" + node.word
        self.node_features += [node_feature_surface]

        node_feature_surface_read = lambda node: "S" + node.word + "\tR" + node.read
        self.node_features += [node_feature_surface]

        edge_feature_surface = lambda prev_node, node: "S" + prev_node.word + "\tS" + node.word
        self.edge_features += [edge_feature_surface]

class Decoder:
    def __init__(self, feature_funcs):
        self.feature_funcs = feature_funcs

    def get_node_score(self, node, w):
        score = 0.0
        for func in self.feature_funcs.node_features:
            feature = func(node)
            score += w[feature]
        return score

    def get_edge_score(self, prev_node, node, w):
        score = 0.0
        for func in self.feature_funcs.edge_features:
            feature = func(prev_node, node)
            score += w[feature]
        return score

    def viterbi(self, graph, w):
        for i in sorted(graph.nodes.keys()):
            for node in graph.nodes[i]:
                if node.is_bos():
                    continue
                node.score = -1000000.0
                node_score_cache = self.get_node_score(node, w)

                for prev_node in graph.get_prevs(node):
                    tmp_score = prev_node.score \
                            + self.get_edge_score(prev_node, node, w) \
                            + node_score_cache
                    if tmp_score >= node.score:
                        node.score = tmp_score
                        node.prev = prev_node

        result = []
        node = graph.eos.prev

        while not node.is_bos():
            result += [(node.word, node.read)]
            node = node.prev

        result.reverse()
        return result

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option("-d", dest="dictionary", default="test/dictionary.txt")
    parser.add_option("-m", dest="model", default="test/model.txt")
    (options, args) = parser.parse_args()

    print "loading.."

    dic = Dic(options.dictionary)
    feature_funcs = FeatureFuncs()
    decoder = Decoder(feature_funcs)
    w = defaultdict(lambda: 0.)

    for line in open(options.model):
        key, value = line.strip().split("\t\t")
        w[key] = float(value)

    if options.dictionary == "test/dictionary.txt":
        graph = Graph(dic, "くるまでまつ")
        result = decoder.viterbi(graph, w)
        print graph.nodes
        print " ".join(word[0] for word in result)
        exit()

    print "input:"

    while True:
        string = raw_input()
        graph = Graph(dic, string)
        result = decoder.viterbi(graph, w)
        print " ".join(word[0] for word in result)

