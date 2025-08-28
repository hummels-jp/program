#include <iostream>
using namespace std;

// tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST() : root(nullptr) {}

    // 插入
    void insert(int val) {
        root = insert(root, val);
    }

    // 查找
    bool search(int val) {
        return search(root, val);
    }

    // 删除
    void remove(int val) {
        root = remove(root, val);
    }

    // 中序遍历
    void inorder() {
        inorder(root);
        cout << endl;
    }

private:
    TreeNode* root;

    // 
    TreeNode* insert(TreeNode* node, int val) {
        if (node == nullptr)
        {
            /* code */
            node = new TreeNode(val);
            return node;
        }

        //
        if (val < node->val)
        {
            /* code */
            node->left = insert(node->left, val);
        }
        else if (val > node->val)
        {
            /* code */
            node->right = insert(node->right, val);
        }

        return node;    
    }

    bool search(TreeNode* node, int val) {
        if (node == nullptr)
        {
            /* code */
            return false;
        }

        if (node->val == val)
        {
            /* code */
            return true;
        }
        else if (val < node->val)
        {
            /* code */
            return search(node->left, val);
        }
        else 
        {
            return search(node->right, val);
        }
        
        
        
    }

    TreeNode* remove(TreeNode* node, int val) {
        if (node == nullptr)
        {
            /* code */
            return nullptr;
        }

        if (val < node->val)
        {
            /* code */
            node->left = remove(node->left, val);
        }
        else if (val > node->val)
        {
            /* code */
            node->right = remove(node->right, val);
        }
        else
        {
            // no left child
            if (node->left == nullptr)
            {
                /* code */
                TreeNode* right = node->right;
                delete node;
                return right;
            }

            // no right child
            if (node->right == nullptr)
            {
                /* code */
                TreeNode* left = node->left;
                delete node;
                return left;
            }

            // left child and right child both exist, find the smallest in the right child
            TreeNode* min_node = node->right;
            while (min_node->left !=nullptr)
            {
                /* code */
                min_node = min_node->left;
            }
            node->val = min_node->val;
            node->right = remove(node->right, min_node->val);   
        }

        return node;   
    }

    // visit the bst by mid order
    void inorder(TreeNode* node) {
        if (node == nullptr)
        {
            /* code */
            return;
        }

        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
        
    }
};

int main() {
    BST tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    cout << "Inorder: ";
    tree.inorder();

    cout << "Search 4: " << tree.search(4) << endl;
    cout << "Search 10: " << tree.search(10) << endl;

    tree.remove(3);
    cout << "After remove 3, Inorder: ";
    tree.inorder();

    return 0;
}