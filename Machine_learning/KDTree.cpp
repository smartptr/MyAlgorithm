//KDTree数求KNN，与某一点最近的k个点，优先队列保存最近的k个点，其实就是建一个有k个元素的最小堆
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <memory.h>
#include <iterator>
#include <queue>
#include <assert.h>
using namespace std;

typedef int real;
typedef int int32;
typedef long long int64;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef short int16;
typedef unsigned uint16;
typedef char int8;
typedef unsigned char uint8;

const int maxn = 50005;

struct point
{
    vector<real> p;
    int dim;
    point():dim(0){}
    point(const vector<real>& _p) : p(_p.begin(), _p.end())
    {
        dim = _p.size();
    }
    void output()
    {
        for(int i = 0; i < dim; ++i)
            if(i == 0) cout << p[i];
            else cout << " " << p[i] ;
        cout << endl;
    }
    friend bool operator == (const point& p, const point & q)
    {
        assert(p.dim == q.dim);
        bool f = true;
        for(int i = 0; i < p.dim; ++i)
        {
            f &= (p.p[i] == q.p[i]);
        }
        return f;
    }
};


//KDTree
struct KDTree
{
    int splitNum;
    point data;
    KDTree* left;
    KDTree* right;
    KDTree()
    {
        splitNum = -1;
        left = NULL;
        right = NULL;
    }
};

point data[maxn];
int N;
template <typename T>
T power(T p)
{
    return p * p;
}

template <typename T>
T getMax(T a, T b)
{
    return a > b ? a : b;
}

//计算方差
vector<real> calS(int l, int r)
{
    int size = data[0].dim;
    vector<real> p(size, 0);
    for(int i = l; i < r + 1; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            p[j] += data[i].p[j];
        }
    }
    for(int i = 0; i < size; ++i)
        p[i] /= (real)size;
    vector<real> pp(size, 0);
    for(int i = l; i < r + 1; ++i)
    {
        for(int j = 0; j < data[i].dim; ++j)
        {
            pp[j] += power(data[i].p[j]-p[j]);
        }
    }
    return pp;
}

//根据方差选择坐标轴
int select(int l, int r)
{
    vector<real> p = calS(l, r);
    int mmax = 0;
    int index = -1;
    for(int i = 0; i < p.size(); ++i)
    {
        if(mmax < p[i])
        {
            mmax = p[i];
            index = i;
        }
    }
    return index;
}

void QuickSort(int pos, int first, int last)
{
    int i = first, j = last;
    point tmp = data[first];
    while(i < j)
    {
        while(i < j && data[j].p[pos] >= tmp.p[pos]) --j;
        if(i < j) data[i] = data[j];
        while(i < j && data[i].p[pos] <= tmp.p[pos]) ++i;
        if(i < j) data[j] = data[i];
    }
    data[i] = tmp;
    if(first < i - 1)
        QuickSort(pos, first, i-1);
    if(last > i + 1)
        QuickSort(pos, i+1, last);
}

KDTree* buildKDTree(KDTree* root, int l, int r, int dep)
{
    if(l > r)
        return NULL;
    root = new KDTree();
    if(l == r)
    {
        root->splitNum = 0;
        root->data = data[l];
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    //一种是根据层进行寻找分割轴
    int index = dep%N;//select(l, r);
    QuickSort(index, l, r);
    int mid = l + (r-l)/2;
    root->splitNum = index;
    root->data = data[mid];
    root->left = buildKDTree(root->left, l, mid-1, dep+1);
    root->right = buildKDTree(root->right, mid+1, r, dep+1);
    return root;
}

struct Node
{
    point p;
    real dis;
    Node(real _dis = 0):dis(_dis){}
};

bool operator < (const Node& p, const Node& q)
{
    return p.dis < q.dis;
}

priority_queue<Node> pque;

real pqdis(const point& p, const point& q)
{
    real sum = 0;
    for(int i = 0; i < p.dim; ++i)
    {
        sum += power(p.p[i] - q.p[i]);
    }
    return sum;
}

//遍历该tree树
void trans(KDTree* root)
{
    root->data.output();
    if(root->left != NULL)
       trans(root->left);
    if(root->right != NULL)
        trans(root->right);
}

void destroy(KDTree* root)
{
    if(root == NULL)
        return;
    if(root->left != NULL)
       destroy(root->left);
    if(root->right != NULL)
        destroy(root->right);
    delete root;
    root = NULL;
}

template <typename T>
T Abs(T a)
{
    return a > 0 ? a : -a;
}

void searchTopK(KDTree* root, const point& p, int k, int dep)
{
    if(root == NULL)
        return ;
    KDTree* child1 = NULL;
    KDTree* child2 = NULL;
    int split = dep%N;//root->splitNum;
    if(p.p[split] <= root->data.p[split])
    {
        child1 = root->left;
        child2 = root->right;
    }
    else
    {
        child1 = root->right;
        child2 = root->left;
    }
    if(child1)
    {
        searchTopK(child1, p, k, dep+1);
    }
    Node node;
    node.p = root->data;
    node.dis = pqdis(p, node.p);
    bool f = false;
    if(pque.size() < k )
    {
        pque.push(node);
        f = true;
    }
    else
    {
        if(pque.top().dis > node.dis) {
            pque.pop();
            pque.push(node);
        }
        real d = power(Abs(root->data.p[split]-p.p[split]));
        if(d < pque.top().dis)
            f = true;
    }

    if(child2 && f)
        searchTopK(child2, p, k, dep+1);
}

void findKNN(vector<point>& p)
{
    p.clear();
    while(!pque.empty())
    {
        p.push_back(pque.top().p);
        pque.pop();
    }
    std::reverse(p.begin(), p.end());
}
