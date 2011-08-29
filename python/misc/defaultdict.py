#!/usr/bin/env python
# encoding: utf-8
from collections import defaultdict

dic = defaultdict(float)
for i in xrange(10000000):
    j = dic[i]

dic = {}
for i in xrange(10000000):
    j = dic.get(i, 0.)

