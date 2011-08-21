#!/usr/bin/env python
#encoding: utf-8
from CaboCha import *
text = "きっと何者にもなれないお前たちに告げる"
parser = Parser("--charset=UTF8")
print parser.parseToString(text)

"""
tree = parser.parse(text)
print tree.toString(FORMAT_LATTICE)
print tree.toString(FORMAT_XML)
"""
