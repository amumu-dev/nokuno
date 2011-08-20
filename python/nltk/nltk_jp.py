#!/usr/bin/env python
#encoding: utf-8

import sys
reload(sys)
sys.setdefaultencoding('utf-8')

import nltk
from nltk.corpus.reader import *
from nltk.corpus.reader.util import *
from nltk.text import Text

def JapaneseCorpusReader(root, fieldids):
    jp_sent_tokenizer = nltk.RegexpTokenizer(u'[^ 「」！？。]*[！？。]')
    jp_chartype_tokenizer = nltk.RegexpTokenizer(u'([ぁ-んー]+|[ァ-ン]+|[\u4e00-\u9FFF]+|[^ぁ-んァ-ン\u4e00-\u9FFF]+)')
    corpus = PlaintextCorpusReader(root, fieldids,
            encoding = 'utf-8',
            para_block_reader = read_line_block,
            sent_tokenizer = jp_sent_tokenizer,
            word_tokenizer = jp_chartype_tokenizer)

    return corpus
