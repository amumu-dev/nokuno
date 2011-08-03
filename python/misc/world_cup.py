#!/usr/bin/env python
from sys import stdin
from optparse import OptionParser
from struct import unpack;

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option("-f", dest="file", default="wc_day10_1.bin")
    (options, args) = parser.parse_args()

    file = open(options.file, "rb")
    while True:
        binary = file.read(20);
        print unpack("IIIIBBBB", binary)
    file.close()
