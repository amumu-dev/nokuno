#!/usr/bin/env python
#encoding: utf-8
from nltk.corpus.reader import *
from jptokenizer import *
from nltk_jp import *

# 入力する文字列
text = "こんにちは世界！"

reader = PlaintextCorpusReader("data/", "ginga.txt",
        encoding="utf-8",
        para_block_reader = read_line_block,
        sent_tokenizer = jp_sent_tokenizer,
        word_tokenizer = JPMeCabTokenizer())

print " ".join(reader.words()[20:80])

