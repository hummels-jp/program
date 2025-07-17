#include <iostream>
using namespace std;

// 节点定义
template<typename K, typename V>
struct BSTNode {
    K key;
    V value;
    BSTNode* left;
    BSTNode* right;
    BSTNode(const K& k, const V& v)
        : key(k), value(v), left(nullptr), right(nullptr) {}
};

// Map实现
template<typename K, typename V>
class MyMap {
private:
    BSTNode<K, V>* root;

    void clear(BSTNode<K, V>* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    //
    BSTNode<K, V>* insert(BSTNode<K, V>* node, const K& key, const V& value) {
        if (!node) return new BSTNode<K, V>(key, value);
        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else
            node->value = value; // 覆盖已有key
        return node;
    }

    BSTNode<K, V>* find(BSTNode<K, V>* node, const K& key) const {
        if (!node) return nullptr;
        if (key < node->key) return find(node->left, key);
        if (key > node->key) return find(node->right, key);
        return node;
    }

    void inorder(BSTNode<K, V>* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->key << ": " << node->value << endl;
        inorder(node->right);
    }

public:
    MyMap() : root(nullptr) {}
    ~MyMap() { clear(root); }

    void insert(const K& key, const V& value) {
        root = insert(root, key, value);
    }

    bool contains(const K& key) const {
        return find(root, key) != nullptr;
    }

    V& operator[](const K& key) {
        BSTNode<K, V>* node = root;
        BSTNode<K, V>* parent = nullptr;
        while (node) {
            parent = node;
            if (key < node->key) node = node->left;
            else if (key > node->key) node = node->right;
            else return node->value;
        }
        // 新建节点，默认值初始化
        if (!root) {
            root = new BSTNode<K, V>(key, V());
            return root->value;
        }
        if (key < parent->key) {
            parent->left = new BSTNode<K, V>(key, V());
            return parent->left->value;
        } else {
            parent->right = new BSTNode<K, V>(key, V());
            return parent->right->value;
        }
    }

    void print_inorder() const {
        inorder(root);
    }
};

int main() {
    MyMap<int, string> mp;
    mp.insert(3, "three");
    mp.insert(1, "one");
    mp.insert(2, "two");
    mp[4] = "four";
    mp[2] = "TWO";

    cout << "中序遍历输出Map内容：" << endl;
    mp.print_inorder();

    cout << "查找key=2: " << (mp.contains(2) ? "存在" : "不存在") << endl;
    cout << "查找key=5: " << (mp.contains(5) ? "存在" : "不存在") << endl;
    return 0;
}