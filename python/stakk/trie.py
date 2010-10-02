#!/usr/bin/env python
#encoding: utf-8
from format import format
from optparse import OptionParser
from sys import stdin

class Trie:
    def __init__(self, data=[]):
        self.children = {}
        self.values = []
        for key, value in data:
            self.insert(key, value)

    def insert(self, key, value):
        if key:
            first, rest = key[0], key[1:]
            if first not in self.children:
                self.children[first] = Trie()
            self.children[first].insert(rest, value)
        else:
            self.values.append(value)

    def common_prefix_search(self, key):
        results = []
        if self.values:
            results = [('', self.values)]
        if not key or not self.children:
            return results
        first, rest = key[0], key[1:]
        if first in self.children:
            children = self.children[first].common_prefix_search(rest)
            results.extend((first + k,v) for k,v in children)
        return results

    def predictive_search(self, key):
        results = []
        if not self.children:
            return results
        if key:
            first, rest = key[0], key[1:]
            if first in self.children:
                children = self.children[first].predictive_search(rest)
                results.extend((first + k,v) for k,v in children)
        else:
            if self.values:
                results.append(('', self.values))
            for k1,v1 in self.children.items():
                children = v1.predictive_search(key)
                results.extend((k1+k,v) for k,v in children)
        return results

    def search(self, key):
        result = None
        if not key and self.values:
            return self.values
        if not key or not self.children:
            return None
        first, rest = key[0], key[1:]
        if first in self.children:
            result = self.children[first].search(rest)
        return result
        
    def display(self, key="", depth=0):
        if self.values:
            print key + "\t" + format(self.values)
        for (k,v) in self.children.items():
            v.display(key + k, depth+1)

if __name__ == '__main__':
    #parse option
    parser = OptionParser()
    parser.add_option("-f", dest="filename")
    parser.add_option("-s", dest="separator", default="\t")
    (options, args) = parser.parse_args()

    trie = Trie()
    if options.filename != None:
        for line in open(options.filename):
            key, value = line.strip().split(options.separator, 1)
            trie.insert(key, value)

        for line in stdin:
            input = line.strip()
            result = trie.common_prefix_search(input)
            print 'common prefix:'
            for i in result:
                print format(i)
            result = trie.predictive_search(input)
            print 'predict:'
            for i in result:
                print format(i)
    else:
        trie.insert('try', 1)
        trie.insert('tryed', 2)
        trie.insert('tryes', 3)
        trie.insert('try', 4)
        trie.display()
        print 'common prefix: ', trie.common_prefix_search('tryes')
        print 'common prefix: ', trie.common_prefix_search('try')
        print 'common prefix: ', trie.common_prefix_search('tryis')
        print 'common prefix: ', trie.common_prefix_search('tr')
        print 'common prefix: ', trie.common_prefix_search('r')
        print 'predict: ', trie.predictive_search('trye')
        print 'predict: ', trie.predictive_search('t')
        print 'predict: ', trie.predictive_search('r')
        print 'search: ', trie.search('try')
        print 'search: ', trie.search('tryed')
        print 'search: ', trie.search('trye')
