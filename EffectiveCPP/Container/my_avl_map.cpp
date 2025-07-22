#include <iostream>
#include <algorithm>
using namespace std;

// AVL树节点定义
template<typename K, typename V>
struct AVLNode {
    K key;
    V value;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(const K& k, const V& v)
        : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
};

// AVL Map实现
template<typename K, typename V>
class AVLMap {
private:
    AVLNode<K, V>* root;

    int height(AVLNode<K, V>* node) const {
        return node ? node->height : 0;
    }

    int balance_factor(AVLNode<K, V>* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void update_height(AVLNode<K, V>* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    // 右旋
    AVLNode<K, V>* rotate_right(AVLNode<K, V>* y) {
        AVLNode<K, V>* x = y->left;
        AVLNode<K, V>* T2 = x->right;
        x->right = y;
        y->left = T2;
        update_height(y);
        update_height(x);
        return x;
    }

    // 左旋
    AVLNode<K, V>* rotate_left(AVLNode<K, V>* x) {
        AVLNode<K, V>* y = x->right;
        AVLNode<K, V>* T2 = y->left;
        y->left = x;
        x->right = T2;
        update_height(x);
        update_height(y);
        return y;
    }

    // 平衡
    AVLNode<K, V>* balance(AVLNode<K, V>* node) {
        update_height(node);
        int bf = balance_factor(node);
        if (bf > 1) {
            if (balance_factor(node->left) < 0)
                node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        if (bf < -1) {
            if (balance_factor(node->right) > 0)
                node->right = rotate_right(node->right);
            return rotate_left(node);
        }
        return node;
    }

    AVLNode<K, V>* insert(AVLNode<K, V>* node, const K& key, const V& value) {
        if (!node) return new AVLNode<K, V>(key, value);
        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else
            node->value = value; // 覆盖
        return balance(node);
    }

    AVLNode<K, V>* find(AVLNode<K, V>* node, const K& key) const {
        if (!node) return nullptr;
        if (key < node->key) return find(node->left, key);
        if (key > node->key) return find(node->right, key);
        return node;
    }

    void clear(AVLNode<K, V>* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void inorder(AVLNode<K, V>* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->key << ": " << node->value << endl;
        inorder(node->right);
    }

public:
    AVLMap() : root(nullptr) {}
    ~AVLMap() { clear(root); }

    void insert(const K& key, const V& value) {
        root = insert(root, key, value);
    }

    bool contains(const K& key) const {
        return find(root, key) != nullptr;
    }

    V& operator[](const K& key) {
        AVLNode<K, V>* node = root;
        AVLNode<K, V>* parent = nullptr;
        while (node) {
            parent = node;
            if (key < node->key) node = node->left;
            else if (key > node->key) node = node->right;
            else return node->value;
        }
        // 插入新节点
        if (!root) {
            root = new AVLNode<K, V>(key, V());
            return root->value;
        }
        if (key < parent->key) {
            parent->left = new AVLNode<K, V>(key, V());
            root = balance(root);
            return parent->left->value;
        } else {
            parent->right = new AVLNode<K, V>(key, V());
            root = balance(root);
            return parent->right->value;
        }
    }

    void print_inorder() const {
        inorder(root);
    }
};

int main() {
    AVLMap<int, std::string> mp;
    mp.insert(3, "three");
    mp.insert(1, "one");
    mp.insert(2, "two");
    mp[4] = "four";
    mp[2] = "TWO";

    std::cout << "中序遍历输出AVLMap内容：" << std::endl;
    mp.print_inorder();

    std::cout << "查找key=2: " << (mp.contains(2) ? "存在" : "不存在") << std::endl;
    std::cout << "查找key=5: " << (mp.contains(5) ? "存在" : "不存在") << std::endl;
    return 0;
}