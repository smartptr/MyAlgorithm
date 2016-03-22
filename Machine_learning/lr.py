# -*- coding: utf-8 -*-
'''
author: cuizhigang
date: 20140905
function: 实现logistic regression
'''
import sys
import math
import random

#载入数据文件
#按照训练集和测试集7:3划分
def load_data(data_file=''):
	train_data=[]
	train_labels=[]
	test_data=[]
	test_label=[]
	for line in open(data_file):
		items=line.strip().split('\t')
		nlen=len(items)
		attr_list=map(float, items[0:nlen-1])
		attr_list.append(1) #(w1,w2,...wn,b), (x1,x2,...xn,1)
		label = int(items[-1])
		r_ind=random.randint(1,100000)
		if r_ind%10==4 or r_ind%10==7 or r_ind%10==9: #测试集
			test_data.append(attr_list)
			test_label.append(label)
		else: #训练集
			train_data.append(attr_list)
			train_labels.append(label)
	return train_data, train_labels, test_data, test_label

# sigmod函数
def sigmod(weight):
	#print weight
	if weight<=-700:
		return 0.0
	return 1.0/(1.0+math.exp(-1.0*float(weight)))

# 计算内积
def inner_cross(list1, list2):
	return sum([list1[i]*list2[i] for i in range(len(list1))])

#训练模型
def trainModel(data=[], labels=[], max_epoch=100, alpha=0.001):
	instance_num=len(data) #样本数
	attribute_num=len(data[0]) #属性个数
	#print data[0], attribute_num
	betaVector=[0 for i in range(attribute_num)] #权重向量
	for iter in range(max_epoch): #迭代次数
		gradiet=[0 for k in range(attribute_num)] #梯度
		for i in range(instance_num):
			z=inner_cross(betaVector, data[i])
			sig=sigmod(z)
			for att in range(attribute_num):
				gradiet[att]+=data[i][att]*(labels[i]-sig) #更新梯度
		for i in range(attribute_num):
			betaVector[i]+=alpha*gradiet[i] #更新权重信息
	return betaVector
	
#测试模型
def testModel(data=[], labels=[], betaVector=[]):
	predict_value=[]
	for ins in data:
		prob=sigmod(inner_cross(ins, betaVector))
		predict_value.append(prob)
	correct_label=0
	total_label=len(predict_value)
	for i in range(total_label):
		p=predict_value[i]
		if p >= 0.5:
			p_label=1
		else:
			p_label=0
		if p_label == labels[i]:
			correct_label+=1
	precision=0.0
	if total_label != 0:
		precision=float(correct_label)/total_label*100
	#precision='%.2f%%' % (precision)
	return precision

#调参模块
def auto_change_argument(train_data=[], train_label=[], test_data=[], test_label=[]):
	max_iter=100
	max_alpha=0.01
	max_precision=0
	for iter in range(100,1001,100):
		for alpha in range(1, 10, 1):
			alpha=float(alpha/1000.0)
			betaVector=trainModel(train_data, train_label, iter, alpha)
			precision=testModel(test_data, test_label, betaVector)
			if max_precision<precision:
				max_precision=precision
				max_iter=iter
				max_alpha=alpha
	return max_iter, max_alpha, max_precision
			

if __name__ == '__main__':
	train_data, train_label, test_data, test_label=load_data(sys.argv[1])
	if len(sys.argv)>=3 and sys.argv[2] == 'C': #自适应调参数
		max_iter, max_alpha, max_precision=auto_change_argument(train_data, train_label, test_data, test_label)
		print "最优参数值：max_iter=", max_iter
		print "优参数值：max_alpha=", max_alpha
		print "模型准确度: precision=%.2f%%" % (max_precision)
	else:
		if len(sys.argv)>=3 and sys.argv[2]=='-I': #迭代次数
			if len(sys.argv)<4:
				print '参数错误!'
				sys.exit(-1)
			iter=int(sys.argv[3])
		else:
			print '参数错误!'
			sys.exit(-1)
		if len(sys.argv)>=5 and sys.argv[4]=='-A': #步长
			if len(sys.argv)<6:
				print '参数错误!'
				sys.exit(-1)
			alpha=float(sys.argv[5])
		else:
			print '参数错误!'
			sys.exit(-1)
		betaVector=trainModel(train_data, train_label, iter, alpha)
		precision=testModel(test_data, test_label, betaVector)
		print "模型准确度: precision=%.2f%%" % (precision)
