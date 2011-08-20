#!/usr/bin/env python
# encoding: utf-8
# JEITAコーパスをNLTKで読み込むサンプル

from nltk_jp import *
from nltk.corpus.reader import *
from nltk.corpus.util import LazyCorpusLoader

# コーパスを読み込み
jeita = ChasenCorpusReader('data/jeita_genpaku', r'.*chasen', encoding='utf-8')
print pp(jeita.words()[:10])
print pp(jeita.tagged_sents()[1])
