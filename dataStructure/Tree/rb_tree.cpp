#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct RBNode {
    int val;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    RBNode(int v) : val(v), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
public:
    RBTree() : root(nullptr) {}

    // 左旋转
    void leftRotate(RBNode* x) {
        RBNode* y = x->right;
        if (!y) return;
        x->right = y->left;

        if (y->left)
            y->left->parent = x;

        y->parent = x->parent;
        
        if (!x->parent)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // 右旋转
    void rightRotate(RBNode* y) {
        RBNode* x = y->left;
        if (!x) return;
        y->left = x->right;
        if (x->right)
            x->right->parent = y;
        x->parent = y->parent;
        if (!y->parent)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        x->right = y;
        y->parent = x;
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