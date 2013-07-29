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

class LISNumberDivTwo {
public:
  	int calculate(vector <int> p);
};

int LISNumberDivTwo::calculate(vector <int> p)
{
    int n = p.size();
    int cnt = 0;
    int i = 0;
    while(i<n)
    {
        if(i == n - 1)
        {
            ++cnt;
            break;
        }
        else
        {
            if(p[i] >= p[i+1])
            {
                ++cnt;
            }
            ++i;
        }
    }
    return cnt;
}

int main()
{
    LISNumberDivTwo lis;
    int a[] = {42};
    vector<int> p(a, a+1);
    int ans = lis.calculate(p);
    cout << ans << endl;
}
