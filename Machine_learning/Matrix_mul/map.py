# -*- coding: utf-8 -*-

import sys

nrows=int(sys.argv[1]) #行
nclos=int(sys.argv[2]) #列

for line in sys.stdin:
	items=line.strip('\n').split('#')	
	key=items[0]
	if key == 'M':
		i,j,v=map(int, items[1:])
		for c in range(1,nclos+1):
			t_key=str(i)+"#"+str(c)
			t_v="M#"+str(j)+"#"+str(v)
			print "%s\t%s" % (t_key, t_v)
	else:
		j,k,v=map(int, items[1:])
		for r in range(1, nrows+1):
			t_key=str(r)+"#"+str(k)
			t_v="N#"+str(j)+"#"+str(v)
			print "%s\t%s" % (t_key, t_v)
