#!/usr/bin/env python
# coding=utf-8

"""Helper module for WSSE authentication

    (c) 2005-2007 A.Shibata (shibata [at] webcore [dot] co [dot] jp)

$Id: wsseauth.py 246 2007-04-08 05:26:23Z ats $
$URL$
$Rev: 246 $
$Date: 2007-04-08 14:26:23 +0900 (日, 08  4 2007) $

Usage:

req = WSSEAuthRequest('user', 'password')
handle = req.urlopen('http://end.point.to/wsseauth/required/uri')

# Do somethind with handle,handle.read() or so...

"""

__author__ = "Atsushi Shibata <http://coreblog.org>"
__version__ = "$Rev: 246 $"
__copyright__ = "Copyright (c) 2005-2007 A. Shibata"
__license__ = """PSF"""

import urllib2
import random
import base64
import datetime
import sha

class HTTPErrorProcessorCustom(urllib2.HTTPErrorProcessor):
    """
    The custom HTTPErrorProcesser for HTTP error responses,
               which handles code 200 to 207 as a success code
    """

    def http_response(self, request, response):
        code, msg, hdrs = response.code, response.msg, response.info()

        if code not in range(200, 207):
            response = self.parent.error(
                'http', request, response, code, msg, hdrs)

        return response

# Install handler
opener = urllib2.build_opener(HTTPErrorProcessorCustom)
urllib2.install_opener(opener)

class MethodAwareRequest(urllib2.Request):
    """
    A Request class to handle methods like PUT, DELETE, etc.
    """

    def set_method(self,method):
        self._method = method

    def get_method(self):
        try:
            return self._method
        except:
            if self.has_data():
                return "POST"
            else:
                return "GET"


class WSSEAuthRequest:
    """
    Wrapper module to allow http access using WSSE authentication
    """

    dt = datetime.datetime(2005, 12, 12)
    headertmpl = 'UsernameToken Username="%s",' + \
                 'PasswordDigest="%s",' + \
                 'Nonce="%s",' + \
                 'Created="%s"'
    

    def __init__(self, username='', password='', nonce_str=None):
        """Initialize method
           nonce_str is optional
        """
        self.username = username
        self.password = password
        self.nonce_str = nonce_str

    def make_request(self, url, method='GET'):
        """Make WSSE Authentication request,
            and returns urllib2.Request instance
        """
        if not self.username:
            self.username = raw_input("username: ")
        if not self.password:
            self.password = raw_input("password: ")
        #Make informations for authentication
        if not self.nonce_str:
            #Make temporaly nonce string
            nonce_str = str(random.random())+str(WSSEAuthRequest.dt.today())
        else:
            nonce_str = self.nonce_str
        nonce = base64.encodestring(nonce_str).replace('\n', '')
        created = WSSEAuthRequest.dt.now().isoformat()+'Z'
        passwd = self.password
        #Make digest
        d = sha.new(nonce_str+created+passwd)
        digeststr = base64.encodestring(d.digest()).replace('\n', '')

        #Make header string
        headerstr = WSSEAuthRequest.headertmpl % \
                             (self.username, digeststr, nonce, created)

        #Post request
        req = MethodAwareRequest(url)
        req.set_method(method)
        req.add_header('X-WSSE', headerstr)

        return req

    def urlopen(self, url, d = None):
        """Try to access url, alogn with WSSE authentication header"""
        req = self.make_request(url)
        handle = urllib2.urlopen(req, d)
        return handle


if __name__ == '__main__':
    req = WSSEAuthRequest('testuser', 'testpass')
    print req.urlopen('http://b.hatena.ne.jp/atom').read()

