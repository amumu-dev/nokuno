#!/usr/bin/env python
#encoding: utf-8
from format import format
from copy import deepcopy
from collections import defaultdict

class Word:
    def __init__(self, pos, lemma, length):
        self.pos = pos
        self.lemma = lemma
        self.length = length
        self.next = []

    def __repr__(self):
        if self.next:
            r = str(self.next) if self.next else u""
            s = u"(%s, %s)\n%s" % (unicode(self.pos), self.lemma, r)
            return s.replace(u"\n",u"\n\t")
        else:
            s = u"(%s, %s)\n" % (unicode(self.pos), self.lemma)
            return s

class Analyzer:
    def __init__(self):
        self._BOS_ENTRY = Word('BOS', u"BOS", 1)
        self._EOS_ENTRY = Word('EOS', u"EOS", 1)

        self.dictionary = {
            u"かれ": [Word('V', u"枯れ", 2), Word('N', u"彼", 2)],
            u"の": [Word('J', u"の", 1)],
            u"く": [Word('N', u"区", 1)],
            u"くる": [Word('V', u"来る", 2)],
            u"くるま": [Word('N', u"車", 3)],
            u"ま": [Word('N', u"間", 1)],
            u"で": [Word('J', u"で", 1)],
            u"でま": [Word('N', u"デマ", 2)],
            u"まつ": [Word('N', u"松", 2), Word('V', u"待つ", 2)],
            u"つ": [Word('N', u"津", 1)],
        }
        self.ctable = set([
          ('BOS', 'N'), ('BOS', 'V'),
          ('N', 'J'), ('J', 'N'), ('J', 'V'),
          ('V', 'N'), ('V', 'J'), ('V', 'EOS')])

    def is_connectable(self, bnode, cnode):
        return (bnode.pos, cnode.pos) in self.ctable

    def common_prefix_search(self, key):
        ret = []
        for i in range(len(key)+1):
            if key[:i] in self.dictionary:
                ret += self.dictionary[key[:i]]
        return ret

    def analyze(self, sent):
        bos_node = self._BOS_ENTRY
        end_node_list = defaultdict(list)
        end_node_list[0].append(bos_node)
        for i in range(0, len(sent)+1):
            if i < len(sent):
                cps_results = self.common_prefix_search(sent[i:])
            else:
                cps_results = [self._EOS_ENTRY]

            for centry in cps_results:
                cnode = deepcopy(centry)

                for bnode in end_node_list[i]:
                    if self.is_connectable(bnode, cnode):
                        bnode.next.append(cnode)
                        end_nodes = end_node_list[i+centry.length]
                        if not cnode in end_nodes:
                            end_nodes.append(cnode)
        return self.enum_solutions(bos_node)

    def enum_solutions(self, node):
        results = []
        if node.lemma == u'EOS':
            return [[u'EOS']]
        for nnode in node.next:
            for solution in self.enum_solutions(nnode):
                results.append([node.lemma] + solution)
        return results


if __name__ == "__main__":
    analyzer = Analyzer()
    res = analyzer.analyze(u"かれのくるまでまつ")
    print '\n'.join('/'.join(sent) for sent in res)

