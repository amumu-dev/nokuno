#!/usr/bin/python
# see http://jspr.tndy.me/2008/05/twitterminal-a-terminal-based-twitter-client-in-python/
import sys
from twit import Twitter

twit = Twitter()
if len(sys.argv) == 1:
    twit.setAction('public')
else:
    twit.setAction(sys.argv[1])
if (twit.action == 'friends'): # needs authentication - check sys - 2 is username - 3 is password
    if len(sys.argv) == 4:
        twit.auth(sys.argv[2],sys.argv[3])
    else:
        twit.setAction('public')
if twit.fetch() is False:
    print 'Username or password was incorrect'
twit.printall()
