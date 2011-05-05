#!/usr/bin/env python
#encoding: utf-8
import sys

def application(environ, start_response):
    status = '200 OK'
    output = str(environ) + "\n" + str(sys.version_info)
    response_headers = [('Content-type', 'text/plain'),
                        ('Content-Length', str(len(output)))]
    start_response(status, response_headers)

    return [output]

if __name__ == '__main__':
    from wsgiref.simple_server import make_server
    make_server('', 8080, application).serve_forever()
