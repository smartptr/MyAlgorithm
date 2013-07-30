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

typedef double real;
typedef int int32;
typedef long long int64;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef short int16;
typedef unsigned uint16;
typedef char int8;
typedef unsigned char uint8;

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
};

bool operator == (const point& p, const point & q)
{
    assert(p.dim == q.dim);
    bool f = true;
    for(int i = 0; i < p.dim; ++i)
    {
        f &= (p.p[i] == q.p[i]);
    }
    return f;
}

//KDTree
struct KDTree
{
    int splitNum;
    point data;
    bool isLeaf;
    KDTree* left;
    KDTree* right;
    KDTree()
    {
        splitNum = -1;
        left = NULL;
        right = NULL;
        isLeaf = false;
    }
};

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
vector<real> calS(const vector<point>& data)
{
    assert(data.size() > 0);
    int size = data[0].dim;
    vector<real> p(size, 0);
    for(int i = 0; i < data.size(); ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            p[j] += data[i].p[j];
        }
    }
    for(int i = 0; i < size; ++i)
        p[i] /= (real)size;
    vector<real> pp(size, 0);
    for(int i = 0; i < data.size(); ++i)
    {
        for(int j = 0; j < data[i].dim; ++j)
        {
            pp[j] += power(data[i].p[j]-p[j]);
        }
    }
    return pp;
}

int select(const vector<point>& data)
{
    assert(data.size() > 0);
    vector<real> p = calS(data);
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

KDTree* buildKDTree(KDTree* root, const vector<point>& dataSet)
{
    if(dataSet.size() == 0)
        return NULL;
    root = new KDTree();
    if(dataSet.size() == 1)
    {
        root->splitNum = 0;
        root->isLeaf = true;
        root->data = dataSet[0];
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    vector<point> lt;
    vector<point> rt;
    vector<real> pt;

    int index = select(dataSet);
    for(int i = 0; i < dataSet.size(); ++i)
    {
        pt.push_back(dataSet[i].p[index]);
    }
    sort(pt.begin(), pt.end());
    int selectV = pt[pt.size()/2];

    root->splitNum = index;
    int pos = -1;
    for(int i = 0; i < dataSet.size(); ++i)
    {
        if(dataSet[i].p[index] == selectV)
        {
            root->data = dataSet[i];
            pos = i;
            break;
        }
    }
    for(int i = 0; i < dataSet.size(); ++i)
    {
        if(pos == i)
            continue;
        if(dataSet[i].p[index] <= selectV)
        {
            lt.push_back(dataSet[i]);
        }
        else
        {
            rt.push_back(dataSet[i]);
        }
    }
    root->left = buildKDTree(root->left, lt);
    root->right = buildKDTree(root->right, rt);
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
    assert(p.dim == q.dim);
    real sum = 0;
    for(int i = 0; i < p.dim; ++i)
    {
        sum += power(p.p[i] - q.p[i]);
    }
    return sum;
}

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

void searchTopK(KDTree* root, const point& p, int k)
{
    if(root == NULL)
        return ;
    if(root->isLeaf)
    {
        Node node;
        node.p = root->data;
        node.dis = pqdis(p, node.p);
        if(pque.size() < k || pque.top().dis > node.dis)
        {
            pque.push(node);
            if(pque.size() > k)
            {
                pque.pop();
            }
        }
        return ;
    }
    int split = root->splitNum;
    //cout << split << endl;
    KDTree* child1 = NULL;
    KDTree* child2 = NULL;
    if(split >= 0 && p.p[split] <= root->data.p[split])
    {
        child1 = root->left;
        child2 = root->right;
    }
    else if(split >= 0)
    {
        child1 = root->right;
        child2 = root->left;
    }
    if(child1)
    {
        searchTopK(child1, p, k);
    }else
    {
        Node node;
        node.p = root->data;
        node.dis = pqdis(p, node.p);
        if(split >= 0 && (pque.size() < k || pque.top().dis > node.dis))
        {
            pque.push(node);
            if(pque.size() > k)
            {
                pque.pop();
            }
        }
    }
    real d = power(Abs(root->data.p[split]-p.p[split]));
    if(split >= 0 && (d < pque.top().dis || pque.size() < k))
    {
        if(child2)
        {
            searchTopK(child2, p, k);
        }
        Node node;
        node.p = root->data;
        node.dis = pqdis(p, node.p);
        if(pque.size() < k || pque.top().dis > node.dis)
        {
            pque.push(node);
            if(pque.size() > k)
            {
                pque.pop();
            }
        }
    }
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
