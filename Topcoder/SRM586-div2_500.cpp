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

class PiecewiseLinearFunctionDiv2 {
public:
  	vector <int> countSolutions(vector <int> Y, vector <int> query);
};


bool check(int l, int r, int p)
{
    if(p >= l && p <= r)
        return true;
    else if(p >= r && p <= l)
        return true;
    return false;
}

vector <int>  PiecewiseLinearFunctionDiv2::countSolutions(vector <int> Y, vector <int> query)
{
    int f[100];
    int n = Y.size();
    for(int i = 0; i < n; ++i)
    {
        f[i+1] = Y[i];
    }
    int m = query.size();
    vector<int> res;
    for(int i = 0; i < m; ++i)
    {
        bool flag = false; // 无穷多个
        double ans = 0;
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
            if(query[i] == f[j])
                ++ans;
        }
        if(flag)
            res.push_back(-1);
        else
            res.push_back(ans);
    }
    return res;
}
