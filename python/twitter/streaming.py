#!/usr/bin/env python
import sys, tweepy
from optparse import OptionParser

class StreamListener(tweepy.StreamListener):
    def on_data(self, data):
        print data

def main():
    parser = OptionParser()
    parser.add_option("-u", dest="username")
    parser.add_option("-p", dest="password")
    (o, a) = parser.parse_args()
    stream = tweepy.Stream(o.username, o.password, StreamListener())
    stream.sample()

if __name__ == "__main__":
    main()
