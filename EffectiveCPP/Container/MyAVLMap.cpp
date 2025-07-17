#include <iostream>
#include <math.h>
using namespace std;

template<typename K, typename V>
struct AVLNode
{
    K _key;
    V _value;
    AVLNode* _left;
    AVLNode* _right;
    int _height;

    // consturct function
    AVLNode(K key, V value)
        : _key(key)
        , _value(value)
        , _left(nullptr)
        , _right(nullptr)
        , _height(0)
    {

    }
};

template <typename K, typename V>
class AVLMap
{
private:
    AVLNode<K, V>* _root;

    // get the height of a node
    int height(AVLNode<K, V>* node)
    {
        if (node == nullptr)
        {
            /* code */
            return 0;
        }
        else
        {
            return node->_height;
        }
        
    }

    // get the balance factor of a node
    int balance_factor(AVLNode<K, V>* node)
    {
        if (node == nullptr)
        {
            /* code */
            return 0;
        }
        else 
        {
            return (height(node->_left) - height(node->_right));
        }
    }

    // update the height of a node
    void update_height(AVLNode<K, V>* node)
    {
        node->_height = 1 + max(height(node->_left), height(node->_right));
    }

    // right_rotate, left child height is bigger than right child
    AVLNode<K, V>* right_rotate(AVLNode<K, V>* y)
    {
        AVLNode<K, V>* x = y->_left;
        AVLNode<K, V>* T2 = x->_right;

        x->_right = y;
        y->_left = T2;

        update_height(y);
        update_height(x);

        return x;
    }

    // left rotate, right child height is bigger than left child
    AVLNode<K, V>* left_rotate(AVLNode<K, V>* y)
    {
        AVLNode<K, V>* x = y->_right;
        AVLNode<K, V>* T2 = x->_left;

        x->_left = y;
        y->_right = T2;

        update_height(y);
        update_height(x);

        return x;
    }

    // balance, LL, RR, LR, RL
    AVLNode<K, V>* balance(AVLNode<K, V>* node)
    {
        update_height(node);
        int bf = balance_factor(node);

        if (bf > 1)
        {
            /* code */
            // LR
            if (balance_factor(node->_left) < 0)
            {
                /* code */
                node->_left = left_rotate(node->_left);
            }
            
            return right_rotate(node);
            
            
        }

        if (bf < -1)
        {
            /* code */
            // RL
            if (balance_factor(node->_left) > 0)
            {
                /* code */
                node->_right = right_rotate(node->_right);
            }

            return left_rotate(node);
            
        }   
    }

    // insert node
    AVLNode<K, V>* insert(AVLNode<K, V>* node, K key, V value)
    {
        if (node == nullptr)
        {
            /* code */
            node = new AVLNode<K, V>(key, value);
        }

        if (key < node->_key)
        {
            /* code */
            node->_left = insert(node->_left, key, value);
        }
        if (key > node->_key)
        {
            /* code */
            node->_right = insert(node->_right, key, value);
        }
        else
        {
            node->_value = value;
        }

        // after insert, balance the node
        return balance(node);   
    }

    // find the node by key
    AVLNode<K, V>* find(AVLNode<K, V>* node, const K& key)
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

    // remove the node
    void clear(AVLNode<K, V>* node)
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

    // pre order visit the node
    void pre_order(AVLNode<K, V>* node) const
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

    void mid_order(AVLNode<K, V>* node) const
    {
        if (node == nullptr)
        {
            /* code */
            return ;
        }

        mid_order(node->_left);
        cout << "key : " << node->_key << " value: " << node->_value << endl;
        mid_order(node->_right);
        
    }

    void post_order(AVLNode<K, V>* node) const
    {
        if (node == nullptr)
        {
            /* code */
            return ;
        }

        post_order(node->_left);
        post_order(node->_right);
        cout << "key : " << node->_key << " value: " << node->_value << endl;     
    }

public:
    AVLMap(): _root(nullptr)
    {

    }

    ~AVLMap()
    {
        clear(_root);
    }

    // insert node
    void insert(const K& key, const V& value)
    {
        _root = insert(_root, key, value);
    }

    // find node
    bool contains(const K& key)
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

    // get the value by index
    // if not exist, create a new one
    V& operator[](const K& key)
    {
        AVLNode<K, V>* node = _root;
        AVLNode<K, V>* parent = nullptr;

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

        // if not exist 
        if (_root == nullptr)
        {
            /* code */
            _root = new AVLNode<K, V>(key, V());
            return _root->_value;
        }

        if (key< parent->_key)
        {
            /* code */
            parent->_left = new AVLNode<K, V>(key, V());
            _root = balance(_root);
            return parent->_left->_value;
        }
        else
        {
            parent->_right = new AVLNode<K, V>(key, V());
            _root = balance(_root);
            return parent->_right->_value;
        }   
    }

    void pre_order() const
    {
        pre_order(_root);
    }

    void mid_order() const
    {
        mid_order(_root);
    }

    void post_order() const
    {
        post_order();
    }
};

int main() {
    AVLMap<int, std::string> mp;
    mp.insert(3, "three");
    mp.insert(1, "one");
    mp.insert(2, "two");
    mp[4] = "four";
    mp[2] = "TWO";

    // std::cout << "前序遍历输出AVLMap内容：" << std::endl;
    // mp.pre_order();

    // std::cout << "查找key=2: " << (mp.contains(2) ? "存在" : "不存在") << std::endl;
    // std::cout << "查找key=5: " << (mp.contains(5) ? "存在" : "不存在") << std::endl;
    return 0;
}