#!/usr/bin/env python
from optparse import OptionParser
from urllib import quote, urlopen
from BeautifulSoup import BeautifulSoup, NavigableString
from re import sub

parser = OptionParser()
parser.add_option("-b", dest="base", default="http://eow.alc.co.jp/")
parser.add_option("-c", dest="count", type="int", default=20)
parser.add_option("-p", dest="page", type="int", default=1)
(options, args) = parser.parse_args()

def remove_html_tags(data):
    return sub(r'<.*?>', '', data)

for arg in args:
    url = options.base + quote(arg)
    result = urlopen(url).read()
    soup = BeautifulSoup(urlopen(url))
    result = soup.find("div", id="resultsList")
    start = 1 + options.count * (options.page-1)
    end = start + options.count
    for i in result.contents[1].contents[start:end]:
        print remove_html_tags(str(i)),

