#include <iostream>
#include <cstdio>
#include <cstring>
#include <deque>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <iterator>
using namespace std;

#define NChar 8 //suppose use 8 bits to describe all symbols
#define Nsymbols 1<<NChar //can describe 256 symbols totally (include a-z, A-Z)

typedef vector<bool> Huff_code;
map<char, Huff_code> Huff_dict;

class HTree
{
public:
    HTree* left;
    HTree* right;
    char ch;
    int weight;
    HTree() {left = NULL; right = NULL; ch = '\0'; weight = 0;}
    HTree(HTree* _lt, HTree* _rt, char _ch, int _weight):
            left(_lt), right(_rt), ch(_ch), weight(_weight){}
    ~HTree() {delete left; delete right;}
    bool IsLeaf() {return left == NULL && right == NULL; }
};


class Compare_tree
{
public:
    bool operator()(HTree* h1, HTree* h2)
    {
        return h1->weight > h2->weight;
    }
};

HTree* buildTree(int *frequency)
{
    priority_queue<HTree*, vector<HTree*>, Compare_tree> QTree;
    for(int i = 0; i < Nsymbols; ++i)
    {
        if(frequency[i])
            QTree.push(new HTree(NULL,NULL,(char)i, frequency[i]));
    }
    while(QTree.size() > 1)
    {
        HTree* left = QTree.top();
        QTree.pop();
        HTree* right = QTree.top();
        QTree.pop();
        HTree* root = new HTree(left, right, (char)256, left->weight+right->weight);
        QTree.push(root);
    }
    return QTree.top();
}

void Huffman_code(HTree* root, Huff_code& curcode)
{
    if(root->IsLeaf())
    {
        Huff_dict[root->ch] = curcode;
        return;
    }
    Huff_code lcode = curcode;
    Huff_code rcode = curcode;
    lcode.push_back(false);
    rcode.push_back(true);
    if(root->left)
        Huffman_code(root->left, lcode);
    if(root->right)
        Huffman_code(root->right, rcode);
}

int main()
{
    int fre[Nsymbols] = {0};
    char *str = "this is the string need to be compressed";
    while(*str != '\0')
        fre[*str++]++;
    HTree* root = buildTree(fre);
    Huff_code nullcode;
    Huffman_code(root, nullcode);
    map<char, Huff_code>::iterator it = Huff_dict.begin();
    for(; it != Huff_dict.end(); ++it)
    {
        cout << (*it).first << "\t";
        std::copy(it->second.begin(), it->second.end(), std::ostream_iterator<bool>(cout));
        cout << endl;
    }
    return 0;
}


