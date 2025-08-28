#include <iostream>
using namespace std;

template<typename T>
struct TreeNode
{
    /* data */
    T _data;
    TreeNode<T>* _left;
    TreeNode<T>* _right;

    TreeNode(T data = T())
        : _data(data)
        , _left(nullptr)
        , _right(nullptr)
    {

    }

};

template <typename T>
class TemplateBinarySearchTree
{
private:
    /* data */
    TreeNode<T>* _root;
public:
    // insert node
    void insert(const T& val)
    {
        if (_root == nullptr)
        {
            /* code */
            _root = new TreeNode(val);
            return;
        }

        TreeNode<T>* cur = _root;
        TreeNode<T>* parent = nullptr;

        // find the insert address
        while (cur != nullptr)
        {
            parent = cur;
            /* code */
            if (val < cur->_data)
            {
                /* code */
                
                cur = cur->_left;
            }
            else if (val > cur->_data)
            {
                /* code */
                cur = cur->_right;
            }
            else
            {
                return;
            }            
        }

        if (val < parent->_data)
        {
            /* code */
            parent->_left = new TreeNode(val);
        }
        else if (val > parent->_data)
        {
            /* code */
            parent->_right = new TreeNode(val);
        }
        else
        {
            return;
        }  
    }
};



