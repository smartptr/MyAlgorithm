'''
function: use the fp growth algorithm to realize the frequente items mining
author: John_czg1989
date: 2013-08-05
'''

class treeNode:
    def __init__(self, nameValue, numOccur, parent):
        self.name = nameValue
        self.count = numOccur
        self.nodeLink = None
        self.parent = parent
        self.child = {}
        
    def inc(self, numOccur):
        self.count += numOccur
        
    def disp(self, ind = 1):
        print ' '*ind, self.name, ' ', self.count
        for child in self.child.values():
            child.disp(ind+1)

# create tree
def createTree(dataSet, minSup=1):
    headerTable = {}
    for trans in dataSet:
        for item in trans:
            headerTable[item] = headerTable.get(item, 0) + dataSet[trans]
    for k in headerTable.keys():
        if headerTable[k] < minSup:
            del(headerTable[k])
    freqItemSet = set(headerTable.keys())
    if len(freqItemSet) == 0:
        return None, None
    for k in headerTable:
        headerTable[k] = [headerTable[k], None] # header table
    retTree = treeNode('NullSet', 1, None)
    for tranSet, count in dataSet.items(): # create by each transcation
        localD = {} # cal the occur number
        for item in tranSet:
            if item in freqItemSet:
                localD[item] = headerTable[item][0]
        if len(localD) > 0:
            orderedItems =[v[0] for v in sorted(localD.items(), \
                            key = lambda p: p[1], reverse = True)]
            updateTree(orderedItems, retTree, headerTable, count)
    return retTree, headerTable
    
def updateTree(items, inTree, headerTable, count):
    if items[0] in inTree.child:
        inTree.child[items[0]].inc(count)
    else:
        inTree.child[items[0]] = treeNode(items[0], count, inTree)
        if headerTable[items[0]][1] == None:
            headerTable[items[0]][1] = inTree.child[items[0]]
        else:
            updateHeader(headerTable[items[0]][1], inTree.child[items[0]])
    if len(items) > 1:
        updateTree(items[1::], inTree.child[items[0]], headerTable, count)

def updateHeader(nodeToTest, targetNode):
    while nodeToTest.nodeLink != None:
        nodeToTest = nodeToTest.nodeLink
    nodeToTest.nodeLink = targetNode

# find the prefix path of a node
def ascendTree(leafNode, prefixPath): #from leaf to parent
    if leafNode.parent != None:
        prefixPath.append(leafNode.name)
        ascendTree(leafNode.parent, prefixPath)

# find all the prefix base pattern of the node whose name is treenode.name 
def findPrefixPath(basePat, treeNode): # basePat: condition pattern base
    condPats = {}
    while treeNode != None:
        prefixPath = []
        ascendTree(treeNode, prefixPath)
        if len(prefixPath) > 1:
            condPats[frozenset(prefixPath[1:])] = treeNode.count
        treeNode = treeNode.nodeLink
    return condPats

def mineTree(inTree, headerTable, minSup, prefix, freqItemList):
    bigL = [v[0] for v in sorted(headerTable.items(), key = lambda p:p[1])]
    for basePat in bigL:
        newFreqSet = prefix.copy()
        newFreqSet.add(basePat)
        freqItemList.append(newFreqSet)
        condPattBases = findPrefixPath(basePat, headerTable[basePat][1])
        myCondTree, myHead = createTree(condPattBases, minSup)
        if myHead != None:
            mineTree(myCondTree, myHead, minSup, newFreqSet, freqItemList)

def loadSimpDat():
    simpDat = [['r', 'z', 'h', 'j', 'p'],
               ['z', 'y', 'x', 'w', 'v', 'u', 't', 's'],
               ['z'],
               ['r', 'x', 'n', 'o', 's'],
               ['y', 'r', 'x', 'z', 'q', 't', 'p'],
               ['y', 'z', 'x', 'e', 'q', 's', 't', 'm']]
    return simpDat

def createInitSet(dataSet):
    retDict = {}
    for trans in dataSet:
        retDict[frozenset(trans)] = 1
    return retDict

'''
test
'''
'''
root = treeNode('test', 9, None)
root.child['eye'] = treeNode('eye', 3, None)
root.child['eye1'] = treeNode('eye1', 4, None)
root.disp()
'''

def read(filepath = ''):
    i = 0
    dataSet = []
    f = open(filepath, 'r')
    line = f.readline().rstrip()
    while line:
        #i = i + 1
        slist = line.split(' ')
        dataSet.append(slist)
        line = f.readline().rstrip()
    return dataSet

d = read('kosarak.dat')
print d[1:11]

minSup = 3
simpDat = loadSimpDat()
#initSet = createInitSet(d[1:1000])
initSet = createInitSet(simpDat)
myFPtree, myHeaderTab = createTree(initSet, minSup)
myFPtree.disp()
myFreqList = []
#print sorted(myHeaderTab.items(), key = lambda p:p[1])
#print myHeaderTab.items()[1][0]
mineTree(myFPtree, myHeaderTab, minSup, set([]), myFreqList)
print myFreqList[1:100]
