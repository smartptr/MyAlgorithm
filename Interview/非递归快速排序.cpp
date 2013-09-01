#include <iostream>
#include <stack>
#include <utility>
using namespace std;

int partition(int a[], int l ,int r)
{
    int key = a[l];
    while(l <= r)
    {
        while(l <= r && a[r] >= key) --r;
        if(l <= r)
            swap(a[l], a[r]);
        while(l <= r && a[l] <= key) ++l;
        if(l <= r)
            swap(a[l], a[r]);
    }
    a[l] = key;
    return l;
}

void quickSort(int a[], int l, int r)
{
    stack< pair<int, int> > s;
    if(l <= r) s.push(make_pair(l, r));
    while(!s.empty())
    {
        pair<int, int> p = s.top();
        s.pop();
        int pos = partition(a, p.first, p.second);
        if(p.first <= pos-1)
            s.push(make_pair(l, pos-1));
        if(pos+1 <= p.second)
            s.push(make_pair(pos+1, r));
    }
}

int main()
{
    int a[] = {4,3,2,1,6,7,3,4,6,7};
    quickSort(a, 0, 9);
    for(int i = 0; i < 10; ++i)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
