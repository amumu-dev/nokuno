#!/usr/bin/env python
# encoding: utf-8

if __name__ == '__main__':
    from common import *

    parser = OptionParser()
    parser.add_option("-d", dest="dictionary", default="data/juman.dic")
    parser.add_option("-m", dest="model", default="data/mk.model")
    opt.add_option("-e", dest="extend", action="store_true") 
    (options, args) = parser.parse_args()

    print "loading.."

    dic = Dic(options.dictionary)
    feature_funcs = FeatureFuncs(options.extend)
    decoder = Decoder(feature_funcs)
    w = read_weight_map(options.model, dic)

    print "input:"

    while True:
        string = raw_input()
        graph = Graph(dic, string)
        result = decoder.viterbi(graph, w)
        print " ".join(word[0] for word in result)

