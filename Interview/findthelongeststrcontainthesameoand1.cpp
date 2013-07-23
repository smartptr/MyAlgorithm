/*
 给定一个数组，数组中只包含0和1。请找到一个最长的子序列，其中0和1的数量是相同的。
例1：10101010 结果就是其本身。
例2：1101000 结果是110100
*/

/*
思路：
可以动态规划，dp[i]表示0-i之间有多少个1，那么(dp[i]-dp[i])*2 = i-j+1(i>j)，求最大的即可,O(n^2)
但是可以优化，如果0变成-1，那么就是dp[i]==0或者dp[i] == dp[j]的间距，那么只需记录区间最大最小，
map存储到当前位置和为sum,区间最小值为min，最大值为max即可，最后遍历求所有区间最大值。O(n)
*/

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <iterator>
using namespace std;

const int maxn = 1000000;

struct node
{
    int mmin;
    int mmax;
    node(int _min = maxn, int _max = -1)
        : mmin(_min), mmax(_max){}
};

map<int, node> mp;

int main()
{
    string str;
    while(cin>>str)
    {
        int n = str.size();
        int sum = 0;
        mp.clear();
        for(int i = 0; i < n; ++i)
        {
            sum += ((str[i] == '0') ? -1 : 1);
            if(sum == 0)
            {
                mp[sum].mmin = 0;
                mp[sum].mmax = i;
                continue;
            }
            mp[sum].mmin = min(mp[sum].mmin, i);
            mp[sum].mmax = max(mp[sum].mmax, i);
        }
        int mmax = 0;
        for(map<int ,node>::iterator it = mp.begin(); it != mp.end(); ++it)
        {
            mmax = max(mmax,it->second.mmax - it->second.mmin+1);
        }
        cout << mmax << endl;
    }
    return 0;
}
