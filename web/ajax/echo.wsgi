#!/usr/bin/env python
#encoding: utf-8

def echo(environ, start_response):
    status = '200 OK'
    output = environ['QUERY_STRING'].split('=',1)[1]
    response_headers = [('Content-type', 'text/plain charset="UTF-8"'),
                        ('Content-Length', str(len(output)))]
    start_response(status, response_headers)

    return [output]

if __name__ == '__main__':
    from wsgiref.simple_server import make_server
    make_server('', 8080, echo).serve_forever()
