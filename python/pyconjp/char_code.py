#!/usr/bin/env python
# encoding: utf-8
from sys import stdin

hello = u"こんにちは！"

s = stdin.read().decode("utf-8")

f = open("test.txt", "w")
f.write(s.encode("utf-8"))

