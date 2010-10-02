#!/usr/bin/env python
#encoding: utf-8
from sys import stdin
from optparse import OptionParser
from urllib2 import urlopen
from re import sub
from json import loads
from format import format

url = "http://www.google.com/transliterate?langpair=ja-Hira|ja&text=%E3%81%B8%E3%82%93%E3%81%8B%E3%82%93"
result = urlopen(url).read()
result = sub(r",\n]", r"\n]", result)
object = loads(result)
print format(object)
