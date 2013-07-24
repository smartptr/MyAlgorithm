/*
n层楼，m个鸡蛋，鸡蛋在某一楼层楼下会碎也可能不碎，所有鸡蛋硬度一样，问鸡蛋可以安全下落的最大高度。
类似的，2个鸡蛋的问题：
状态转移方程：f[n] = min{ 1+max(i-1,f[n-i]) | i=1..n }
初始条件: f[0]=0（或f[1]=1）
2个鸡蛋的时候可以求数学问题：
假设完成k次得到结果，第一次从k层扔，如果第一次鸡蛋碎，那么剩下k-1次机会，从第一层开始有k-1次机会，如果没碎，那么还剩下k-1次机会，
可以从k+（k-1）层计算，那么问题变成了k次可以到达的最高楼层，那么有k+（k-1）+（k-2）+。。。+1=k(k+1)/2>=n;求出最小k即可
如果3个鸡蛋，由上面结论，k-1次机会最多可以测试k(k-1)/2层楼，所以第一次在k(k-1)/2+1层楼，第一次如果第一枚鸡蛋不
碎，第二次在此基础上增加(k-1)(k-2)/2+1层楼，于是，三个鸡蛋k次机会总共测试楼层数
为{k(k-1)/2+1}+{(k-1)(k-2)/2+1}+...+{2*1/2+1}+{1*0/2+1}=(k^3+5k)/6；如果四个五个一次类推。
m个鸡蛋，状态转移方程：f[n,m] = min{ 1+max(f[i-1,m-1], f[n-i,m]) | i＝1..n }
初始条件：f[i,0]=0（或f[i,1]=i），对所有i
*/
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const int maxn = 1005;
const int maxm = 55;

int dp[maxn][maxm];

void init()
{
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= 1000; ++i)
        dp[i][1] = i;
    for(int i = 1; i <= 50; ++i)
        dp[1][i] = 1;
    for(int i = 2; i <= 1000; ++i)
    {
        for(int j = 1; j < i; ++j)
        {
            for(int k = 2; k <= 50; ++k)
            {
                if(dp[i][k] == 0)
                    dp[i][k] = 1 + max(dp[i-1][k-1], dp[i-j][k]);
                else
                    dp[i][k] = min(dp[i][k], 1 + max(dp[j-1][k-1], dp[i-j][k]));
            }
        }
    }
}

int main()
{
    init();
    int times;
    cin >> times;
    while(times--)
    {
        int t,n,m;
        cin >> t >> m >> n;
        cout << t << " " << dp[n][m] << endl;
    }
    return 0;
}
