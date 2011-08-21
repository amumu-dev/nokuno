#!/usr/bin/env python
#encoding: utf-8
from nltk_jp import *
from format import format

_BOS_ENTRY = {'pos':'BOS', 'lemma':u"BOS", 'length':0}
_EOS_ENTRY = {'pos':'EOS', 'lemma':u"EOS", 'length':0}

dict_entries = [
        [u"かれ", {'pos':'V-Y', 'lemma':u"枯れ"}],
        [u"かれ", {'pos':'V-Z', 'lemma':u"枯れ"}],
        [u"かれ", {'pos':'N', 'lemma':u"彼"}],
        [u"の", {'pos':'J-K', 'lemma':u"の"}],
        [u"く", {'pos':'N', 'lemma':u"区"}],
        [u"くる", {'pos':'V-S', 'lemma':u"来る"}],
        [u"くる", {'pos':'V-T', 'lemma':u"来る"}],
        [u"くるま", {'pos':'N', 'lemma':u"車"}],
        [u"ま", {'pos':'N', 'lemma':u"間"}],
        [u"まで", {'pos':'J-F', 'lemma':u"まで"}],
        [u"で", {'pos':'J-K', 'lemma':u"で"}],
        [u"でま", {'pos':'N', 'lemma':u"デマ"}],
        [u"まつ", {'pos':'N', 'lemma':u"松"}],
        [u"まつ", {'pos':'V-S', 'lemma':u"待つ"}],
        [u"まつ", {'pos':'V-T', 'lemma':u"待つ"}],
        [u"つ", {'pos':'N', 'lemma':u"津"}]
        ]

def insert(trie, key, value):
    if key:
        first, rest = key[0], key[1:]
        if first not in trie:
            trie[first] = {}
        insert(trie[first], rest, value)
    else:
        if not 'value' in trie:
            trie['value'] = []
        trie['value'].append(value)

def common_prefix_search(trie, key):
    ret = []
    if 'value' in trie:
        ret += trie['value']
    if key:
        first, rest = key[0], key[1:]
        if first in trie:
            ret += common_prefix_search(trie[first], rest)
    return ret

def is_connectable(bnode, cnode):
     ctable = set([
          ('BOS', 'N'), ('BOS', 'V'), ('BOS', 'T'),
          ('T', 'N'), ('N', 'J'), ('J', 'N'), ('J', 'V'),
          ('V-T', 'N'), ('V-T', 'J-F'), ('V-Y', 'A'), ('V-S', 'EOS'), ('A', 'EOS')])
     bpos = bnode['entry']['pos']
     bpos_s = bpos.split('-')[0]
     cpos = cnode['entry']['pos']
     cpos_s = cpos.split('-')[0]
     return (((bpos, cpos) in ctable) or ((bpos_s, cpos) in ctable)
         or ((bpos, cpos_s) in ctable) or ((bpos_s, cpos_s) in ctable))

def analyze_simple(trie, sent, connect_func=lambda x, y: True):
    bos_node = {'next':[], 'entry': _BOS_ENTRY}
    end_node_list = nltk.defaultdict(list)
    end_node_list[0].append(bos_node)
    for i in range(0, len(sent)+1):
        if i < len(sent):
            cps_results = common_prefix_search(trie, sent[i:].encode('utf-8'))
        else:
            cps_results = [_EOS_ENTRY]

        for centry in cps_results:
            cnode = {'next':[], 'entry':centry}

            for bnode in end_node_list[i]:
                if connect_func(bnode, cnode):
                    bnode['next'].append(cnode)
                    end_nodes = end_node_list[i+centry['length']]
                    if not cnode in end_nodes: end_nodes.append(cnode)

    return enum_solutions(bos_node)

def enum_solutions(node):
     results = []
     if node['entry']['lemma'] == u'EOS':
        return [[u'EOS']]
     for nnode in node['next']:
        for solution in enum_solutions(nnode):
           results.append([node['entry']['lemma']]+solution)
     return results


if __name__ == "__main__":
    matrie = {}
    for entry in dict_entries:
        entry[1]['length'] = len(entry[0])
        insert(matrie, entry[0].encode('utf-8'), entry[1])

    #print format(matrie)
    res = analyze_simple(matrie, u"かれのくるまでまつ", is_connectable)
    print '\n'.join('/'.join(sent) for sent in res)
