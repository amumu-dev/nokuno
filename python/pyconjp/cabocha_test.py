#!/usr/bin/env python
#encoding: utf-8
from CaboCha import *

# 入力する文字列
text = "こんにちは世界！"
parser = Parser("--charset=UTF8")

print parser.parseToString(text)
tree = parser.parse(text)
print tree.toString(FORMAT_LATTICE)
print tree.toString(FORMAT_XML)
