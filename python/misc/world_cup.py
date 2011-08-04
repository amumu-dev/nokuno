#!/usr/bin/env python
from sys import stdin
from optparse import OptionParser
from struct import unpack;

# parse the structure
# struct request
# {
#    uint32_t timestamp;
#    uint32_t clientID;
#    uint32_t objectID;
#    uint32_t size;
#    uint8_t method;
#    uint8_t status;
#    uint8_t type;
#    uint8_t server;
# };

if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option("-f", dest="file", default="wc_day10_1.bin")
    (options, args) = parser.parse_args()

    file = open(options.file, "rb")
    while True:
        binary = file.read(20);
        print unpack("IIIIBBBB", binary)
    file.close()
