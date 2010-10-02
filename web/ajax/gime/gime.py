#!/usr/bin/env python
#encoding: utf-8
from urllib import urlopen, quote

def convert(query):
    base = "http://www.google.com/transliterate?langpair=ja-Hira|ja&text="
    url = base + query
    result = urlopen(url).read()
    cands = result.split("\n")[5].split(",")
    output = "\n".join([i[1:-1] for i in cands])
    return output

def application(environ, start_response):
    status = '200 OK'
    query = environ['QUERY_STRING'].split('=',1)[1]
    output = convert(query)
    response_headers = [('Content-type', 'text/plain'),
                        ('Content-Length', str(len(output)))]
    start_response(status, response_headers)
    return [output]

if __name__ == '__main__':
    query = "わたし"
    result = convert(query)
    print result
