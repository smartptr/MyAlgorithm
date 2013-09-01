#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <ostream>
using namespace std;


void FindTopK(const vector<int>& data, int K, multiset<int, greater<int> >& result)
{
    if(K == 0 || data.size() < K)
        return; //do something,根据面试官要求的情况决定返回结果
    for(vector<int>::const_iterator it = data.begin(); it != data.end(); ++it)
    {
        if(result.size() < K)
            result.insert((*it));
        else
        {
            multiset<int, greater<int> >::iterator it_re = result.begin();
            if(*it_re > *it)
            {
                result.erase(it_re);
                result.insert(*it);
            }
        }
    }
}

int main()
{
    int a[] = {4,3,2,1,6,7,3,4,6,7};
    vector<int> b(a, a+10);
    multiset<int, greater<int> > result;
    FindTopK(b, 5,result);
    ostream_iterator<int> out(cout, " ");
    copy(result.rbegin(), result.rend(), out);
    return 0;
}
