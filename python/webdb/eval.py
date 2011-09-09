#!/usr/bin/env python
# encoding: utf-8

def calc_lcs(a, b):
    table = [ [0 for j in range(len(b) + 1)] for i in range(len(a)+1) ]

    for i in xrange(1, len(a) + 1):
        for j in xrange(1, len(b) + 1):
            if a[i - 1] == b[j - 1]:
                table[i][j] = table[i-1][j-1] + 1
            else:
                table[i][j] = max(table[i-1][j], table[i][j-1])

    return table[-1][-1]

if __name__ == '__main__':
    from common import *

    opt = OptionParser()
    opt.add_option("-d", dest="dictionary", default="data/juman.dic")
    opt.add_option("-m", dest="model", default="data/mk.model")
    opt.add_option("-e", dest="extend", action="store_true") 
    opt.add_option("-v", dest="verbose_mode", action="store_true")
    (options, args) = opt.parse_args()

    print "loading.."

    dic = Dic(options.dictionary)
    feature_funcs = FeatureFuncs()
    decoder = Decoder(feature_funcs)
    w = read_weight_map(options.model, dic)

    print "testing:"

    lcs_sum = 0
    sys_sum = 0
    cps_sum = 0

    for line in open(args[0]):
        sentence = [x.split("/",1) for x in line.strip().split(" ")]
        sentence = [x for x in sentence if len(x) == 2]
        string = "".join(x[1] for x in sentence)

        graph = Graph(dic, string)
        result = decoder.viterbi(graph, w)

        gold = "".join(x[0] for x in sentence).decode("utf-8")
        ret = "".join(x[0] for x in result).decode("utf-8")
        lcs = calc_lcs(gold, ret)

        lcs_sum += lcs
        cps_sum += len(gold)
        sys_sum += len(ret)

        if options.verbose_mode:
            print " ".join(x[0] for x in result)

    precision = 100. * lcs_sum / sys_sum
    recall = 100. * lcs_sum / cps_sum
    fmeasure = 2. / (1/precision + 1/recall)

    print "precision: %2.2f" % (precision)
    print "recall: %2.2f" % (recall)
    print "f-measure: %2.2f" % (fmeasure)

