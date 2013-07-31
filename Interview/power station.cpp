//tree dp
//num[i]表示以i为根的所有子树的节点个数
//dp[i]表示的是以i为根的子树中i到所有子节点的距离
//dfs1表示随机找一个根
//dfs2表示如果选取dfs1中找的根的孩子作为跟那么dp对应的值
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <iterator>
#include <queue>
using namespace std;

typedef long long LL;

const int maxn = 50005;

LL num[maxn];
LL dp[maxn];
bool visit[maxn];
vector<int> edge[maxn];
int n, I, R;

void dfs1(int root)
{
    num[root] = 1;
    dp[root] = 0;
    visit[root] = 1;
    for(int i = 0; i < edge[root].size(); ++i)
    {
        int p = edge[root][i];
        if(!visit[p])
        {
            dfs1(p);
            num[root] += num[p];
            dp[root] += dp[p] + num[p];
        }
    }
}

void dfs2(int root)
{
    visit[root] = true;;
    for(int i = 0; i < edge[root].size(); ++i)
    {
        int p = edge[root][i];
        if(!visit[p])
        {
            dp[p] = dp[root] - (LL)2 * num[p] + n;
            dfs2(p);
        }
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    bool flag = false;
    while(t--)
    {
        if(flag)
        {
            printf("\n");
        }
        scanf("%d%d%d", &n,&I,&R);
        for(int i = 0; i < n; ++i)
            edge[i].clear();
        for(int i = 0; i < n - 1; ++i)
        {
            int a, b;
            scanf("%d%d", &a,&b);
            --a; --b;
            edge[a].push_back(b);
            edge[b].push_back(a);
        }
        memset(num, 0, sizeof(num));
        memset(dp, 0, sizeof(dp));
        memset(visit, 0, sizeof(visit));
        dfs1(0);
        memset(visit, 0, sizeof(visit));
        dfs2(0);
        LL maxdis = (LL)(1<<24) * (LL)(1<<24);
        vector<int> ans;
        for(int i = 0; i < n; ++i)
        {
            if(dp[i] < maxdis)
            {
                maxdis = dp[i];
                ans.clear();
                ans.push_back(i+1);
            }else if(dp[i] == maxdis)
            {
                ans.push_back(i+1);
            }
        }
        maxdis = maxdis * (LL)I * (LL)I * (LL)R;
        //cout << maxdis << endl;
        printf("%lld\n", maxdis);
        for(int i = 0; i < ans.size(); ++i)
        {
            if(i == 0)
                printf("%d", ans[i]);
            else
                printf(" %d", ans[i]);
        }
        printf("\n");
        flag = true;
    }
    return 0;
}
