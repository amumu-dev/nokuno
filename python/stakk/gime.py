#!/usr/bin/env python
#encoding: utf-8
from sys import stdin
from optparse import OptionParser
from urllib2 import urlopen
from urllib import quote
from re import sub
from json import loads
from format import format

base = "http://www.google.com/transliterate?langpair=ja-Hira|ja&text="
for line in stdin:
    input = line.strip()
    query = quote(input)
    url = base + query
    result = urlopen(url).read()
    result = sub(r",\n]", r"\n]", result)
    object = loads(result)
    print format(object)
