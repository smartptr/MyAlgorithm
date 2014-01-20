# -*- coding: utf-8 -*-
# author: czg1989
# time: 2014-01-20

import numpy as np
import matplotlib
import matplotlib.pyplot as plt

def loadDataSet(filename, delim = '\t'):
    f = open(filename)
    stringArr = [line.strip().split(delim) for line in f.readlines()]
    dataArr = [map(float, line) for line in stringArr]
    return np.mat(dataArr)

def replaceNanWithMean(): 
    datMat = loadDataSet('secom.data', ' ')
    numFeat = np.shape(datMat)[1]
    for i in range(numFeat):
        meanVal = np.mean(datMat[np.nonzero(~np.isnan(datMat[:,i].A))[0],i]) #values that are not NaN (a number)
        datMat[np.nonzero(np.isnan(datMat[:,i].A))[0],i] = meanVal  #set NaN values to mean
    return datMat

def pca(dataMat, topNfeature=1000):
    """ arguments description.
    Args:
        dataMat: data to do pca
        topNfeature: the new dimensionality we want to reduce to.
    """
    meanVec = np.mean(dataMat, axis=0)
    centerVecs = dataMat - meanVec
    covMat = np.cov(centerVecs, rowvar=0)
    print 'Calculating eigenvectors and eigenvalues'
    eValues, eVectors = np.linalg.eigh(np.mat(covMat))
    print "eValues: "
    print eValues
    print "eVectors: "
    print eVectors
    idx = np.argsort(eValues)
    idx = idx[:-(topNfeature+1):-1]
    newValues = eValues[idx]
    mynewVectors = eVectors[:,idx]
    lowDataMat = centerVecs * mynewVectors
    reconMat = (lowDataMat * mynewVectors.T) + centerVecs
    return lowDataMat, reconMat, newValues, mynewVectors

dataMat = loadDataSet('testSet.txt')
#dataMat = replaceNanWithMean()
lowDMat, reconMat, eValues, eVectors = pca(dataMat, 1)

print dataMat.shape
print lowDMat.shape
print reconMat.shape
print "newValues:"
print eValues
print "newVectors:"
print eVectors

#display
fig = plt.figure()
ax = fig.add_subplot(111)
ax.scatter(dataMat[:,0], dataMat[:,1], marker='^', s=90)
ax.scatter(reconMat[:,0], reconMat[:,1], marker='o', s=50, c='red')
plt.show()



