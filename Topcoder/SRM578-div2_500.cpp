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

const int mod = 1000000007;

class GooseInZooDivTwo {
public:
  	int count(vector <string> field, int dist);
};

bool visit[55][55];

void dfs(vector <string> f, int x, int y, int n, int m, int s)
{
    visit[x][y] = 1;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            int d = abs(x-i) + abs(y-j);
            if(!visit[i][j] && f[i][j] == 'v' && d <= s )
                dfs(f,i,j,n,m,s);
        }
    }
}

int GooseInZooDivTwo::count(vector <string> field, int dist)
{
    int n = field.size();
    int m = field[0].length();
    int num = 0;
    memset(visit, 0, sizeof(visit));
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            if(field[i][j] == 'v' && !visit[i][j])
            {
                dfs(field, i, j, n, m, dist);
                ++num;
            }
        }
    }
    int ans = 1;
    while(num)
    {
        ans = (2 * ans)%mod;
        --num;
    }
    return ans - 1;
}
