# -*- coding: cp936 -*-
# 基于用户的协同过滤算法
# atthor:John
# date : 2013-05-19

import random
import math

class userCF:
    def __init__(self, datafile = None):
        self.datafile = datafile;
        self.readData();
        self.splitData(3, 47);
    def readData(self, datafile = None):
        # read the file
        self.datafile = datafile or self.datafile
        self.data = []
        for line in open(self.datafile):
            userid,itemid,record,_ = line.split();
            self.data.append((userid, itemid, int(record)))
            
    def splitData(self, k, seed, data = None, M = 8):
        """
            split data set into test set and train set
            test data : train data = 1 : M - 1
        """
        self.testdata = {}
        self.traindata = {}
        data = data or self.data
        random.seed(seed)
        for user, item, record in data:
            if random.randint(0,M) == k:
                self.testdata.setdefault(user, {})
                self.testdata[user][item] = record
            else:
                self.traindata.setdefault(user, {})
                self.traindata[user][item] = record
                
    def userSimilarity(self, train = None):
        """
            cal the user similarity
        """
        train = train or self.traindata
        self.userSim = dict()
        for u in train.keys():
            for v in train.keys():
                if u == v:
                    continue
                self.userSim.setdefault(u, {})
                self.userSim[u][v] = len(set(train[u].keys()) & set(train[v].keys()))
                self.userSim[u][v] /= math.sqrt(len(train[u]) * len(train[v]) * 1.0)
                
    def userSimlarityBest(self, train= None):
        """
            use the reverse table to cal the sim between of user u and user v
            c[u][v] will be added 1 if u and v in the same good list
        """
        train = train or self.traindata
        self.userSimBest = dict()
        item_users = dict()
        for u, item in train.items():
            for i in item.keys():
                item_users.setdefault(i, set())
                item_users[i].add(u)
        user_item_count = dict() # 用户包含的商品个数
        count = dict() # 用户u和v共有的商品个数
        for item, users in item_users.items():
            for u in users:
                user_item_count.setdefault(u, 0)
                user_item_count[u] += 1
                for v in users:
                    if u == v:
                        continue
                    count.setdefault(u, {})
                    count[u].setdefault(v, 0)
                    count[u][v] += 1
        for u, related_users in count.items():
            self.userSimBest.setdefault(u,dict())
            for v, cuv in related_users.items():
                self.userSimBest[u][v] = cuv / math.sqrt(user_item_count[u] * user_item_count[v] * 1.0);

    def recommend(self, user, train = None, k = 8, nitem = 40):
        """
            recommend the top k user which are have the higher similarity with user.
            nitem 表示推荐给用户的商品数量
        """
        train = train or self.traindata
        rank = dict()
        interacted_items = train.get(user, {})
        # wuv 用户相似度
        # rvi 用户v对i的兴趣度
        for v, wuv in sorted(self.userSimBest[user].items(), key = lambda x : x[1], reverse = True)[0:k]:
            for i, rvi in train[v].items():
                if i in interacted_items:
                    continue;
                rank.setdefault(i, 0)
                rank[i] += wuv
        return dict(sorted(rank.items(), key = lambda x : x[1], reverse = True)[0:nitem])

    def recallAndPrecision(self, train = None, test = None, k = 8, nitem = 10):
        """
            cal the recall and precision
        """
        train = train or self.traindata
        test = test or self.testdata
        recall = 0;
        precision = 0;
        hit = 0;
        for user in train.keys():
            tu = test.get(user, {})
            rank = self.recommend(user, train = train, k = k, nitem = nitem)
            for item, pui in rank.items():
                if item in tu:
                    hit += 1
            recall += len(tu)
            precision += nitem
        return (hit / (recall * 1.0), hit / (precision * 1.0))
        

def testRecommdation():
    uscf = userCF("u.data")
    uscf.readData()
    uscf.splitData(4, 100)
    uscf.userSimlarityBest()
    user = "345"
    rank = uscf.recommend(user,k = 3)
    for i, rvi in rank.items():
        items = uscf.testdata.get(user, {})
        record = items.get(i, 0)
        print "%5s: %.4f--%.4f" %(i,rvi, record)

def testUserCF():
    uscf = userCF("u.data")
    uscf.userSimlarityBest()
    print "%3s%20s%20s" % ('K',"recall",'precision')
    for k in [5, 10, 20, 40, 80, 160]:
        recall, precision = uscf.recallAndPrecision(k = k)
        print "%3d%19.3f%%%19.3f%%" % (k, recall*100, precision*100)
        
if __name__ == "__main__":
    # testRecommdation()
    testUserCF()
