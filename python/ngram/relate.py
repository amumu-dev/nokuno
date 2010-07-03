#!/usr/bin/python
#encoding: utf-8
#文字コード認識用
import sys, optparse, MySQLdb, math

class Relate:
    def __init__(self):
        self.cursor = MySQLdb.connect(db="wikipedia", user="nokuno", passwd="nokuno").cursor()

    def get_freq(self, word):
        query = 'select freq from unigram where word = %s limit 1'
        self.cursor.execute(query, left)
        row = self.cursor.fetchone()
        if row == None:
            return None
        return float(row[0])

    def get_pmi(self, left, right, both):
        return -math.log( left * right / both )

    def get_emi(self, left, right, both):
        return -math.log( left * right / both ) * both

if __name__ == '__main__':
    parser = optparse.OptionParser()
    parser.add_option("-t", dest="threshold", type="float", default=5.0)
    parser.add_option("-f", dest="freq", type="float", default=100.0)
    parser.add_option("-e", dest="expect", action="store_true", default=False)
    (o, args) = parser.parse_args()
    relate = Relate()
    size = 300000000.0
    prob = o.freq / size

    for line in sys.stdin:
        (left, right, freq) = line.split()
        l = relate.get_freq(left)
        r = relate.get_freq(right)
        both = float(freq) / size
        if l == None or r == None or l < float(freq) or r < float(freq):
            continue
        lp = l / size
        rp = r / size
        if o.expect:
            score = relate.get_emi(lp, rp, both)
        else:
            score = relate.get_pmi(lp, rp, both)
        if score >= o.threshold:
            print "%s %s\t%f" % (left, right, score)

"""
usage:
    cat bigram.txt | relate.py -t 5 | sort -nr -k3 > pmi.txt
"""
