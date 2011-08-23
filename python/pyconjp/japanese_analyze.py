#!/usr/bin/env python
#encoding: utf-8
from nltk import *
from nltk.text import *
from nltk.corpus.reader import *
from nltk.corpus.reader.util import *
from nltk.tokenize.api import *
from MeCab import *

# NLTKをUTF-8に対応させる
def init():
    import sys
    reload(sys)
    sys.setdefaultencoding('utf-8')

# Mecabによるトークナイザ
class JPMeCabTokenizer(TokenizerI):
    def __init__(self):
        self.mecab = Tagger('-Owakati')

    def tokenize(self, text):
        result = self.mecab.parse(text.encode('utf-8'))
        return result.decode('utf-8').strip().split(' ')

# コーパスの読み込み
def JapaneseCorpusReader(root, fieldids, encoding='utf-8'):
    jp_sent_tokenizer = RegexpTokenizer(u'[^ 「」！？。]*[！？。]')
    corpus = PlaintextCorpusReader(root, fieldids,
            encoding = encoding,
            para_block_reader = read_line_block,
            sent_tokenizer = jp_sent_tokenizer,
            word_tokenizer = JPMeCabTokenizer())

    return corpus

if __name__ == '__main__':
    init()

    # コーパスの読み込み
    reader = JapaneseCorpusReader("data", "ginga.txt")
    text = Text(reader.words())
    freq = FreqDist(text)

    # 単語カウント
    print "Frequency: "
    freq.tabulate(10)

    # 共起語
    print "Collocations: "
    text.collocations()

    # 自動生成
    print "Generate: "
    text.generate()

    # 検索
    # text.concordance(u"は", 10, 10)

    # 類似語
    # text.similar(u"は")

