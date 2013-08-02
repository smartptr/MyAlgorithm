//二维单调栈的应用，求最大的全部是1的矩阵，根据行累加看成一维单调栈处理
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <memory.h>
#include <stack>
using namespace std;

struct Node
{
    int h;
    int start;
    Node() {}
    Node(int _h, int _s): h(_h), start(_s) {}
};

const int maxn = 2005;
int mat[maxn][maxn];
int m, n; //m*n

int process(int row)
{
    stack<Node> s;
    s.push(Node(-1, 0));
    int h;
    int max_area = 0;
    for(int i = 0; i <= n; ++i) //列
    {
        if(i == n)
            h = 0;
        else
            h = mat[row][i];
        Node tmp(h, i);
        while(s.top().h > h)
        {
            tmp = s.top();
            s.pop();
            int area = (i - tmp.start) * tmp.h;
            //cout << i << "  "  << " " << tmp.start << "  " << tmp.h << endl;
            max_area = std::max(max_area, area);
        }
        s.push(Node(h, tmp.start));
    }
    return max_area;
}

int main()
{
    while(scanf("%d%d", &m, &n)!=EOF)
    {
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                scanf("%d", &mat[i][j]);
        for(int j = 0; j < n; ++j)
        {
            for(int i = 1; i < m; ++i)
            {
                if(0 != mat[i][j])
                    mat[i][j] += mat[i-1][j];
            }
        }
        int max_area = 0;
        for(int i = 0; i < m; ++i)
        {
            max_area = std::max(max_area, process(i));
        }
        printf("%d\n", max_area);
    }
    return 0;
}

