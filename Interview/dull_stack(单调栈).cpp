#include <iostream>
#include <string>
#include <stack>
#include <cmath>
using namespace std;

struct Node
{
    int h;
    int start;
    Node() {}
    Node(int _h, int _start): h(_h), start(_start) {}
};

const int maxn = 100005;
int n = 7;
int data[maxn] = {2, 1, 4, 5, 1, 3, 3};

int process()
{
    stack<Node> s;
    s.push(Node(-1, 0)); //标记
    int h;
    int max_area = 0;
    for(int i = 0; i <= n; ++i)
    {
        if(i == n)
            h = 0;
        else
            h = data[i];
        Node tmp(h, i);
        while(s.top().h > h)
        {
            tmp = s.top();
            s.pop();
            int area = (i - tmp.start) * tmp.h;
            max_area = std::max(area, max_area);
        }
        s.push(Node(h, tmp.start));
    }
    return max_area;
}
