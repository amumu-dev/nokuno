#!/bin/env python
import tweepy
from optparse import OptionParser

#oauth
consumer_key = ""
consumer_secret = ""
access_key = ""
access_secret = ""

#parse option
parser = OptionParser()
parser.add_option("-c", dest="count", type="int", default=40)
parser.add_option("-p", dest="page", type="int", default=1)
parser.add_option("-l", dest="list")
parser.add_option("-u", dest="user")
parser.add_option("-m", dest="mention", action="store_true")
parser.add_option("-t", dest="tweet")
(o, a) = parser.parse_args()

# OAuth 
auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_key, access_secret) 
api = tweepy.API(auth)

#update status if exists -t option
if o.tweet != None:
    api.update_status(o.tweet)

#get timeline corresponding to option
if o.list != None:
    timeline = api.list_timeline("nokuno", o.list, per_page=o.count, page=o.page)
elif o.user != None:
    timeline = api.user_timeline(o.user, per_page=o.count, page=o.page)
elif o.mention == True:
    timeline = api.mentions(count=o.count, page=o.page)
else:
    timeline = api.home_timeline(count=o.count, page=o.page)
    
#display tweets
for tweet in timeline:
    print tweet.user.screen_name, ":", tweet.text, "at", tweet.created_at

