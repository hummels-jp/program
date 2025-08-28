#include <iostream>
#include <algorithm>
using namespace std;

struct AVLNode {
    int val;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int v) : val(v), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLTree() : root(nullptr) {}

    // 插入节点
    void insert(int val) {
        root = insert(root, val);
    }

    // 中序遍历
    void inorder() {
        inorder(root);
        cout << endl;
    }

    // 获取树高
    int getHeight() {
        return getHeight(root);
    }

    // 删除节点接口
    void remove(int val) {
        root = remove(root, val);
    }

private:
    AVLNode* root;

    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    AVLNode* insert(AVLNode* node, int val) {
        if (!node) return new AVLNode(val);
        if (val < node->val)
            node->left = insert(node->left, val);
        else if (val > node->val)
            node->right = insert(node->right, val);
        else
            return node; // 不允许重复

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // LL型
        if (balance > 1 && val < node->left->val)
            return rightRotate(node);
        // RR型
        if (balance < -1 && val > node->right->val)
            return leftRotate(node);
        // LR型
        if (balance > 1 && val > node->left->val) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // RL型
        if (balance < -1 && val < node->right->val) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void inorder(AVLNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    AVLNode* remove(AVLNode* node, int val) {
        if (!node) return nullptr;
        if (val < node->val)
            node->left = remove(node->left, val);
        else if (val > node->val)
            node->right = remove(node->right, val);
        else {
            // 只有一个子节点或无子节点
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            // 有两个子节点，找右子树最小节点替换
            AVLNode* temp = minValueNode(node->right);
            node->val = temp->val;
            node->right = remove(node->right, temp->val);
        }

        // 更新高度
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // LL型
        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);
        // LR型
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // RR型
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);
        // RL型
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }


};

int main() {
    AVLTree tree;
    int arr[] = {10, 20, 30, 40, 50, 25};
    for (int v : arr) tree.insert(v);

    cout << "Inorder traversal: ";
    tree.inorder();

    cout << "Tree height: " << tree.getHeight() << endl;

    // 测试删除
    tree.remove(40);
    cout << "After remove 40, inorder: ";
    tree.inorder();
    cout << "Tree height: " << tree.getHeight() << endl;

    return 0;
}