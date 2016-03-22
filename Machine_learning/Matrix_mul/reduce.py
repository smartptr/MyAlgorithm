# -*- coding: utf-8 -*-

import sys

pre_key=None
Mij={}
Njk={}

for line in sys.stdin:
	line = line.strip('\n')
	key, value=line.split('\t')
	#print key
	if pre_key == key or pre_key == None:
		pre_key = key
		items=value.split('#')
		if items[0] == 'M':
			Mij[items[1]]=int(items[-1])
		else:
			Njk[items[1]]=int(items[-1])
	else:
		sum=0
		for k in Mij.keys():
			if Njk.has_key(k):
				sum += Mij[k] * Njk[k]
		print "%s\t%s" % (pre_key, str(sum))
		pre_key = key
		Mij={}
		Njk={}
		items=value.split('#')
		if items[0] == 'M':
			Mij[items[1]]=int(items[-1])
		else:
			Njk[items[1]]=int(items[-1])

if pre_key != None:
	sum = 0
	for key in Mij.keys():
		if Njk.has_key(key):
			sum += Mij[key] * Njk[key]
	print "%s\t%s" % (pre_key, str(sum))
