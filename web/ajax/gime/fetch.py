#!/usr/bin/env python
#encoding: utf-8
from optparse import OptionParser
from urllib import urlopen, quote
from re import sub
from json import loads
from format import format

def convert(query):
    base = "http://www.google.com/transliterate?langpair=ja-Hira|ja&text="
    url = base + quote(query)
    result = urlopen(url).read()
    result = sub(r",\n]", r"\n]", result)
    object = loads(result)
    return object

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option("-q", dest="query", default="へんかん")
    (options, args) = parser.parse_args()
    object = convert(options.query)
    #print format(object)
    print '\n'.join(object[0][1])
