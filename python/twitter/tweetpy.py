#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import tweepy
from pit import Pit

class StreamListener(tweepy.StreamListener):
    def on_data(self, data):
        print data

def main():
    conf   = Pit.get('twitter.com')
    user   = conf['username']
    passwd = conf['password']
    stream = tweepy.Stream(user, passwd, StreamListener())
    stream.filter(track=[sys.argv[1]])

if __name__ == "__main__":
    main()
