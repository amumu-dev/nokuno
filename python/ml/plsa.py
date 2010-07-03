#!/usr/bin/env python
# -*- coding: utf-8 -*-

import math,random

class plsa:

    def __init__(self,n,nz=2):
        """ n:DW行列 nz:潜在変数の数"""
        self.n = n
        self.nz = nz
        
        # num of the docs
        self.nd = len(n)
        # num of the words
        self.nw = len(n[0])

        # initialize the probability
        self.pdwz = self.arr([ self.nd, self.nw, self.nz ]) # P(z|d,w)
        self.pzw  = self.arr([ self.nz, self.nw ])          # P(w|z)
        self.pzd  = self.arr([ self.nz, self.nd ])          # P(d|z)
        self.pz   = self.arr([ self.nz ])                   # P(z)
        self.pdw  = self.arr([ self.nd, self.nw ])          # P(d,w)
        
        
    def train(self,k=1000):
        # 収束するまで繰り返す
        tmp = 0
        for i in range(k):
            self.e_step()
            self.m_step()
            L = self.likelihood()
            # 収束したか
            if abs(L - tmp) < 1.0e-10:
                break
            else:
                tmp = L
        
    @staticmethod
    def normalized(list):
        """ 合計が1になるように正規化する """
        total = sum(list)
        return map(lambda a: a/total, list)

    @staticmethod
    def arr(list):
        """ 多次元配列の生成する
        list=[M,N...] としたら M x N x... で要素がランダムの配列を返す """
        if len(list) > 1:
            return [ plsa.arr(list[1:]) for i in range(list[0]) ]
        else:
            return plsa.normalized([ random.random() for i in range(list[0]) ])

    def likelihood(self):
        """ log-liklihood """
        # P(d,w)
        for d in range(self.nd):
            for w in range(self.nw):
                self.pdw[d][w] = sum([ self.pz[z]*self.pzd[z][d]*self.pzw[z][w] for z in range(self.nz) ])
        # Σ n(d,w) log P(d,w)
        return sum([ self.n[d][w]*math.log(self.pdw[d][w]) for d in range(self.nd) for w in range(self.nw) ])

    def e_step(self):
        """ E-step """
        # P(z|d,w)
        for d in range(self.nd):
            for w in range(self.nw):
                for z in range(self.nz):
                    self.pdwz[d][w][z] = self.pz[z]*self.pzd[z][d]*self.pzw[z][w]
                self.pdwz[d][w] = self.normalized(self.pdwz[d][w])

    def m_step(self):
        """ M-step """
        # P(w|z)
        for z in range(self.nz):
            for w in range(self.nw):
                self.pzw[z][w] = sum([ self.n[d][w]*self.pdwz[d][w][z] for d in range(self.nd) ])
            self.pzw[z] = self.normalized(self.pzw[z])
        # P(d|z)
        for z in range(self.nz):
            for d in range(self.nd):
                self.pzd[z][d] = sum([ self.n[d][w]*self.pdwz[d][w][z] for w in range(self.nw) ])
            self.pzd[z] = self.normalized(self.pzd[z])
        # P(z)
        for z in range(self.nz):
            self.pz[z] = sum([ self.n[d][w]*self.pdwz[d][w][z] for d in range(self.nd) for w in range(self.nw) ])
        self.pz = self.normalized(self.pz)

if __name__ == '__main__':
    n = [[1,1,0,0],
         [0,0,1,1],
         [0,0,0,1]]
    p = plsa(n)
    p.train()
    print 'pz', p.pz
    print 'pzd', p.pzd
    print 'pzw', p.pzw
    print 'pdwz', p.pdwz



