#include <cstdio>
#include <iostream>
using namespace std;

const int MAX = 0x3fffffff;
int a[101][101];

int maxsubsque(int a[], int n)
{
    int sum = 0;
    int maxsum = -MAX;
    for (int i = 0; i < n; ++i)
    {
        if (sum > 0 )
            sum += a[i];
        else
            sum = a[i];
        if(sum > maxsum)
            maxsum = sum;
    }
    return maxsum;
}

int maxsubmatrix(int n)
{
    int maxsum = -MAX;
    int b[101];
    for(int i = 0; i < n; ++i)
    {
        memset(b, 0, sizeof(b));
        for(int j = i; j < n; ++j)
        {
            for(int k = 0; k < n; ++k)
            {
                b[k] += a[j][k];
            }
            int sum = maxsubsque(b, n);
            if (sum > maxsum)
                maxsum = sum;
        }
    }
    return maxsum;
}

int main()
{
    int n;
    while(cin >> n)
    {
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                cin >> a[i][j];
        cout << maxsubmatrix(n) << endl;
    }
    return 0;
}

