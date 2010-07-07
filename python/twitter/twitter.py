#!/bin/env python
import tweepy, sys
from optparse import OptionParser

#account
userename = ""
password = ""

#parse option
parser = OptionParser()
parser.add_option("--username", dest="username", default=username)
parser.add_option("--password", dest="password", default=password)
parser.add_option("-c", dest="count", type="int", default=50)
parser.add_option("-l", dest="list", help="display list timeline")
parser.add_option("-u", dest="user", help="display user timeline")
parser.add_option("-m", dest="mention", action="store_true", help="display mentions")
(o, a) = parser.parse_args()

#setup tweepy
auth = tweepy.BasicAuthHandler(o.username, o.password)
api = tweepy.API(auth)

#get timeline corresponding to option
if o.list != None:
    timeline = api.list_timeline("nokuno", o.list, per_page=o.count)
elif o.user != None:
    timeline = api.user_timeline(o.user, per_page=o.count)
elif o.mention == True:
    timeline = api.mentions(count=o.count)
else:
    timeline = api.home_timeline(count=o.count)
    
#display tweets
for tweet in timeline:
    print tweet.user.screen_name, ":", tweet.text, "at", tweet.created_at

