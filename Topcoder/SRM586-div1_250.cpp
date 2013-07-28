#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory.h>
using namespace std;

class PiecewiseLinearFunction {
public:
  	int maximumSolutions(vector <int> Y);
};


bool check(int l, int r, double p)
{
    if(p >= l && p <= r)
        return true;
    else if(p >= r && p <= l)
        return true;
    return false;
}

int PiecewiseLinearFunction::maximumSolutions(vector <int> Y)
{
    int f[100];
    int n = Y.size();
    for(int i = 0; i < n; ++i)
    {
        f[i+1] = Y[i];
    }
    for(int i = 1; i < n; ++i)
    {
        if(f[i] == f[i+1])
            return -1;
    }
    vector<double> query;
    for(int i = 1; i <= n; ++i)
    {
        query.push_back(f[i]);
    }
    for(int i = 1; i <= n; ++i)
    {
        for(int j = i; j <= n; ++j)
        {
            query.push_back((f[i]+f[j])/2.0);
        }
    }
    int m = query.size();
    int res = 0;
    double tt=0;
    for(int i = 0; i < m; ++i)
    {
        bool flag = false; 
        int ans = 0;
        for(int j = 1; j < n; ++j)
        {
            int l = f[j];
            int r = f[j+1];
            if(!check(l, r, query[i]))
                continue;
            int k = r - l;
            if(k == 0)
            {
                flag = true;
                break;
            }
            else if(query[i] != l && query[i] != r)
                ++ans;
        }
        for(int j = 1; j <= n; ++j)
        {
            if(query[i] == (double)f[j])
                ++ans;
        }
        if(!flag)
        {
            res = max(res, ans);
        }
    }
    return res;
}
