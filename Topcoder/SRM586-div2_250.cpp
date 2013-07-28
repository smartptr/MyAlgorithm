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

class TeamsSelection {
public:
  	string simulate(vector <int> p1, vector <int> p2);
};

string TeamsSelection::simulate(vector <int> p1, vector <int> p2)
{
    int n = p1.size();
    int t = 1;
    int f[55];
    memset(f, 0, sizeof(f));
    while(t<=n)
    {
        if(t%2==1)
        {
            for(int i = 0; i < n; ++i)
            {
                if(f[p1[i]] == 0 )
                {
                    f[p1[i]] = 1;
                    break;
                }
            }
        }else
        {
            for(int i = 0; i < n; ++i)
            {
                if(f[p2[i]] == 0 )
                {
                    f[p2[i]] = 2;
                    break;
                }
            }
        }
        ++t;
    }
    string s= "";
    for(int i = 1; i <= n; ++i)
    {
        if(f[i] != 0)
            s += (f[i] + '0');
    }
    return s;
}
