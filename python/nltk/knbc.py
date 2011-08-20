#!/usr/bin/env python
# encoding: utf-8
# KNBCコーパスをNLTKで読み込むサンプル

from nltk_jp import *
from nltk.corpus.reader import *
from nltk.corpus.util import LazyCorpusLoader

def _knbc_fileids_sort(x):
    cells = x.split('-')
    return (cells[0], int(cells[1]), int(cells[2]), int(cells[3]))

# コーパスを読み込み
root = nltk.data.find('corpora/knbc/corpus1')
fileids = [f for f in find_corpus_fileids(FileSystemPathPointer(root), ".*") if re.search(r"\d\-\d\-[\d]+\-[\d]+", f)]
knbc = LazyCorpusLoader('knbc/corpus1', KNBCorpusReader, sorted(fileids, key=_knbc_fileids_sort), encoding='euc-jp')
#print "fileids :", knbc.fileids()
print "words :", pp(knbc.words()[:10])
print "parsed_sents :", str(knbc.parsed_sents()[0])
print "tagged_words :", pp(knbc.tagged_words()[:5])

