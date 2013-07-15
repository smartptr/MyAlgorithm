/*
Calculate the sum: sum{n^a/b^n|n=1,2,3,...n...无穷大} 1<=a,b<=10
*/
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

using namespace std;


typedef long long LL;

LL gcd(LL a, LL b)
{
    if(b == 0)
    {
        return a;
    }
    return gcd(b, a%b);
}

LL lcm(LL a, LL b)
{
    return a/gcd(a,b) * b;
}

LL c[12][12];
LL a[20];
LL b[20];

void init()
{
    for(int i=1;i<12;i++) c[i][1] = 1;
    for(int i=1;i<12;++i) c[i][0] = 1;
    for(int i=2;i<12;++i)
    {
        for(int j=1;j<=i;++j)
        {
            c[i][j] = c[i-1][j] + c[i-1][j-1];
        }
    }
    /*for(int i = 1; i <= 5; ++i)
    {
        for(int j = 1; j <= i; ++j)
        {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }*/
}

LL power(int x, int y)
{
    LL num = 1;
    for(int i = 1; i <= y;++i)
    {
        num = num * (LL)x;
    }
    return num;
}

int sign(int x)
{
    if(x%2==1)
        return 1;
    else
        return -1;
}

void process(int x, int y)
{
    a[0] = 1;
    b[0] = (LL)y-1;
    a[1] = y;
    b[1] = power(y-1,2);
    for(int i = 2; i <= x; ++i)
    {
        vector<int> tmp;
        LL allLcm = 1;
        for(int j = i -1; j >=0; --j)
        {
            allLcm = lcm(allLcm, b[j]);
        }
        LL sum = 0;
        for(int j = 1; j <= i; ++j)
        {
            LL p1 = allLcm / b[i-j];
            sum += p1 * c[i][j] * a[i-j] * sign(j);
        }
        allLcm *= (y-1);
        sum *= y;
        LL g = gcd(sum, allLcm);
        a[i] = sum / g;
        b[i] = allLcm / g;
    }
    LL g = gcd(a[x], b[x]);
    cout << a[x]/g << "/" << b[x]/g << endl;
}

int main()
{
    init();
    int a, b;
    while(cin>>a>>b)
    {
        if(b==1&&a>=1)
        {
            cout << "infinity" << endl;
        }else
        {
            process(a,b);
        }
    }
    return 0;
}
