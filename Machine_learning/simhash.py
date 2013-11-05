# -*- conding:utf-8 -*-
import jieba
import jieba.posseg as pseg

class simhash:
    def __init__(self, feature, hashbits = 64):
        self.hashbits = hashbits
        self.hash = self.simhash(feature)
        
    def __str__(self):
        return str(self.hash)
    
    def simhash(self, feature):
        v = [0] * self.hashbits
        for t in [self.strHash(x) for x in feature]:
            for i in range(self.hashbits):
                bitmask = 1 << i
                if t & bitmask:
                    v[i] += 1
                else:
                    v[i] -= 1
        fingerprint = 0
        #print v
        for i in range(self.hashbits):
            if v[i] >= 0:
                fingerprint += (1<<i)
        return fingerprint
    
    def hamming_dis(self, other):
        x = (self.hash ^ other.hash) & ((1<<self.hashbits)-1)
        tot = 0
        while x:
            tot += 1
            x &= x - 1
        return tot

    def similarity(self, other):
        a = float(self.hash)
        b = float(other.hash)
        if a > b:
            return b / a
        else:
            return a / b
    
    def strHash(self, mystr):
        if mystr == "":
            return 0
        x = ord(mystr[0]) << 7
        m = 1000003
        mask = 2**self.hashbits - 1
        for c in mystr:
            x = ((x*m)^ord(c)) & mask
        x ^= len(mystr)
        if x == -1:
            x = -2
        return x

def readAllcontent(filename = ""):
    f = open(filename, 'r')
    content = []
    line = f.readline().rstrip()
    while line:
        content.append(line)
        line = f.readline().rstrip()
    f.close()
    return content

def splitcorus(content):
    wordslist = []
    for obj in content:
        wordslist.append(splitsentence(obj))
    return wordslist

def splitsentence(line):
    words = pseg.cut(line)
    con1 = []
    for w in words:
        key = w.word.encode('utf-8')
        con1.append(key)
    return con1

def process(filename = ''):
    contents = readAllcontent(filename)
    result = []
    wordslist = splitcorus(contents)
    print len(wordslist), 'words'
    cnt = 0
    for obj in wordslist:
        cnt += 1
        hash1 = simhash(obj)
        flag = True
        for re in result:
            hash2 = simhash(re)
            d = hash1.hamming_dis(hash2)
            if d < 10:
               flag = False
               break
        if flag:
            result.append(obj)
        if cnt % 200 == 0:
            print cnt, "times"
    return result

if __name__ == '__main__':
    #s = "你 好 北京"
    #hash1 = simhash(s.split())
    #print hash1
    s = '#2012奔驰新车大盘点#最佳豪华行政座驾：梅赛德斯-奔驰长轴距E级轿车，65年成长史，9代“单传”，1100万成功人士一致共识！创新夜视辅助系统，远见前所未见；顶级Nappa皮饰，尊贵气质尽显；3014mm轴距的挺拔“身段”，脱颖而出……低调奢华，非凡气度!'#'This is a test string for testing'
    hash1 = simhash(splitsentence(s))
   
    s = '#2012奔驰新车大盘点#最佳豪华行政座驾：梅赛德斯-奔驰长轴距E级轿车，65年成长史，9代“单传”，1100万成功人士一致共识！创新夜视辅助系统，远见前所未见；顶级Nappa皮饰，尊贵气质尽显；3014mm轴距的挺拔“身段”，脱颖而出……低调奢华，非凡气度！'#'This is a test string for testing also'
    hash2 = simhash(splitsentence(s))
   
    s = 'nai nai ge xiong cao'
    hash3 = simhash(s.split())
   
    print(hash1.hamming_dis(hash2) , "   " , hash1.similarity(hash2))
    print(hash1.hamming_dis(hash3) , "   " , hash1.similarity(hash3))
    result = process("data_all_weibo_benchi.txt")
    f = open('result.txt', 'w')
    for obj in result:
        mystr = ""
        for o in obj:
            if mystr == "":
                mystr = o
            else:
                mystr = "\3" + o
        f.write(mystr + '\n')
    f.close()
    print len(result)
