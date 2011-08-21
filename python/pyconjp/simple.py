#!/usr/bin/env python
#encoding: utf-8
from format import format
from copy import deepcopy
from collections import defaultdict

class Word:
    def __init__(self, pos, lemma):
        self.pos = pos
        self.lemma = lemma
        self.length = 1
        self.next = []

    def __repr__(self):
        if self.next:
            s = u"(%s, %s)\n%s" % (unicode(self.pos), self.lemma, str(self.next))
            return s.replace(u"\n", u"\n\t")
        else:
            return u"(%s, %s)" % (unicode(self.pos), self.lemma)

class Analyzer:
    def __init__(self):
        self.dic = {
            u"くる": [Word(u'動詞', u"来る")],
            u"くるま": [Word(u'名詞', u"車")],
            u"ま": [Word(u'名詞', u"間")],
            u"で": [Word(u'助詞', u"で")],
            u"まつ": [Word(u'名詞', u"松"),
                Word(u'動詞', u"待つ")],
        }
        for key, value in self.dic.items():
            for word in value:
                word.length = len(key)

        self.table = set([
          (u'文頭', u'名詞'),
          (u'文頭', u'動詞'),
          (u'名詞', u'助詞'),
          (u'助詞', u'動詞'),
          (u'動詞', u'名詞'),
          (u'動詞', u'文末')])

    def connect(self, left, right):
        return (left.pos, right.pos) in self.table

    def lookup(self, key):
        ret = defaultdict(list)
        for i in range(len(key)-1):
            for j in range(i+1, len(key)+1):
                k = key[i:j]
                if k in self.dic:
                    ret[j] += deepcopy(self.dic[k])
        return ret

    def analyze(self, sent):
        nodes = self.lookup(sent)
        nodes[0] = [Word(u'文頭', u'')]
        nodes[len(sent)+1] = [Word(u'文末', u'')]

        for i in range(1, len(sent)+2):
            for right in nodes[i]:
                for left in nodes[i-right.length]:
                    if self.connect(left, right):
                        left.next.append(right)

        return self.enumerate(nodes[0][0])

    def enumerate(self, node):
        results = []
        if node.pos == u'文末':
            return [[]]
        for next in node.next:
            for solution in self.enumerate(next):
                results.append([node.lemma] + solution)
        return results

if __name__ == "__main__":
    analyzer = Analyzer()
    res = analyzer.analyze(u"くるまでまつ")
    print '\n'.join(' '.join(sent[1:]) for sent in res)

