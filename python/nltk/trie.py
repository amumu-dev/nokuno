#!/usr/bin/python
# Natural Language Toolkit: trie

import nltk,pprint

def insert(trie, key, value):
    if key:
        first, rest = key[0], key[1:]
        if first not in trie:
            trie[first] = {}
        insert(trie[first], rest, value)
    else:
        trie['value'] = value

if __name__ == '__main__':
    trie = nltk.defaultdict(dict)
    insert(trie, 'chat', 'cat')
    insert(trie, 'chien', 'dog')
    insert(trie, 'chair', 'flesh')
    insert(trie, 'chic', 'stylish')
    trie = dict(trie)               # for nicer printing
    trie['c']['h']['a']['t']['value']

    pprint.pprint(trie)
