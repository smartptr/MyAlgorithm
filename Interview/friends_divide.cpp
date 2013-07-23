/*
题目：
大家都知道facebook用户都是双向的好友，a是b的好友，那么b一定是a的好友，现在给定一个用户列表
，其中有些用户是好友，有些不是，请判断，这些用户是否可以划分为两组，并且每组内的用户，
互相都不是好友。如果能，请给出这个划分。
例子1： 用户：{1, 2, 3} 好友关系：1-2， 2-3 划分：{1,3} {2}
例子2： 用户{1,2,3,4} 好友关系：1-2， 2-3， 3-4，4-1 划分：{1, 3}{2, 4}
*/
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <queue>
#include <ostream>
using namespace std;


const int maxn = 1000;

vector< int > vec[maxn];
bool visit[maxn];
int color[maxn];

bool bfs(int s)
{
    queue<int> q;
    visit[s] = 1;
    q.push(s);
    while(!q.empty())
    {
        int p = q.front();
        q.pop();
        for(int i = 0; i < vec[p].size(); ++i)
        {
            int t = vec[p][i];
            if(!visit[t])
            {
                if(color[p] == 1)
                    color[t] = 2;
                else if(color[p] == 2)
                    color[t] = 1;
                q.push(t);
                visit[t] = 1;
            }
            else if(visit[t] && color[t] == color[p])
                return false;
        }
    }
    return true;
}

int main()
{
    int n;//n个人
    while(cin>>n)
    {
        for (int i = 0; i < n; ++i)
            vec[i].clear();
        int m; // m组关系
        cin >> m;
        for (int i = 0; i < m; ++i)
        {
            int p,q;
            cin >> p >> q;
            --p;
            --q;
            vec[p].push_back(q);
            vec[q].push_back(p);
        }
        memset(visit, 0, sizeof(visit));
        memset(color, 0, sizeof(color));
        bool flag = true;
        for(int i = 0; i < n; ++i)
        {
            if (!visit[i])
            {
                color[i] = 1;
                if(!bfs(i))
                {
                    flag = false;
                    break;
                }
            }
        }
        if(!flag)
        {
            cout << "can not find!" << endl;
            continue;
        }
        vector<int> vec1;
        vector<int> vec2;
        for(int i = 0; i < n; ++i)
        {
            if(color[i] == 1)
                vec1.push_back(i+1);
            else
                vec2.push_back(i+1);
        }
        ostream_iterator<int> out(cout, ",");
        cout << "first union: {";
        copy(vec1.begin(), vec1.end()-1, out);
        cout << vec1[vec1.size()-1] << "}" << endl;
        cout << "second union: {";
        copy(vec2.begin(), vec2.end()-1, out);
        cout << vec2[vec2.size()-1] << "}" << endl;
    }
    return 0;
}
/*
3
2 
1 2
2 3
4
4
1 2
2 3
3 4
4 1
4
5
1 2
1 3
1 4
2 3
3 4
*/
