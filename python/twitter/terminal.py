#!/usr/bin/python
# see http://jspr.tndy.me/2008/05/twitterminal-a-terminal-based-twitter-client-in-python/
import urllib2 as urllib
import base64
import xml.dom.minidom

class Twitter:
    public = 'http://twitter.com/statuses/public_timeline.rss'
    friends = 'http://www.twitter.com/statuses/friends_timeline.xml'
    action = 'public'
    actions = ['public','friends']
    items = []

    def __init__(self):
        pass

    def auth(self,username,password):
        self._username = username
        self._password = password
        self._b64 = base64.encodestring('%s:%s' % (self._username,self._password))
        self._authhead = 'Basic %s' % self._b64

    def setAction(self,action):
        if action not in self.actions:
            return False
        self.action = action

    def fetch(self):
        if self.action == 'public':
            url = self.public
            self._req = urllib.Request(url)
            self._handler = urllib.urlopen(self._req)
            self.parsePublic()
        elif self.action == 'friends':
            url = self.friends
            self._req = urllib.Request(url)
            self._req.add_header('Authorization',self._authhead)
            try:
                self._handler = urllib.urlopen(self._req)
            except IOError, e:
                return False
            self.parseFriends()

    def parsePublic(self):
        txt = self._handler.read()
        feed = xml.dom.minidom.parseString(txt)
        statuses = feed.getElementsByTagName('item')
        for status in statuses:
            self.items.append(status.getElementsByTagName('description')[0].childNodes[0].data)

    def parseFriends(self):
        feed = xml.dom.minidom.parseString(self._handler.read())
        statuses = feed.getElementsByTagName('status')
        for status in statuses:
            self.items.append('%s: %s' % (
                status.getElementsByTagName('screen_name')[0].childNodes[0].data,
                status.getElementsByTagName('text')[0].childNodes[0].data))

    def printall(self):
        for item in self.items:
            print '%sn' % item

if __name__ == '__main__':
    import sys

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

