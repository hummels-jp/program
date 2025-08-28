#include <iostream>
#include <queue>
#include <stack>
using namespace std;

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

        // visit the three by level order
    void level_order()
    {
        if (root == nullptr)
        {
            /* code */
            return;
        }

        queue<TreeNode*> q;
        q.push(root);

        while (q.empty() == false)
        {
            /* code */
            TreeNode * node = q.front();
            q.pop();
            cout << node->val << " ";

            if (node->left != nullptr)
            {
                /* code */
                q.push(node->left);
            }
            if (node->right !=nullptr)
            {
                /* code */
                q.push(node->right);
            } 
        }

        cout << endl;
        
        
    }



private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, int val) {
        if (!node) return new TreeNode(val);
        if (val < node->val) node->left = insert(node->left, val);
        else if (val > node->val) node->right = insert(node->right, val);
        return node;
    }

    bool search(TreeNode* node, int val) {
        if (!node) return false;
        if (val == node->val) return true;
        if (val < node->val) return search(node->left, val);
        else return search(node->right, val);
    }

    TreeNode* remove(TreeNode* node, int val) {
        if (!node) return nullptr;
        if (val < node->val) node->left = remove(node->left, val);
        else if (val > node->val) node->right = remove(node->right, val);
        else {
            if (!node->left) {
                TreeNode* right = node->right;
                delete node;
                return right;
            }
            if (!node->right) {
                TreeNode* left = node->left;
                delete node;
                return left;
            }
            // 两个孩子，找右子树最小节点替换
            TreeNode* minNode = node->right;
            while (minNode->left) minNode = minNode->left;
            node->val = minNode->val;
            node->right = remove(node->right, minNode->val);
        }
        return node;
    }

    // mid order
    void inorder(TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    }

    // get the depth of binary search tree
    int max_depth(TreeNode* node)
    {
        if (node == nullptr)
        {
            /* code */
            return 0;
        }

        int left_depth = max_depth(node->left);
        int right_depth = max_depth(node->right);

        return max(left_depth, right_depth) + 1;
        
    }

    // get the node count
    int count(TreeNode* node)
    {
        if (node == nullptr)
        {
            /* code */
            return 0;
        }

        int left_count = count(node->left);
        int right_count = count(node->right);

        return 1 + left_count + right_count;
        
    }

    // not recursive pre order
    void preorder_iter()
    {
        if (root == nullptr)
        {
            /* code */
            return;
        }

        stack<TreeNode*> st;
        st.push(root);
        while (st.empty() == false)
        {
            /* code */
            TreeNode* node = st.top();
            st.pop();
            cout << node->val << " ";

            // first vist left,  last insert into stack
            st.push(node->right);
            st.push(node->left);
        }

        cout << endl;
    }

    // no recursive mid order
    void midorder_iter()
    {
        stack<TreeNode*> st;
        TreeNode* cur = root;

        // first inset the left child
        while (cur != nullptr)
        {
            /* code */
            st.push(cur);
            cur = cur->left;
        }

        while (st.empty()== false)
        {
            /* code */
            TreeNode* top = st.top();
            st.pop();
            cout << top->val << endl;

            cur = top->right;
            while (cur!=nullptr)
            {
                /* code */
                st.push(cur);
                cur = cur->left;
            }
            
        }

        cout << endl;
    }

    // post order
    void post_order()
    {
        if (root == nullptr)
        {
            /* code */
            return;
        }

        stack<TreeNode*> st1;
        stack<TreeNode*> st2;
        st1.push(root);

        while (st1.empty() == false)
        {
            /* code */
            TreeNode* cur = st1.top();
            st1.pop();

            st2.push(cur);

            if (cur->left!=nullptr)
            {
                /* code */
                st1.push(cur->left);
            }

            if (cur->right != nullptr)
            {
                /* code */
                st1.push(cur->right);
            }  
        }

        while (st2.empty() == false)
        {
            /* code */
            cout << st2.top()->val << " ";
            st2.pop();
        }
        cout << endl;  
    }

    void range_search(TreeNode* node, int low, int high)
    {
        if (node == nullptr)
        {
            /* code */
            return;
        }

        // l
        if (node->val > low)
        {
            /* code */
            range_search(node->left, low, high);
        }
        
        // v
        if (node->val >= low && node->val <=high)
        {
            /* code */
            cout << node->val << " ";
        }
        
        // r
        if (node->val < high)
        {
            /* code */
            range_search(node->right, low, high);
        }
        
        
    }

    // wheather is a bst tree, wrong, only compare the local value, not the whole value
    bool is_bst(TreeNode* node)
    {
        if (node == nullptr)
        {
            /* code */
            return true;
        }


        // v
        if (node->left != nullptr && node->val < node->left->val)
        {
            /* code */
            return false;
        }

        if (node->right !=nullptr && node->val > node->right->val)
        {
            /* code */
            return false;
        }

        if (is_bst(node->left) == false)
        {
            /* code */
            return false;
        }
        
        return is_bst(node->right);
    }

    // bst tree, mid order is an ascending array
    bool is_bst2(TreeNode* cur, TreeNode* & pre)
    {
        if (cur == nullptr)
        {
            /* code */
            return true;
        }

        // L
        if (is_bst2(cur->left, pre) == false)
        {
            /* code */
            return false;
        }

        // V
        if (pre!=nullptr)
        {
            /* code */
            if (cur->val < pre->val)
            {
                /* code */
                return false;
            }
            
        }
        pre = cur;
        
    
        // R
        return is_bst2(cur->right, pre);
        
    }

    bool is_sub_tree(TreeNode* parent, TreeNode* child)
    {
        if (parent == nullptr && child == nullptr)
        {
            /* code */
            return true;
        }

        if (parent == nullptr)
        {
            /* code */
            return false;
        }

        if (child == nullptr)
        {
            /* code */
            return true;
        }

        if (is_sub_tree(parent->left, child->left) == false)
        {
            /* code */
            return false;
        }

        return is_sub_tree(parent->right, child->right);  
    }

    TreeNode* get_LCA(TreeNode* node, int v1, int v2)
    {
        if (node == nullptr)
        {
            /* code */
            return nullptr;
        }

        // L
        if (node->val > v2)
        {
            /* code */
            return get_LCA(node->left, v1, v2);
        }
        
        
        // V
        if (node->val > v1 && node->val < v2)
        {
            /* code */
            return node;
        }
        
        // R
        if (node->val < v1)
        {
            /* code */
            return get_LCA(node->right, v1, v2);
        }
        
        
    }

    // flip the left child and right child
    void mirror_flip(TreeNode* node)
    {
        if (node == nullptr)
        {
            /* code */
            return;
        }

        // V
        TreeNode* temp = node->left;
        node->left = node->right;
        node->right = temp;

        // L
        mirror_flip(node->left);
        // R
        mirror_flip(node->right);
        
    }

    // initial value: root.left, root.right
    bool mirror_symmetric(TreeNode* node1, TreeNode* node2)
    {
        if (node1 == nullptr && node2 == nullptr)
        {
            /* code */
            return true;
        }

        if (node1 == nullptr || node2 == nullptr)
        {
            /* code */
            return false;
        }

        if (node1->val != node2->val)
        {
            /* code */
            return false;
        }

        return (mirror_symmetric(node1->left, node2->right) && mirror_symmetric(node1->right, node2->left)); 
    }

    bool is_balance()
    {

    }

    // 
    int is_balance_02(TreeNode* node, int level, bool& flag)
    {
        if (node == nullptr)
        {
            /* code */
            return level;
        }

        int left = is_balance_02(node->left, level + 1, flag);
        if (flag == false)
        {
            /* code */
            return left;
        }

        int right = is_balance_02(node->right, level + 1, flag);
        if (flag == false)
        {
            /* code */
            return right;
        }

        if (abs(left - right) > 1)
        {
            /* code */
            flag = false;
        }
        
        return max(left, right);
        
        
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