//优先队列优化的Dijkstra算法
//枚举吃饭的点
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <iterator>
#include <queue>
using namespace std;
typedef long long LL;

const int maxn = 1005;
const int maxm = 20005;
struct Graph
{
    int v;
    int c;
    Graph() {}
    Graph(int _v, int _c): v(_v), c(_c){}
};

struct Node
{
    int v;
    LL dis;
};

struct cmp
{
    bool operator()(const Node& p, const Node& q)
    {
        return p.dis > q.dis;
    }
};

priority_queue<Node, vector<Node>, cmp> Q;
vector<Graph> g[maxn];
int n, m;
int cost[maxn];
LL d[maxn];
LL qer[maxm];
int s[maxm],t[maxm];

void dij(int s)
{
    while(!Q.empty())
    {
        Q.pop();
    }
    memset(d, -1, sizeof(d));
    Node node;
    node.v = s;
    node.dis = 0;
    d[s] = 0;
    Q.push(node);
    while(!Q.empty())
    {
        Node no = Q.top();
        Q.pop();
        int id = no.v;
        for(int i = 0; i < g[id].size(); ++i)
        {
            int to = g[id][i].v;
            int c = g[id][i].c;
            if(cost[to] <= cost[s] && (d[to] == -1 || d[to] > c + no.dis))
            {
                d[to] = (LL)c + no.dis;
                Node v;
                v.v = to;
                v.dis = d[to];
                Q.push(v);
            }
        }
    }
}

const LL inf = (LL)(1<<24) * (LL)(1<<24);

int main()
{
    bool f = false;
    while(scanf("%d%d", &n,&m)!=EOF)
    {
        if(n==0&&m==0)
            break;
        if(f)
            printf("\n");
        for(int i = 0; i < n; ++i)
            g[i].clear();
        for(int i = 0; i < n; ++i)
            scanf("%d", &cost[i]);
        for(int i = 0; i < m; ++i)
        {
            int x, y,z;
            scanf("%d%d%d", &x, &y, &z);
            --x; --y;
            g[x].push_back(Graph(y,z));
            g[y].push_back(Graph(x,z));
        }
        int q;
        scanf("%d", &q);
        for(int i = 0; i < q; ++i)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            --x; --y;
            s[i] = x;
            t[i] = y;
        }
        memset(qer,-1,sizeof(qer));
        for(int i = 0; i < n; ++i)
        {
            dij(i);
            for(int j = 0; j < q; ++j)
            {
                if(d[s[j]]!=-1&&d[t[j]]!=-1)
                {
                    if(qer[j] == -1)
                        qer[j] = d[s[j]]+d[t[j]]+cost[i];
                    else
                        qer[j] = min(qer[j], d[s[j]]+d[t[j]]+cost[i]);
                }
            }
        }
        for(int i = 0; i < q; ++i)
            printf("%I64d\n", qer[i]);
        f = true;
    }
    return 0;
}

