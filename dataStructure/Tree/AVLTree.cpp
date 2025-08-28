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
        if (node == nullptr)
        {
            /* code */
            return 0;
        }
        else
        {
            return node->height;
        }
        
    }

    int getBalance(AVLNode* node) {
        if (node == nullptr)
        {
            /* code */
            return 0;
        }
        else
        {
            return getHeight(node->left) - getHeight(node->right);
        }
        
    }

    // left rotate
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* t2 = y->left;

        y->left = x;
        x->right = t2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // right rotate
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* t2 = x->right;

        x->right = y;
        y->left = t2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return x;
    }


    // 
    AVLNode* insert(AVLNode* node, int val) {
        if (node == nullptr)
        {
            /* code */
            node = new AVLNode(val);
            return node;
        }

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
        else
        {
            return node;
        }

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        int balance = getBalance(node);
        
        // LL
        if (balance > 1 && val < node->left->val)
        {
            /* code */
            return rightRotate(node);
        }
        
        // RR
        else if (balance < -1 && val > node->right->val)
        {
            /* code */
            return leftRotate(node);
        }
        
        // LR
        else if (balance > 1 && val > node->left->val)
        {
            /* code */
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        // RL
        else if (balance < -1 && val < node->right->val)
        {
            /* code */
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

    AVLNode* minValueNode(AVLNode* node) 
    {

    }

    AVLNode* remove(AVLNode* node, int val) {
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
            // first delete node, after adjust the avl tree

            // only one child or no child
            if (node->left == nullptr || node->right == nullptr)
            {
                /* code */
                AVLNode* temp = nullptr;
                if (node->left != nullptr)
                {
                    /* code */
                    temp = node->left;
                }
                else if (node->right != nullptr)
                {
                    /* code */
                    temp = node->right;
                }
                delete node;
                return temp;
            }

            // two child, first delete high height child
            // left child is high
            if (getHeight(node->left) > getHeight(node->right))
            {
                /* code */
                AVLNode* pre = node->left;
                while (pre->right != nullptr)
                {
                    /* code */
                    pre = pre->right;
                }
                node->val = pre->val;
                node->left = remove(node->left, pre->val);
            }
            else
            {
                AVLNode* post = node->right;
                while (post->left != nullptr)
                {
                    /* code */
                    post = post->left;
                }

                node->val = post->val;
                node->right = remove(node->right, post->val);
                
            }
        }

        // update the height
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        int balance = getBalance(node);

        //LL
        if (balance > 1 && getBalance(node->left)>=0)
        {
            /* code */
            return rightRotate(node);
        }
        
        //RR
        else if (balance < -1 && getBalance(node->right) <=0)
        {
            /* code */
            return leftRotate(node);
        }
        
        //LR
        else if (balance > 1 && getBalance(node->left) < 0)
        {
            /* code */
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // RL
        else if (balance < -1 && getBalance(node->right)>0)
        {
            /* code */
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