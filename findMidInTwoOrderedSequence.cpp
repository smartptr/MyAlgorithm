#include <cstdio>
#include <iostream>
using namespace std;

const int maxn = 1000;

int a[maxn];
int b[maxn];
int n;

int findMergeMedian(int a[], int b[], int len)
{
    if (len == 1)
    {
        return a[0] > b[0] ? b[0] : a[0];
    }
    int mid = (len-1)/2;
    if (a[mid] == b[mid])
        return a[mid];
    if (a[mid] < b[mid])
    {
        return findMergeMedian(&a[len - mid - 1], &b[0], mid+1);
    }
    else
        return findMergeMedian(&a[0], &b[len - mid - 1], mid+1);
}

int findMergeMedian1(int a[], int b[], int len)
{
    while(1)
    {
        if (len == 1)
        {
            return a[0] > b[0] ? b[0] : a[0];
        }
        int mid = (len-1)/2;
        if (a[mid] == b[mid])
            return a[mid];
        else if (a[mid] < b[mid])
            a = a + len - mid - 1;
        else
            b = b + len - mid - 1;
        len = mid + 1;
    }
}

int main()
{
    while(cin >> n)
    {
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        for (int j = 0; j < n; ++j)
            cin >> b[j];
        cout << findMergeMedian(a, b, n) << endl;
        cout << findMergeMedian1(a, b, n) << endl;
    }
    return 0;
}
