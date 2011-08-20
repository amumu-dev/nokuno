#!/usr/bin/env python
# encoding: utf-8
# 「銀河鉄道の夜」をNLTKで解析するサンプル

from nltk_jp import *

# コーパスを読み込み
corpus = JapaneseCorpusReader("data/", "ginga.txt")
text = nltk.Text(corpus.words())

# 単語カウント
freq = nltk.FreqDist(text)
print pp(freq.items()[:20])

# 検索，共起，自動生成
text.concordance(u"苹果", 10, 10)
text.similar(u"カムパネルラ")
text.generate()
