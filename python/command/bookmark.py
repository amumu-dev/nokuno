#!/usr/bin/env python
from pyhatebu import PyHatebu
from optparse import OptionParser
from ConfigParser import SafeConfigParser
from os.path import expanduser

#parse option
parser = OptionParser()
parser.add_option("-c", dest="comment", default="")
parser.add_option("-f", dest="file", default=expanduser("~/.settings/bookmark.conf"))
(options, args) = parser.parse_args()

#parse config
config = SafeConfigParser()
config.read(options.file)
user = config.get("account", "user")
password = config.get("account", "password")

#post bookmark
bookmark = PyHatebu(user, password)
for url in args:
    information = bookmark.post(url, options.comment, [])

