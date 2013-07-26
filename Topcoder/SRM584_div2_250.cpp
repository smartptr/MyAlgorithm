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

class Egalitarianism {
public:
  	int maxDifference(string s, string t);
};

int Egalitarianism::maxDifference(string s, string t)
{
    set<string> se;
    for(int i = 0; i < s.length(); ++i)
    {
        for(int j = 0; j < t.length(); ++j)
        {
            string ss = s.substr(0,i+1) + t.substr(0, j+1);
            se.insert(ss);
        }
    }
    return se.size();
}

int main()
{
    Egalitarianism e;
    string s = "ababababab";
    string t = "bababababa";
    int ans = e.maxDifference(s, t);
    cout << ans << endl;
}
