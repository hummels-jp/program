#include <iostream>
using namespace std;

// Binary Search Tree Node
template<typename K, typename V>
struct BSTNode
{
    K _key;
    V _value;
    BSTNode* _left;
    BSTNode* _right;

    // consturct function
    BSTNode(K key, V value) 
        : _key(key)
        , _value(value)
        , _left(nullptr)
        , _right(nullptr)
    {

    }
};


template<typename K, typename V>
class MyMap
{
private:
    BSTNode<K, V>* _root;

    // delete node by recurise
    void clear(BSTNode<K, V>* node)
    {
        if (node == nullptr)
        {
            /* code */
            return;
        }

        clear(node->_left);
        clear(node->_right);
        delete node; 
    }

    // insert, insert an node into the tree
    BSTNode<K, V>* insert(BSTNode<K,V>* node, K key, V value)
    {
        if (node == nullptr)
        {
            /* code */
            return new BSTNode(key, value);
        }

        if (key < node->_key)
        {
            /* code */
            node->_left = insert(node->_left, key, value);
        }
        else if (key > node->_key)
        {
            /* code */
            node->_right = insert(node->_right, key, value);
        }
        else
        {
            node->_value = value;
        }

        return node;  
    }

    // find an value in the tree
    BSTNode<K, V>* find(BSTNode<K, V>* node, const K& key) const
    {
        if (node == nullptr)
        {
            /* code */
            return nullptr;
        }

        if (key < node->_key)
        {
            /* code */
            return find(node->_left, key);
        }
        else if (key > node->_key)
        {
            /* code */
            return find(node->_right, key);
        }
        else
        {
            return node;
        }        
    }

    // visit the tree by pre order
    void pre_order(BSTNode<K, V>* node)
    {
        if (node == nullptr)
        {
            /* code */
            return;
        }

        cout << "key : " << node->_key << " value: " << node->_value << endl;
        pre_order(node->_left);
        pre_order(node->_right);
        
    }

    // visit the tree by mid order
    void mid_order(BSTNode<K, V>* node)
    {
        if (node == nullptr)
        {
            /* code */
            return;
        }

        mid_order(node->_left);
        cout << "key : " << node->_key << " value: " << node->_value << endl;
        mid_order(node->_right);
        
    }

    // visit the tree by post order
    void post_order(BSTNode<K, V>* node)
    {
        if (node == nullptr)
        {
            /* code */
            return;
        }
        post_order(node->_left);
        post_order(node->_right);
        cout << "key : " << node->_key << " value: " << node->_value << endl;
    }

public:
    // construct function
    MyMap():_root(nullptr)
    {
    }

    // deconstruct function 
    ~MyMap()
    {
        delete _root;
    }

    // inset an node into the root
    void insert(K key, V value)
    {
        _root = insert(_root, key, value);
    }

    // whether the key is in the map
    bool contains(K key)
    {
        if (find(_root, key) == nullptr)
        {
            /* code */
            return false;
        }
        else
        {
            return true;
        }
        
    }

    // get an element by key, override operator []
    // if not exist, create an element
    V& operator[](const K& key)
    {
        BSTNode<K, V>* node = _root;
        BSTNode<K, V>* parent = nullptr;

        // can find the key
        while (node != nullptr)
        {
            /* code */
            parent = node;
            if (key < node->_key)
            {
                /* code */
                node = node->_left;
            }
            else if (key > node->_key)
            {
                /* code */
                node = node->_right;
            }
            else
            {
                return node->_value;
            }
        }

        // can not find the key, create an new element
        if (_root == nullptr)
        {
            /* code */
            _root = new BSTNode<K, V>(key, V());
            return _root->_value;
        }


        if (key < parent->_key)
        {
            /* code */
            parent->_left = new BSTNode<K, V>(key, V());
            return parent->_left->_value;
        }
        else
        {
            /* code */
            parent->_right = new BSTNode<K, V>(key, V());
            return parent->_right->_value;
        }
    }

    // visit the tree by pre order
    void pre_order()
    {
        pre_order(_root);
    }

};


int main() {
    MyMap<int, string> mp;
    mp.insert(3, "three");
    mp.insert(1, "one");
    mp.insert(2, "two");
    mp[4] = "four";
    mp[2] = "TWO";

    cout << "前序遍历输出Map内容：" << endl;
    mp.pre_order();

    cout << "查找key=2: " << (mp.contains(2) ? "存在" : "不存在") << endl;
    cout << "查找key=5: " << (mp.contains(5) ? "存在" : "不存在") << endl;
    return 0;
}