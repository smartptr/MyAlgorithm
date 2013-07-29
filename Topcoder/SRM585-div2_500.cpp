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

typedef long long LL;

class TrafficCongestionDivTwo {
public:
  	LL theMinCars(int h);
};


LL dp[66];

LL TrafficCongestionDivTwo::theMinCars(int h)
{
    dp[0] = 1;
    dp[1] = 1;
    for(int i = 2; i <= h; ++i)
    {
        dp[i] = dp[i-1] + (LL)2 * dp[i-2];
    }
    return dp[h];
}


int main()
{
    TrafficCongestionDivTwo t;
    LL ans = t.theMinCars(60);
    cout << ans << endl;
}


