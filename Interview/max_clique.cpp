/*
 * function: max-clique problem
 * author: John
 * 下标从1开始
*/

#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

const int maxn =101;

bool graph[maxn][maxn];
bool used[maxn];
int cn, bestcn;
int V,E;

void max_clique(int id)
{
    if(id == V+1)
    {
        bestcn = cn;
        cout << cn << endl;
        for (int i = 1; i <= V; ++i)
        {
            if(used[i])
                cout << i << " ";
        }
        cout << endl;
    }
    bool flag = true;
    for(int i=1; i < id; ++i)
    {
        if(used[i]&&!graph[id][i])
        {
            flag = false;
            break;
        }
    }
    if(flag)
    {
        ++cn;
        used[id] = true;
        max_clique(id+1);
        --cn;
    }
    //剪枝操作
    if(cn+V-id > bestcn)
    {
        used[id] = false;
        max_clique(id+1);
    }
}


int main()
{
    int test;
    cin >> test;
    while(test--)
    {
        memset(graph, false, sizeof(graph));
        memset(used, false, sizeof(used));
        bestcn = 0;
        cn = 0;
        cin >> V >> E;
        int u, v;
        for (int i = 0; i < E; ++i)
        {
            cin >> u >> v;
            graph[u][v] = true;
            graph[v][u] = true;
        }
        max_clique(1);
    }
    return 0;
}

/*
1
5 7
1 2
1 4
1 5
2 3
2 5
3 5
4 5
*/
