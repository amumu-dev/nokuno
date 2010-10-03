#!/usr/bin/env python
#encoding: utf-8
from commands import getoutput
from urllib import unquote

def application(environ, start_response):
    status = '200 OK'
    query = environ['QUERY_STRING'].split('=',1)[1]
    command = "/usr/local/bin/python /home/nokuno/nokuno/web/ajax/gime/fetch.py -q " + unquote(query)
    output = getoutput(command)
    response_headers = [('Content-type', 'text/plain'),
                        ('Content-Length', str(len(output)))]
    start_response(status, response_headers)
    return [output]

