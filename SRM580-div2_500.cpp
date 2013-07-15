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

using namespace std;

class EelAndRabbit {
public:
  	int getmax(vector<int> s, vector<int> t);
};

int EelAndRabbit::getmax(vector<int> s, vector<int> t)
{
    int n = s.size();
    for(int i = 0; i < n; ++i)
        t[i] = -t[i];
    int mmax = -100000;
    for(int i = 0; i < n; ++i)
    {
        int ans = 0;
        int m = -t[i];
        vector<int> s1;
        vector<int> t1;
        //cout <<m << endl;
        for(int j = 0; j < n; ++j)
        {
            int p = m + t[j];
            //cout << "p="<<p << endl;
            if(p - s[j] <= 0 && p >= 0)
            {
                ++ans;
            }
            else{
                if(p-s[j] > 0 )
                    continue;
                s1.push_back(s[j]);
                t1.push_back(p);
            }
        }
        //cout << "ans=" << ans << endl;
        int ll = s1.size();
        for(int id = 0; id < ll; ++id)
        {
            if(t1[id] > 0 )
                continue;
            int ans1 = 0;
            int ml = -t1[id];
            for(int k = 0; k < ll; ++k)
            {
                int pl = ml + t1[k];
                if(pl - s1[k] <= 0 && pl >= 0)
                {
                    ++ans1;
                }
            }
            //cout << ans << " " << ans1 << " " << ans + ans1 << endl;
            mmax = max(mmax, ans + ans1);
        }
        if(ll == 0)
        {
            mmax = max(mmax, ans);
        }
        //mmax = max(mmax, ans);
    }
    return mmax;
}
