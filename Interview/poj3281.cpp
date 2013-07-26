#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include <vector>
#include <iterator>
using namespace std;

const int maxn = 40005;
const int maxm = 600;
const int max_value = 10000000;


struct Edge
{
    int from;
    int to;
    int flow;
    int next;
    int op;
}edge[maxn];

int pre[maxm];
int flow[maxm];
int head[maxm];
int tot;

void init()
{
    tot = -1;
    memset(head, -1, sizeof(head));
}

void addEdge(int from, int to, int flow)
{
    edge[++tot].from = from;
    edge[tot].to = to;
    edge[tot].flow = flow;
    edge[tot].next = head[from];
    edge[tot].op = tot + 1;
    head[from] = tot;

    edge[++tot].from = to;
    edge[tot].to = from;
    edge[tot].flow = 0;
    edge[tot].next = head[to];
    edge[tot].op = tot - 1;
    head[to] = tot;
}

int bfs(int s, int t)
{
    queue<int> q;
    memset(pre, -1, sizeof(pre));
    q.push(s);
    flow[s] = INT_MAX;
    while(!q.empty())
    {
        int p = q.front();
        q.pop();
        if(p == t)
            break;
        for(int h = head[p]; h != -1; h = edge[h].next)
        {
            int to = edge[h].to;
            if(to != s && pre[to] == -1 && edge[h].flow > 0)
            {
                pre[to] = h;
                flow[to] = min(flow[p], edge[h].flow);
                q.push(to);
            }
        }
    }
    if(pre[t] == -1)
        return -1;
    return flow[t];
}

int EK(int s, int t)
{
    int maxFlow = 0;
    while(true)
    {
        int inc = bfs(s,t);
        //cout << inc << endl;
        if(inc == -1)
            break;
        int k = t;
        while(pre[k] != -1)
        {
            int p = pre[k];
            edge[p].flow -= inc;
            edge[edge[p].op].flow += inc;
            k = edge[p].from;
        }
        maxFlow += inc;
    }
    return maxFlow;
}


int main()
{
    int n,f,d;
    while(cin >> n >> f >> d)
    {
        init();
        int s = 0;
        int t = 2*n + f + d + 1;
        //拆点,人-人，保证food和drink不会被重复选择
        for(int i = 1; i <= n; ++i)
        {
            addEdge(i, i+n, 1);
        }
        //源点到food
        for(int i = 1; i <= f; ++i)
        {
            addEdge(s, 2*n+i, 1);
        }
        //drink到汇点
        for(int i=1; i <= d; ++i)
        {
            addEdge(2*n+f+i, t, 1);
        }
        for(int i = 1; i <= n; ++i)
        {
            int n1, f1, u;
            cin >> n1 >> f1;
            for(int j = 1; j <= n1; ++j)
            {
                cin >> u;
                addEdge(2*n+u, i, 1);
            }
            for(int j = 1; j <= f1; ++j)
            {
                cin >> u;
                addEdge(i+n, 2*n+f+u, 1);
            }
      }
        int ans = EK(s, t);
        cout << ans << endl;
    }
    return 0;
}
