#!/usr/bin/env python
# encoding: utf-8
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

import string
from xml.sax import make_parser
from xml.sax.handler import ContentHandler
from optparse import OptionParser
import re

class CategoryHandler(ContentHandler):
    def __init__(self):
        self.init()
        self.in_title = False
        self.title = ""

    def init(self):
        self.in_text = False
        self.content = ""
        self.categories = []

    def startElement(self, name, attrs):
        if name == 'text':
            self.init()
            self.in_text = True
        elif name == "title":
            self.in_title = True

    def endElement(self, name):
        if name == 'text':
            categories = re.findall("\[\[Category:([^\t\]\|]+)(\|.+)*\]\]", self.content)
            if categories:
                for category in categories:
                    self.categories += [category[0]]

            if self.title \
                    and re.search(r"^Wikipedia:", self.title) == None \
                    and re.search(u"\(曖昧さ回避\)$", self.title.decode("utf-8")) == None \
                    and re.search(u"^ファイル:", self.title.decode("utf-8")) == None:
                print self.title + "\t" + "\t".join(self.categories)

            self.init()
            self.in_title = False
            self.title = ""

        elif name == "title":
            self.in_title = False

    def characters(self, content):
        if self.in_text:
            self.content += content
        elif self.in_title:
            self.title += content

if __name__ == '__main__':
    opt = OptionParser()
    opt.add_option("-f", dest="file")
    (options, args) = opt.parse_args()

    parser  = make_parser()
    handler = CategoryHandler()
    parser.setContentHandler(handler)
    parser.parse(options.file)

