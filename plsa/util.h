#ifndef _UTIL_H_
#define _UTIL_H_

#include <assert.h>
#include <vector>
#include <time.h>
#include <cstdio>
#include <cmath>
using std::vector;

namespace CZG
{
	 typedef double real;
	 static vector<real> randomPro(int size)
	 {
		 assert(size >= 1);
		 vector<real> pros(size, 0);
		 real total = 0;
		 srand((unsigned int)time(NULL));
		 for(int i = 0; i < size; ++i)
		 {
			 pros[i] = (real)(rand() % size + 1);
			 total += pros[i];
		 }
		 for(int i = 0; i < size; ++i)
			pros[i] /= total;
		 return pros;
	 }

	 const real eps = 1e-8;
	 inline bool isZero(real num)
	 {
		  if(fabs(num) < eps)	
			  return true;
		  return false;
	 }
	 const real EPS = 1e-6;
}
#endif
