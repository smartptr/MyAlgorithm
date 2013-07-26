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
#include <queue>
using namespace std;

class Egalitarianism {
public:
  	int maxDifference(vector<string> isFriend, int d);
};

bool check(vector<string> vec)
{
    int n = vec.size();
    for(int k = 0; k < n; ++k)
    {
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(i!=j&&i!=k&&j!=k)
                {
                    if(vec[i][k] == 'Y' && vec[k][j] == 'Y')
                        vec[i][j] = 'Y';
                }
            }
        }
    }
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(i != j && vec[i][j] != 'Y')
                return false;
        }
    }
    return true;
}

int dp[55][55];

int bfs(int s, int n)
{
    bool visited[55];
    memset(visited, false, sizeof(visited));
    queue<int> q;
    q.push(s);
    visited[s] = true;
    int d[55];
    memset(d, 0, sizeof(d));
    d[s] = 0;
    while(!q.empty())
    {
        int p = q.front();
        q.pop();
        for(int i = 0; i < n; ++i)
        {
            if(dp[p][i] == 1 && !visited[i])
            {
                if(d[p] + 1 > d[i])
                {
                    d[i] = d[p] + 1;
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
    int mmax = 0;
    for(int i = 0; i < n; ++i)
    {
        mmax = max(mmax, d[i]);
    }
    return mmax;
}

int Egalitarianism::maxDifference(vector<string> isFriend, int d)
{
    vector<string> tmp(isFriend.begin(), isFriend.end());
    if(!check(tmp))
    {
        return -1;
    }
    int n = isFriend.size();
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(isFriend[i][j] == 'Y')
                dp[i][j] = 1;
            else
                dp[i][j] = 0;
        }
    }
    int mmax = 0;
    for(int i = 0; i < n; ++i)
    {
        mmax = max(mmax,bfs(i,n));
    }
    return mmax*d;
}

int main()
{
    Egalitarianism e;
    vector<string> v;
    v.push_back("NYNYYYN");
    v.push_back("YNNYYYN");
    v.push_back("NNNNYNN");
    v.push_back("YYNNYYN");
    v.push_back("YYYYNNN");
    v.push_back("YYNYNNY");
    v.push_back("NNNNNYN");
    /*v.push_back("NNYNYY");
    v.push_back("NNNYNN");
    v.push_back("NNNYNN");*/
    int ans = e.maxDifference(v,10);
    cout << ans << endl;
}
