#!/usr/bin/env python
# coding=utf-8
"""Wrapper module for Hatena API

    (c) 2005-2007 A.Shibata (shibata [at] webcore [dot] co [dot] jp)

$Id: pyhatebu.py 243 2007-04-08 05:18:21Z ats $
$URL$
$Rev: 243 $
$Date: 2007-04-08 14:18:21 +0900 (日, 08  4 2007) $


使い方:
>>> # はてなのアカウント情報をもとにエンドポイントを作ります
>>> # ユーザ名とパスワードは省略できます。省略した場合，アクセス時にプロンプトが出ます
>>> from pyhatebu import PyHatebu
>>> h = PyHatebu('user', 'pass') 
>>> # エンドポイントを使ってブックマークを追加します。コメントやタグも指定できます
>>> i = h.post('http://www.python.org', 'Python本家サイト', ['python', 'dev'])
>>> # ブックマーク追加時に返ってくるオブジェクトには，追加したブックマークの情報が入ってます
>>> i.link                    # URLを表示
'http://www.python.org'
>>> i.title                   # タイトルを表示
'Python Programming Language -- Official Website'
>>> i.subject                 # タグを表示
['python', 'dev']
>>> print i.summary           # コメントを表示
Python本家サイト
>>> i.getCount()              # ブックマークの件数を取得
53
>>> i.subject.append('LL')    # タグはリストです。タグを追加します
>>> # エンドポイントにオブジェクトを渡してを使ってブックマークの内容を更新
>>> h.edit(i)
>>> # エンドポイントにオブジェクトを渡してを使ってブックマークを削除
>>> h.delete(i)
>>> # エンドポイントを使って最新のフィードを取得
>>> # フィードはオブジェクトとして返ってくる。URLとタイトルを表示
>>> for i in h.feed():
...     print i.link, i.title
... 
リンクとURLのリスト...

"""

__author__ = "Atsushi Shibata <http://coreblog.org>"
__version__ = "$Rev: 243 $"
__copyright__ = "Copyright (c) 2005-2007 A. Shibata"
__license__ = """PSF"""

import urllib2
import re
import datetime, time
import xmlrpclib
try:
    # for Python 2.5
    from xml.etree import ElementTree
except:
    from elementtree import ElementTree

from wsseauth import WSSEAuthRequest

def make_datetime(dttext):
    """
    function to parse datetime string and
    convert it to datetime.datetime object.

    >>> d = make_datetime('2005-04-07T18:36:00+09:00')
    >>> d
    datetime.datetime(2005, 4, 7, 18, 36)
    >>> d.hour, d.minute, d.second
    (18, 36, 0)
    """
    if not dttext:
        return
    dttext = dttext.replace('+09:00', '')
    return datetime.datetime(*time.strptime(dttext, "%Y-%m-%dT%H:%M:%S")[:6])

def resp2HatebuItem(src):
    """
    Make HatebuItem instance from response
    """
    e = ElementTree.fromstring(src)
    d = {'subject':[]}
    for elem in e.getiterator():
        # loop over elements
        t = elem.tag
        if t.endswith('}title'):
            d['title'] = elem.text
        elif t.endswith('}link'):
            rel = elem.attrib.get('rel', '')
            if rel == 'related':
                d['link'] = elem.attrib.get('href', '')
            if rel == 'alternate':
                d['edit_id'] = elem.attrib.get('href', '').split('#')[1]
            if rel == 'service.edit':
                d['service_edit'] = elem.attrib.get('href', '')
        elif t.endswith('}author'):
            d['author'] = ''.join([x.text for x in elem.getiterator()
                                    if x.tag.endswith('name') ])
        elif t.endswith('}issued'):
            d['issued'] = make_datetime(elem.text)
        elif t.endswith('}id'):
            d['id'] = elem.text
        elif t.endswith('}summary'):
            d['summary'] = elem.text
        elif t.endswith('}subject'):
            d['subject'].append(elem.text)
    return HatebuItem(**d)

class PyHatebu(WSSEAuthRequest):
    """Python wrapper class for HATENA Bookmark ATOM API"""

    _root_endpoint = 'http://b.hatena.ne.jp/atom'
    _post_uri = 'http://b.hatena.ne.jp/atom/post'
    _edit_uri = 'http://b.hatena.ne.jp/atom/edit/'
    _feed_uri = 'http://b.hatena.ne.jp/atom/feed'

    _post_xml = """<entry xmlns="http://purl.org/atom/ns#">
<link type="text/html" rel="related" href="%s" />
<summary type="text/plain">%s</summary>
</entry>"""
    _edit_xml = """<entry xmlns="http://purl.org/atom/ns#">
<link type="text/html" rel="related" href="%s" />
<title>%s</title>
<summary type="text/plain">%s</summary>
</entry>"""

    def __init__(self, username='', password=''):
        """
        Initialization
        """
        self.handle = None
        self.post_uri = ''
        self.feed_uri = ''
        #Initialize WSSEAuthRequest
        WSSEAuthRequest.__init__(self, username, password)

    def make_handle(self):
        """
        Trying to make handle, if not exist.
        """
        if not self.handle:
            # Tring to make WSSE authentication
            self.handle = self.urlopen('http://b.hatena.ne.jp/atom')
            src = self.handle.read()

    def make_hatena_request(self, uri, method='POST', data=None):
        """
        Try to make a request to hatena bookmark
        """
        # Try to make handle, if not exist
        self.make_handle()
        # Try to make request
        request = self.make_request(uri, method=method)
        if data:
            # Adding data
            request.add_data(data)
            # Setting content-type
            request.add_header('Content-Type','text/xml')
        return request

    def post(self, url, comment='', tags=[]):
        """
        Post a new url and comment.
        """
        xmldata = self._post_xml % (url,
                            ''.join(['[%s]' % x for x in tags]) + comment)
        req = self.make_hatena_request(self._post_uri, 'POST', xmldata)
        # Make request and HatebuItem instance
        return resp2HatebuItem(urllib2.urlopen(req).read())

    def get(self, item):
        """
        Get a exist url and comment.
        """
        req = self.make_hatena_request(self._edit_uri+item.edit_id, 'GET')
        return resp2HatebuItem(urllib2.urlopen(req).read())

    def edit(self, item):
        """
        edit a exist bookmark item
        """
        xmldata = self._edit_xml % (item.link, item.title,
                ''.join(['[%s]' % x for x in item.subject]) + item.summary)
        xmldata = xmldata.encode('utf-8', 'ignore')
        req = self.make_hatena_request(self._edit_uri+item.edit_id,
                                                        'PUT', xmldata)
        urllib2.urlopen(req)

    def delete(self, item):
        """
        delete a exist bookmark item
        """
        req = self.make_hatena_request(self._edit_uri+item.edit_id, 'DELETE')
        urllib2.urlopen(req)

    def feed(self):
        """
        get feeds
        """
        req = self.make_hatena_request(self._feed_uri, method='GET')
        # Make request and HatebuItem instance
        elems = ElementTree.fromstring(urllib2.urlopen(req).read())
        for e in elems.getiterator('{http://purl.org/atom/ns#}entry'):
            yield resp2HatebuItem(ElementTree.tostring(e))


class HatebuItem(object):
    """
    The class for hatena bookmark item
    """
    __slots__ = ('handler', 'title', 'link', 'author', 'issued',
                 'id', 'summary', 'subject', 'edit_id', 'service_edit')
    xmlrpc_endpoint_url = 'http://b.hatena.ne.jp/xmlrpc'
    def __init__(self, handler=None, **kws):
        """
        Initialize HatebuItem instance
        """
        self.handler = handler
        if kws:
            all = list(self.__slots__)
            all.remove('handler')
            for k in all:
                if k in kws:
                    setattr(self, k, kws[k])

    def getCount(self):
        """
        Get count of bookmark
        """
        s = xmlrpclib.Server(self.xmlrpc_endpoint_url)
        return s.bookmark.getCount(self.link).get(self.link, 0)

def _test():
    import doctest
    doctest.testmod()

if __name__ == "__main__":
    _test()


