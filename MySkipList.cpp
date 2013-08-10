/*
 * function : skiplist
 * author: John_czg1989
 * date : 2013-08-10
*/
#include <iostream>
#include <assert.h>
#include <vector>
#include <iterator>
#include <time.h>
using namespace std;

typedef signed char           int8_t;
typedef signed short          int16_t;
typedef signed int            int32_t;
typedef signed long long      int64_t;
typedef unsigned char         uint8_t;
typedef unsigned short        uint16_t;
typedef unsigned int          uint32_t;
typedef unsigned long long    uint64_t;

class Random
{
private:
    uint32_t seed_;
public:
    explicit Random(uint32_t s): seed_(s & 0x7fffffffu) {}
    uint32_t Next()
    {
        static const uint32_t M = (1<<31)-1;
        static const uint64_t A = 16807;
        // seed_ = (seed_ * A) % M;
        uint64_t product = seed_ * A;
        seed_ = static_cast<uint32_t>((product >> 31) + (product & M));
        if(seed_ > M)
            seed_ -= M;
        return seed_;
    }
    // Returns a uniformly distributed value in the range [0..n-1]
    uint32_t Uniform(int n) { return Next() % n; }
};

template <typename keyType, typename valueType>
struct SkipListNode
{
    keyType key;
    valueType value;
    std::vector<SkipListNode*> forword;

    SkipListNode<keyType, valueType>* &operator = (const SkipListNode<keyType, valueType>* & p1)
    {
        key = p1->key;
        value = p1->value;
        return *this;
    }
};


template <typename keyType, typename valueType>
class SkipList
{
private:
    int level; // current level
    int maxLevel; // the bound of the level
    Random rnd_;
    SkipListNode<keyType, valueType>* header;
public:
    SkipList(int _maxLevel = 16):
        level(0), maxLevel(_maxLevel), rnd_(0xdeadbeef)
    {
        header = new SkipListNode<keyType, valueType>();
        assert(header != NULL);
        header->forword.resize(maxLevel, NULL);
    }

    ~SkipList()
    {
        SkipListNode<keyType, valueType>* p = header->forword[0];
        while(NULL != p)
        {
            SkipListNode<keyType, valueType>* next = p->forword[0];
            delete p;
            p = next;
        }
        header->forword.clear();
        delete header;
    }

    // generate the random level
    int random_level()
    {
        int level = 1;
        while ((rand()&1) == 1) // p = 0.25
            level += 1;
        if (level > maxLevel)
            level = maxLevel;
        return level;
        /*
        static const unsigned int kBranching = 4;
        int height = 1;
        while(height < maxLevel && ((rnd_.Next())%kBranching) == 0) {
            ++height;
        }
        assert(height > 0);
        assert(height <= maxLevel);
        return height;*/
    }

    // output
    void print()
    {
        SkipListNode<keyType, valueType>* p;
        for(int i = level - 1; i >= 0; --i)
        {
            p = header->forword[i];
            std::cout << "the level id is: " << i << endl;
            while(NULL != p)
            {
                std::cout << p->key << ": " << p->value << "\t";
                p = p->forword[i];
            }
            std::cout << endl;
        }
    }
    // insert pair: (key, value)
    // order by key
    bool Insert(const keyType& key, const valueType& value)
    {
        int k = level-1;
        SkipListNode<keyType, valueType>* update[maxLevel];
        SkipListNode<keyType, valueType>* p = header;
        SkipListNode<keyType, valueType>* q;
        while(k >= 0)
        {
            q = p->forword[k];
            while(NULL != q && q->key < key)
            {
                p = q;
                q = p->forword[k];
            }
            if(NULL != p)
                update[k] = p;
            --k;
        }
        if(NULL != q && q->key == key) //exits改进方案是可以存相同的key，在key相同时根据value进行,redis做法
        {
            q->value = value;
            return false;
        }
        k = random_level();
        cout << "k = " << k << endl;
        if(k > level)
        {
            k = ++level;
            update[k-1] = header;
        }
        q = new SkipListNode<keyType, valueType>();
        if(NULL == q)
            return false;
        q->forword.resize(k, NULL);
        q->key = key;
        q->value = value;
        while(--k >= 0)
        {
            p = update[k];
            q->forword[k] = p->forword[k];
            p->forword[k] = q;
        }
        return true;
    }

    // delete pair: (key, value)
    // based the key
    bool Delete(const keyType& key, SkipListNode<keyType, valueType>& deleteNode)
    {
        SkipListNode<keyType, valueType>* update[maxLevel];
        SkipListNode<keyType, valueType>* p = header;
        SkipListNode<keyType, valueType>* q;
        int k = level - 1;
        while(k >= 0)
        {
            q = p->forword[k];
            while(NULL != q && q->key < key)
            {
                p = q;
                q = p->forword[k];
            }
            update[k] = p;
            --k;
        }
        if(NULL != q && q->key == key)
        {
            //deleteNode->value = q->value;
            //deleteNode->key = q->key;
            deleteNode = *q;
            //cout << deleteNode.key << "!!!" << deleteNode.value << endl;
            for(int i = 0; i < level; ++i)
            {
                if(update[i]->forword[i] != q)
                    break;
                p = update[i];// update[i]是q的前驱
                assert(p->forword[i]->key == key);
                p->forword[i] = q->forword[i];
            }
            delete q;
            int m = level;
            while(header->forword[m-1] == NULL && m > 0)
                --m;
            level = m;
            cout << m << endl;
            return true;
        }
        return false;
    }

    // search pair: (key, value)
    // based key, save to value
    bool search(const keyType& key, valueType& value)
    {
        SkipListNode<keyType, valueType>* p = header;
        SkipListNode<keyType, valueType>* q;
        int k = level-1;
        while(k >= 0) // [0,level-1]
        {
            q = p->forword[k];
            while(NULL != q && q->key < key)  // search the level of k
                q = q->forword[k];
            --k;
        }
        if(NULL != q && q->key == key)
        {
            value = q->value;
            return true;
        }
        return false;
    }
};

//test
int main(int argc, char* argv[])
{
    SkipList<int, int> skip_list;
    //test insert
    cout << "insert (1,2)" << endl;
    bool r = skip_list.Insert(1,2);
    if (!r) {
        cout << "Insertion Failure!" << endl;
    }
    cout << "insert (3,4)" << endl;
    r = skip_list.Insert(3, 4);
    if (!r) {
        cout << "Insertion Failure!" << endl;
    }
    cout << "insert (2,4)" << endl;
    r = skip_list.Insert(2,4);
    if (!r) {
        cout << "Insertion Failure!" << endl;
    }
    cout << "insert (5,6)" << endl;
    r = skip_list.Insert(5, 6);
    if (!r) {
        cout << "Insertion Failure!" << endl;
    }
    skip_list.print();

    //test search
    int v = -1;
    r = skip_list.search(1, v);
    assert(v == 2);
    r = skip_list.search(3, v);
    assert(v == 4);
    r = skip_list.search(5, v);
    assert(v == 6);

    //test delete
    SkipListNode<int, int> deleteNode;// = new SkipListNode<int, int>();
    cout << "delete key:1" << endl;
    r = skip_list.Delete(1, deleteNode);
    if (!r) {
        cout << "Deletion failure.." << endl;
    }
    cout << "delete key: " << deleteNode.key << " value: " << deleteNode.value << endl;
    skip_list.print();

    cout << "delete key:3" << endl;
    r = skip_list.Delete(3, deleteNode);
    if (!r) {
        cout << "Deletion failure.." << endl;
    }
    cout << "delete key: " << deleteNode.key << " value: " << deleteNode.value << endl;
    skip_list.print();

    cout << "delete key:5" << endl;
    r = skip_list.Delete(5, deleteNode);
    if (!r) {
        cout << "Deletion failure.." << endl;
    }
    cout << "delete key: " << deleteNode.key << " value: " << deleteNode.value << endl;
    skip_list.print();

    return 0;
}
