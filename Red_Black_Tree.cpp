/*
 * function : red-black tree
 * author : John_czg1989
 * date : 2013-08-11
*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
using namespace std;

template <class K, class V>
class RBTree
{
private:
    RBTree(const RBTree& _rbt) {}
    const RBTree& operator = (const RBTree& _rbt) {}
public:
    enum COLOR{RED, BLACK};
    class RBNode
    {
    public:
        COLOR color;
        RBNode* left_;
        RBNode* right_;
        RBNode* parent_;
        K key;
        V value;
    public:
        RBNode():color(BLACK), left_(NULL),right_(NULL), parent_(NULL){}
        void output()
        {
            cout << key << "  " << value << "  " << color << endl;
        }
    };
public:
    RBTree()
    {
        nullNode_ = new RBNode();
        root_ = nullNode_;
        nullNode_->left_ = root_;
        nullNode_->right_ = root_;
        nullNode_->parent_ = root_;
        nullNode_->color = BLACK;
    }
    bool IsEmpty()
    {
        return root_ == nullNode_;
    }
    RBNode* getRoot() { return root_; };
    //search
    RBNode* search_(K key)
    {
        RBNode* node = root_;
        while(node != nullNode_)
        {
            if(key < node->key)
                node = node->left_;
            else if(key > node->key)
                node = node->right_;
            else
                return node;
        }
        return node;
    }
    // left rotate
    void rotate_left(RBNode* node)
    {
        if(node == nullNode_ || node->right_ == nullNode_)
            return;
        RBNode* r_n = node->right_;;
        node->right_ = r_n->left_;
        r_n->parent_ = node->parent_;
        if(r_n->left_ != nullNode_)
            r_n->left_->parent_ = node;
        if(node->parent_ == nullNode_)
        {
            root_ = r_n;
            nullNode_->left_ = root_;
            nullNode_->right_ = root_;
        }
        else
        {
            if(node->parent_->left_ == node)
                node->parent_->left_ = r_n;
            else
                node->parent_->right_ = r_n;
        }
        node->parent_ = r_n;
        r_n->left_ = node;
    }
    // right rotate
    void rotate_right(RBNode* node)
    {
        if(node == nullNode_ || node->left_ == nullNode_)
            return ;
        RBNode* l_n = node->left_;
        node->left_ = l_n->right_;
        l_n->parent_ = node->parent_;
        if(l_n->right_ != nullNode_)
            l_n->right_->parent_ = node;
        if(node->parent_ == nullNode_)
        {
            root_ = l_n;
            nullNode_->left_ = root_;
            nullNode_->right_ = root_;
        }
        else
        {
            if(node->parent_->left_ == node)
                node->parent_->left_ = l_n;
            else
                node->parent_->right_ = l_n;
        }
        node->parent_ = l_n;
        l_n->right_ = node;
    }
    //insert
    bool Insert(K key, V value)
    {
        RBNode* insert_point = nullNode_;
        RBNode* pnode = root_;
        while(pnode != nullNode_)
        {
            insert_point = pnode;
            if(key == pnode->key)
                return false;
            else if(key < pnode->key)
                pnode = pnode->left_;
            else
                pnode = pnode->right_;
        }
        RBNode* insert_node = new RBNode();
        insert_node->color = RED;
        insert_node->key = key;
        insert_node->value = value;
        insert_node->left_ = nullNode_;
        insert_node->right_ = nullNode_;
        if(insert_point == nullNode_)
        {
            root_ = insert_node;
            root_->parent_ = nullNode_;
            nullNode_->left_ = root_;
            nullNode_->right_ = root_;
            nullNode_->parent_ = root_;
        }
        else
        {
            if(key < insert_point->key)
                insert_point->left_ = insert_node;
            else
                insert_point->right_ = insert_node;
            insert_node->parent_ = insert_point;
        }
        RB_Insert_FixUp(insert_node);
        return true;
    }
    //insert_fix_up
    void RB_Insert_FixUp(RBNode* node)
    {
        while(node->parent_->color == RED)
        {
            if(node->parent_->parent_->left_ == node->parent_) // parent is left node
            {
                RBNode* uncle = node->parent_->parent_->right_;
                if(uncle->color == RED)// father and uncle both are red color
                {
                    node->parent_->color = BLACK;
                    uncle->color = BLACK;
                    node->parent_->parent_->color = RED;
                    node = node->parent_->parent_;
                }
                else
                {
                    if(node == node->parent_->right_) // node is the right child, father is the left child
                    {
                        node = node->parent_;
                        rotate_left(node);
                    }
                    node->parent_->color = BLACK;
                    node->parent_->parent_->color = RED;
                    rotate_right(node->parent_->parent_);
                }
            }
            else // parent is right node
            {
                RBNode* uncle = node->parent_->parent_->left_;
                if(uncle->color == RED)
                {
                    node->parent_->color = BLACK;
                    uncle->color = BLACK;
                    node->parent_->parent_->color = RED;
                    node = node->parent_->parent_;
                }
                else
                {
                   if(node == node->parent_->left_) // node is the left child, father is the right child
                   {
                        node = node->parent_;
                        rotate_right(node);
                   }
                   node->parent_->color = BLACK;
                   node->parent_->parent_->color = RED;
                   rotate_left(node->parent_->parent_);
                }
            }
        }
        root_->color = BLACK;
    }

    // find the successpr of the node
    RBNode* successor(RBNode* node)
    {
        if(node == nullNode_)
            return nullNode_;
        RBNode* pnode = node->right_;
        while(pnode != nullNode_)
        {
            if(pnode->left_ != nullNode_)
                pnode = pnode->left_;
            else
                break;
        }
        if(pnode == nullNode_) //the right child of node is null, find its lowest father
        {
            RBNode* pp = node->parent_;
            pnode = node;
            while(pp != nullNode_ && pnode == pp->right_)
            {
                pnode = pp;
                pp = pp->parent_;
            }
            pnode = pp;
        }
        return pnode;
    }
    // find the predecessor of the node
    RBNode* predecessor(RBNode* node)
    {
        if(node == nullNode_)
            return nullNode_;
        RBNode* pnode = node->left_;
        while(pnode != nullNode_)
        {
            if(pnode->right_ != nullNode_)
                pnode = pnode->right_;
        }
        if(pnode == nullNode_)
        {
            RBNode* pp = node->parent_;
            pnode = node;
            while(pp != nullNode_ && pnode == pp->left_)
            {
                pnode = pp;
                pp = pp->parent_;
            }
            pnode = pp;
        }
        return pnode;
    }

    // del the node
    bool Delete(K key)
    {
        RBNode* node = search_(key);
        if(node == nullNode_)
            return false;
        RBNode* pnode = nullNode_;
        if(node->left_ == nullNode_ || node->right_ == nullNode_) //at least has one empty child
            pnode = node;
        else //find the successor of the node to replace current node, and delete the successor node
        {
            pnode = successor(node);
            node->key = pnode->key;
            node->value = pnode->value;
        }
        RBNode* rep = nullNode_;
        if(pnode->left_ != nullNode_) //check the empty child of the current node
            rep = pnode->left_;
        else if(pnode->right_ != nullNode_)
            rep = pnode->right_;
        rep->parent_ = pnode->parent_;
        if(pnode->parent_ == nullNode_) // if delete node is root
        {
            root_ = rep;
            nullNode_->left_ = rep;
            nullNode_->left_ = rep;
            nullNode_->parent_ = rep;
        }
        else if(pnode->parent_->left_ == pnode) //check the delete node is left or right
        {
            pnode->parent_->left_ = rep;
        }
        else if(pnode->parent_->right_ == pnode)
        {
            pnode->parent_->right_ = rep;
        }
        //the delete node's color is black and is not nullnode
        //and is not the root of the tree
        if(pnode->color == BLACK &&!(rep == nullNode_ &&
                                    rep->parent_ == nullNode_))
            RB_Delete_FixUp(rep);
        delete pnode;
        return true;
    }

    // fix-up the current red-balck tree
    void RB_Delete_FixUp(RBNode* node)
    {
        while(node != root_ && node->color == BLACK)
        {
            if(node == node->parent_->left_)
            {
                RBNode* brother = node->parent_->right_;
                if(brother->color == RED)
                {
                    brother->color = BLACK;
                    node->parent_->color = RED;
                    rotate_left(node->parent_);
                }
                else if(brother->color == BLACK)
                {
                    if(brother->left_->color == BLACK &&
                        brother->right_->color == BLACK)
                    {
                        brother->color = RED;
                        node = node->parent_;
                    }
                    else if(brother->right_->color == BLACK)
                    {
                        brother->color = RED;
                        brother->left_->color = BLACK;
                        rotate_right(brother);
                    }
                    else if(brother->right_->color == RED)
                    {
                        brother->color = brother->parent_->color;
                        brother->parent_->color = BLACK;
                        brother->right_->color = BLACK;
                        rotate_left(brother->parent_);
                        node = root_;
                    }

                }
            }
            else
            {
                RBNode* brother = node->parent_->left_;
                if(brother->color == RED)
                {
                    brother->color = BLACK;
                    node->parent_->color = RED;
                    rotate_right(node->parent_);
                }
                else if(brother->color == BLACK)
                {
                    if(brother->left_->color == BLACK &&
                        brother->right_->color == BLACK)
                    {
                        brother->color = RED;
                        node = node->parent_;
                    }
                    else if(brother->left_->color == BLACK)
                    {
                        brother->color = RED;
                        brother->right_->color = BLACK;
                        rotate_left(brother);
                    }
                    else if(brother->left_->color == RED)
                    {
                        brother->color = node->parent_->color;
                        brother->left_->color = BLACK;
                        node->parent_->color = BLACK;
                        rotate_right(node->parent_);
                        node = root_;
                    }
                }
            }
        }
        node->color = BLACK;//if node is root or the color of the node is red
    }
    // pre order travel
    void preOrder() { preOrder(root_); }
    void preOrder(RBNode* node)
    {
        cout << "key: " << node->key << " value: " << node->value << endl;
        if(node->left_ != nullNode_)
            preOrder(node->left_);
        if(node->right_ != nullNode_)
            preOrder(node->right_);
    }

    // in order travel
    void InOrder() { InOrder(root_); }
    void InOrder(RBNode* node)
    {
        if(node->left_ != nullNode_)
            InOrder(node->left_);
        cout << "key: " << node->key << " value: " << node->value << endl;
        if(node->right_ != nullNode_)
            InOrder(node->right_);
    }
    // post order travel
    void postOrder() { postOrder(root_); }
    void postOrder(RBNode* node)
    {
        if(node->left_ != nullNode_)
            postOrder(node->left_);
        if(node->right_ != nullNode_)
            postOrder(node->right_);
        cout << "key: " << node->key << " value: " << node->value << endl;
    }
public:
    ~RBTree()
    {
        clear(root_);
        delete nullNode_;
    }
private:
    RBNode* root_;
    RBNode* nullNode_;
private:
    void clear(RBNode* node)
    {
        if(node == nullNode_)
        {
            return;
        }
        clear(node->left_);
        clear(node->right_);
        delete node;
    }
};

//test
int main(int* argv, char** argc)
{
    RBTree<int, int> tree;
    vector<int> v;
    for(int i=0;i<20;++i)
        v.push_back(i);
    random_shuffle(v.begin(), v.end());
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    for(int i = 0; i < v.size(); ++i)
    {
        bool f = tree.Insert(v[i], i + 1);
        cout << f << "  insert: " << v[i] << endl;
    }
    cout << "preOrder: " << endl;
    tree.preOrder();
    cout << "InOrder: " << endl;
    tree.InOrder();
    cout << "PostOrder: " << endl;
    tree.postOrder();
    RBTree<int,int>::RBNode* pp = tree.search_(10);
    pp->output();
    RBTree<int,int>::RBNode* node = tree.successor(pp);
    node->output();
    RBTree<int,int>::RBNode* node1 = tree.predecessor(pp);
    node1->output();
    for(int i = 0; i < v.size(); ++i)
    {
        cout << "delete: " << v[i] << endl;
        tree.Delete(v[i]);
        if(!tree.IsEmpty())
            tree.InOrder();
        else
            cout << "tree is empty!" << endl;
        cout<< "##############" << endl;
    }
    return 0;
}
