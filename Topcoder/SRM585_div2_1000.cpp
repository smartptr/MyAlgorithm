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
#include <iterator>
using namespace std;

typedef long long LL;
const int MAX = 1205;

class EnclosingTriangleColorful {
public:
  	int getNumber(int m, vector<int> x, vector<int> y);
};

struct point
{
    int x, y;
    point() {}
    point(int _x, int _y):x(_x), y(_y){}
    point(const point& _p):x(_p.x), y(_p.y){}
    point operator==(const point& p)
    {
        x = p.x;
        y = p.y;
        return *this;
    }
    void output()
    {
        cout << x << " " << y << endl;
    }
};

bool operator < (const point& p1, const point& p2)
{
    if(p1.x != p2.x) p1.x < p2.x;
    return p1.y <= p2.y;
}

bool operator == (const point& p1, const point& p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}
bool operator != (const point& p1, const point& p2)
{
    return !(p1 == p2);
}


int cross(const point& p1, const point& p2, const point p)
{
    return (p1.x-p.x)*(p2.y-p.y) - (p2.x-p.x)*(p1.y-p.y);
}

bool clockOrder(const point& p1, const point& p2, const point p)
{
    return cross(p1, p2, p) <= 0;
}

bool valid(const point& p1, const point& p2, vector<int> x, vector<int> y)
{
    bool val = true;
    for(int i = 0; i < x.size(); ++i)
        val &= clockOrder(p1, p2, point(x[i], y[i]));
    return val;
}

int nextSide[MAX];
bool ok[MAX][MAX];
point po[MAX];

int EnclosingTriangleColorful::getNumber(int m, vector<int> x, vector<int> y)
{
    int n = 0;
    for(int t = 0; t < 4; ++t)
    {
        for(int i = 1; i < m; ++i)
        {
            int ox[4] = {0, i, m, m-i};
            int oy[4] = {i, m, m-i, 0};
            po[n] = point(ox[t],oy[t]);
            nextSide[n++] = (t+1)*(m-1);
        }
    }
    memset(ok, false, sizeof(ok));
    for(int i = 0; i < n; ++i)
    {
        for(int j = nextSide[i]; j < n; ++j)
        {
            ok[i][j] = valid(po[i], po[j], x, y);
            ok[j][i] = valid(po[j], po[i], x, y);
        }
    }
    int ans = 0;
    for(int i = 0; i < n; ++i)
    {
        for(int j = nextSide[i]; j < n; ++j)
        {
            for(int k = nextSide[j]; k < n; ++k)
            {
                if(ok[i][j] && ok[j][k] && ok[k][i])
                    ++ans;
            }
        }
    }
    return ans;
}
