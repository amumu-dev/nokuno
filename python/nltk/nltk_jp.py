#!/usr/bin/env python
#encoding: utf-8
# NLTKを日本語で使うためのユーティリティ集

# NLTKがutf-8に対応していないのでシステムのエンコーディングを変更して強引に対応させる
import sys
reload(sys)
sys.setdefaultencoding('utf-8')


import nltk
from nltk.corpus.reader import *
from nltk.corpus.reader.util import *
from nltk.text import Text

# NLTKで日本語の平文コーパスを読み込む
# 単語区切りはひらがな，カタカナ，それ以外の文字種で区切る
def JapaneseCorpusReader(root, fieldids, encoding='utf-8'):
    jp_sent_tokenizer = nltk.RegexpTokenizer(u'[^ 「」！？。]*[！？。]')
    jp_chartype_tokenizer = nltk.RegexpTokenizer(u'([ぁ-んー]+|[ァ-ン]+|[\u4e00-\u9FFF]+|[^ぁ-んァ-ン\u4e00-\u9FFF]+)')
    corpus = PlaintextCorpusReader(root, fieldids,
            encoding = encoding,
            para_block_reader = read_line_block,
            sent_tokenizer = jp_sent_tokenizer,
            word_tokenizer = jp_chartype_tokenizer)

    return corpus


import re, pprint

# Pythonで日本語を含むオブジェクトを表示するための関数
def pp(obj):
    pp = pprint.PrettyPrinter(indent=4, width=160)
    str = pp.pformat(obj)
    return re.sub(r"\\u([0-9a-f]{4})", lambda x: unichr(int("0x"+x.group(1), 16)), str)

