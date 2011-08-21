#!/usr/bin/env python
#encoding: utf-8
from MeCab import Tagger

# 入力する文字列
text = "こんにちは世界！"
tagger = Tagger()

# 簡易的な解析
print tagger.parse(text)

# 単語ごとの情報を取り出す
node = tagger.parseToNode(text)
while node:
    print node.surface, node.feature
    node = node.next

