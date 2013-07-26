//max flow算法, EK算法
#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;


const int MAX_NUM = 401;

struct Edge
{
    int from;
    int to;
    int flow; //容量
    int next;
    int op; //对应反向弧的位置
};

Edge edge[MAX_NUM];
int pre[MAX_NUM];
int flow[MAX_NUM];
int head[MAX_NUM];
int tot;
int Edge_Num, Vertex_Num;

void addEdge(int u, int v, int c)
{
    //正向弧
    edge[++tot].from = u;
    edge[tot].to = v;
    edge[tot].flow = c;
    edge[tot].next = head[u];
    edge[tot].op = tot+1;
    head[u] = tot;

    //反向弧
    edge[++tot].from = v;
    edge[tot].to = u;
    edge[tot].flow = 0;
    edge[tot].next = head[v];
    edge[tot].op = tot-1;
    head[v] = tot;
}

int bfs(int s, int t)
{
    queue<int> q;
    flow[s] = INT_MAX;
    memset(pre, -1, sizeof(pre));
    q.push(s);
    while(!q.empty())
    {
        int p = q.front();
        q.pop();
        if (p == t)
            break;
        for(int h = head[p]; h != -1; h = edge[h].next)
        {
            int to = edge[h].to;
            if(to != s && pre[to] == -1 && edge[h].flow > 0)
            {
                pre[to] = h;
                flow[to] = min(flow[p],edge[h].flow);
                q.push(to);
            }
        }
    }
    if(pre[t] == -1)
        return -1;
    return flow[t];
}

int EK(int s, int t) // 源s， 汇t
{
    int maxFlow = 0;
    while(true)
    {
        int inc = bfs(s, t);
        if(inc == -1)
        {
            break;
        }
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

void init()
{
    tot = -1;
    memset(head, -1, sizeof(head));
}

int main()
{
  while( scanf("%d%d", &Edge_Num, &Vertex_Num) != EOF )
	{
		int s,t,w;
		init();
		for ( int i = 0; i < Edge_Num; ++i )
		{
			scanf("%d%d%d", &s, &t, &w);
			//注意在网络流中如果存在重边，要将所有流量相加求得边的容量;
			//可以想象多条水管运输水的量肯定是累加的;
			//Capacity[s-1][t-1] += w;
			addEdge(s-1, t-1, w);
		}
		int ans = EK(0, Vertex_Num-1);
		printf("%d\n", ans);
	}
	return 0;
}

