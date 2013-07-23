/*
在柱状图中找最大的矩形：给一组非负的整数来表示一个柱状图，设计一个算法找到最大面积的能适合到
柱状图内的矩形。比如，对与这组数，1 2 3 4 1，有两种可能的方案，一种是适合到 2 3 4 内的矩
形，面积是 2*3；另一种是适合到 3 4 内的矩形，面积是 3*2
*/
//算法实现o(n),基于单调栈思想
#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

typedef long long LL;

const int maxn = 100005;

LL data[maxn+1];

LL Max(LL a, LL b)
{
    return  a > b ? a : b;
}

int l[maxn];
int r[maxn];

LL process(int n)
{
    LL mmax = -1;
    stack<int> s;
    for(int i = 1; i <= n; ++i)
    {
        if(s.empty())
            s.push(i);
        else
        {
            int p = s.top();
            int index = p;
            while(data[p] > data[i])
            {
                s.pop();
                r[p] = index;
                if(s.empty())
                    break;
                p = s.top();
            }
            s.push(i);
        }
    }
    int index,p;
    if(!s.empty())
    {
        index = s.top();
        p = index;
    }
    while(!s.empty())
    {
        r[p] = index;
        s.pop();
        if(s.empty())
            break;
        p = s.top();
    }
    for(int i = n; i >= 1; --i)
    {
        if(s.empty())
            s.push(i);
        else
        {
            int p = s.top();
            int index = p;
            while(data[p] > data[i])
            {
                s.pop();
                l[p] = index;
                if(s.empty())
                    break;
                p = s.top();
            }
            s.push(i);
        }
    }
    if(!s.empty())
    {
        index = s.top();
        p = index;
    }
    while(!s.empty())
    {
        l[p] = index;
        s.pop();
        if(s.empty())
            break;
        p = s.top();
    }
    for(int i = 1; i <= n; ++i)
    {
        mmax = Max(mmax, data[i] * (LL)(r[i]-l[i]+1));
    }
    return mmax;
}

int main()
{
    int n;
    while(scanf("%d",&n))
    {
        if(n == 0)
            break;
        for (int i = 1; i <= n; ++i)
        {
            //cin >> data[i];
            scanf("%lld",&data[i]);
        }
        LL ans = process(n);
        //cout << ans << endl;
        printf("%lld\n", ans);
    }
    return 0;
}

