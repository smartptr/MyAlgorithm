#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <memory.h>
using namespace std;

#define MAX_VALUE 100000000

class GameOnABoard {
public:
  	int optimalChoice(vector<string> cost);
};

const int maxn = 50;
int mp[maxn][maxn];
int dis[1800][1800];

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int bfs(int x,int y, int n, int m)
{
    queue<int> que;
    int p = x*m+y;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            dis[i][j] = MAX_VALUE;
        }
    }
    dis[x][y] = mp[x][y];
    que.push(p);
    bool visited[1800];
    memset(visited, 0, sizeof(visited));
    visited[p] = 1;
    int mmax = 0;
    while(!que.empty())
    {
        int q = que.front();
        que.pop();
        int x = q/m;
        int y = q%m;
        visited[q] = 0;
        for(int i = 0; i < 4;++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx>=0&&nx<n&&ny>=0&&ny<m)
            {
                int u = nx*m+ny;
                if(dis[nx][ny] > dis[x][y]+mp[nx][ny])
                {
                    dis[nx][ny] = dis[x][y]+mp[nx][ny];
                    if(!visited[u])
                    {
                        que.push(u);
                        visited[u] = 1;
                    }
                }
            }
        }
    }
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            mmax = max(mmax, dis[i][j]);
        }
    }
    return mmax;
}

int GameOnABoard::optimalChoice(vector<string> cost)
{
    int n = cost.size();
    int m = cost[0].size();
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            mp[i][j] = cost[i][j] - '0';
        }
    }
    int ans = MAX_VALUE;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            ans = min(ans,bfs(i,j, n, m));
        }
    }
    return ans;
}

//test
int main()
{
    vector<string> vec;
    GameOnABoard g;
    vec.push_back("111001");
    vec.push_back("001000");
    vec.push_back("111111");
    vec.push_back("001111");
    vec.push_back("001100");
    vec.push_back("001011");
    vec.push_back("111001");
    vec.push_back("010011");
    int ans = g.optimalChoice(vec);
    cout << ans << endl;
}

/*
0)  
    	

{"11",
 "10"}

Returns: 2

Regardless of Alice's choice, Bob can always achieve L=2 by choosing the opposite corner.

Sometimes he also has other optimal moves. For example, if Alice chooses (0,0), Bob can choose any of the other three cells to get L=2.
1)	
    	

{"01",
 "10"}

Returns: 1

Alice will not choose the cell (0,1), nor the cell (1,0). If she chooses one of those, Bob will choose the other one and L will be 2.

Alice prefers the other option. If she chooses one of the cells (0,0) or (1,1), Bob can only achieve L=1.
2)	
    	

{"111001",
 "001000",
 "111111",
 "001111",
 "001100",
 "001011",
 "111001",
 "010011"}

Returns: 3

3)	
    	

{"001001101011",
 "110011001101",
 "111111000001",
 "111101010001",
 "011100101111",
 "110010111000",
 "111111110101",
 "111011110111",
 "111100100011",
 "000000000110",
 "101011011110",
 "011111000111",
 "101111001011"}

Returns: 5

4)	
    	

{"110010100101010110100010001100111011",
 "001000000110100011010100000001001000",
 "011000110111101001011101110111000100",
 "111001011000100101111010100110110011",
 "111000011101001010000100001010000010",
 "111001110010100101000001001100011011",
 "111110100111010101100000100111000111",
 "011111111100100111111110000001110111",
 "110000010101001111100011110000001000",
 "010010110111111100011101100000011010",
 "110001100001111001101000101110110001",
 "110010000111011110000010110111010101",
 "100100110101001001101000001101101101",
 "001011101101001100111110101111001110",
 "111010111111111100110100000011111100",
 "110101101000001001000100101011100000",
 "011011001011010001001000100000110101",
 "011111111100000011010111010011010100",
 "111001111110001110001110010100111010",
 "000001111000001100101010000001101110",
 "010000110000010010111110111000010101",
 "100010010100110011000111101001101011",
 "111010110001101011010001111101111100",
 "000111110000110000000101100101000110",
 "110000010111001001110001101010111100",
 "011111101101001011011010011111100010",
 "110101111101010100110010000011001101",
 "101101111001010100101111100001110001",
 "000110010100101111011011110010010010",
 "110101010011101000111011100000010011",
 "110001010001110011010100110000010001",
 "111010101100111100100011001101010100",
 "011000000000100001011010000100010001",
 "100000110110000001010001001111010000",
 "100011111110010011011011001110011111",
 "101100001111100101001101100000100001",
 "010000111011010110011001110011111000",
 "100010100111110111001010100101111010",
 "000110011110111011111000101000001000"}

Returns: 7
*/
