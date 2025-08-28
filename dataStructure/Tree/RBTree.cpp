#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct RBNode {

    int _val;
    RBNode* _left;
    RBNode* _right;
    RBNode* _parent;
    Color _color;

    RBNode(int val =0, RBNode* left = nullptr, RBNode* right = nullptr, RBNode* parent = nullptr, Color color = BLACK)
        : _val(val)
        , _left(left)
        , _right(right)
        , _parent(parent)
        , _color(color)

    {

    }
};

class RBTree {
public:
    RBTree() : root(nullptr) {}

    // 左旋转
    void leftRotate(RBNode* x) {
        RBNode* y = x->_right;
        RBNode* T2 = y->_left;

        if (y == nullptr)
        {
            /* code */
            return;
        }

        // 0
        x->_right = T2;

        // 1
        if (T2 != nullptr)
        {
            /* code */
            T2->_parent = x;
        }

        // 2
        y->_parent = x->_parent;

        // 3 
        if (x->_parent == nullptr)
        {
            /* code */
            root = y;
        }
        else if (x->_parent->_left == x)
        {
            /* code */
            x->_parent->_left = y;
        }
        else if (x->_parent->_right == x)
        {
            /* code */
            x->_parent->_right = y;
        }
        
        // 4
        y->_left = x;

        // 5
        x->_parent = y;

    }

    // 右旋转
    void rightRotate(RBNode* y) {

    }

    // 简单插入（不修正红黑性质，仅用于测试旋转）
    RBNode* insert(int val) {
        RBNode* node = new RBNode(val);
        if (!root) {
            node->color = BLACK;
            root = node;
            return node;
        }
        RBNode* cur = root;
        RBNode* parent = nullptr;
        while (cur) {
            parent = cur;
            if (val < cur->val)
                cur = cur->left;
            else
                cur = cur->right;
        }
        node->parent = parent;
        if (val < parent->val)
            parent->left = node;
        else
            parent->right = node;
        return node;
    }

    // 中序遍历
    void inorder() {
        inorder(root);
        cout << endl;
    }

private:
    RBNode* root;

    void inorder(RBNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->val << "(" << (node->color == RED ? "R" : "B") << ") ";
        inorder(node->right);
    }
};

int main() {
    RBTree tree;
    // 插入节点
    RBNode* n10 = tree.insert(10);
    RBNode* n20 = tree.insert(20);
    RBNode* n30 = tree.insert(30);

    cout << "Before leftRotate:" << endl;
    tree.inorder();

    // 对10节点做左旋
    tree.leftRotate(n10);

    cout << "After leftRotate(10):" << endl;
    tree.inorder();

    // 对20节点做右旋
    tree.rightRotate(n20);

    cout << "After rightRotate(20):" << endl;
    tree.inorder();

    return 0;
}