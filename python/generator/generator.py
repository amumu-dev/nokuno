#!/usr/bin/python
#encoding: utf-8
import sys, random, MySQLdb

class Generator:
    def __init__(self):
        """ DBに接続 """
        self.db = MySQLdb.connect(db="sourcecode", user="nokuno", passwd="nokuno")
        self.cursor = self.db.cursor()

    @staticmethod
    def test():
        generator = Generator()
        for i in range(30):
            print " ".join(generator.generate())

    def generate(self, length=10, n=5):
        """ 文章を自動生成 """
        result = []
        context = []
        for j in range(length):
            #word = self.backoff(context)
            word = self.smooth(context)
            result.append(word)
            context.append(word)
            if len(context) > n-1:
                context = context[-n:]
        return result

    def smooth(self, context):
        """ スムージングによるサンプリング """
        word = None
        while True:
            if random.random() > 0.1:
                word = self.sampling(context)
            if word != None:
                return word
            context = context[1:]

    def backoff(self, context):
        """ バックオフによるサンプリング """
        while True:
            word = self.sampling(context)
            if word != None:
                return word
            context = context[1:]

    def sampling(self, context):
        """ 単語を自動生成 """
        r = random.random()
        query = 'select word from ngram where context = %s and prob >= %s limit 1'
        if len(context) > 0:
            c = " ".join(context)
        else:
            c = ""
        self.cursor.execute(query, (c, r))
        row = self.cursor.fetchone()
        if row == None:
            return None
        return row[0]


if __name__ == "__main__":
    Generator.test()
