#!/usr/bin/env python
#encoding: utf-8
from urllib2 import urlopen
from urllib import quote
from re import sub

def application(environ, start_response):
    base = "http://www.google.com/transliterate?langpair=ja-Hira|ja&text="
    status = '200 OK'
    query = environ['QUERY_STRING'].split('=',1)[1]
    url = base + query
    result = urlopen(url).read()
    output = sub(r",\n]", r"\n]", result)

    response_headers = [('Content-type', 'text/plain'),
                        ('Content-Length', str(len(output)))]
    start_response(status, response_headers)
    return [output]

