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

class TrafficCongestion {
public:
  	LL theMinCars(int h);
};


LL dp[1000005];
const LL MOD = (LL)1000000007;
LL TrafficCongestion::theMinCars(int h)
{
    dp[0] = 1;
    dp[1] = 1;
    for(int i = 2; i <= h; ++i)
    {
        dp[i] = (dp[i-1]%MOD + ((LL)2 * (dp[i-2]%MOD))%MOD)%MOD;
    }
    return dp[h]%MOD;
}


int main()
{
    TrafficCongestion t;
    LL ans = t.theMinCars(585858);
    cout << ans << endl;
}



