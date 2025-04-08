#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // 实现2个数相加，返回一个链表
    // 1. 先创建一个虚拟头结点，方便处理链表的头结点
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummyHead = new ListNode(0);
        ListNode* current = dummyHead;
        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry != 0) 
        {
            int sum = carry;
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }
            carry = sum / 10;
            current->next = new ListNode(sum % 10);
            current = current->next;
        }

        return dummyHead->next;
    }
};

// Helper function to create a linked list from an array
ListNode* createList(const vector<int>& nums) {
    ListNode* dummyHead = new ListNode(0);
    ListNode* current = dummyHead;
    for (int num : nums) {
        current->next = new ListNode(num);
        current = current->next;
    }
    return dummyHead->next;
}

// Helper function to print a linked list
void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val;
        if (head->next != nullptr) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

ListNode* add_two_number_hqq(ListNode* l1, ListNode* l2)
{
    ListNode* result = nullptr; // 存储最终结果链表
    ListNode* head = nullptr; // 存储最终结果链表的起始节点
    ListNode* next = nullptr; // 下一个节点
    int carry = 0; // 进位值

    // 共同的部分
    while (l1 != nullptr && l2 !=nullptr)
    {
        int value = l1->val + l2->val + carry;
        ListNode* new_node = new ListNode();
        if (value >=10)
        {
            /* code */
            value = value%10;
            carry =1;
            // 创建新节点
            new_node->val = value;
        }
        else
        {
            carry = 0;
            new_node->val = value;
        }

        if (head == nullptr)
        {
            /* code */
            head = new_node;
            next = head;

        }
        else
        {
            next->next= new_node;
            next = next->next;
        }
        
        l1 = l1->next;
        l2 = l2->next;
        /* code */
    }

    // L1 多出的部分
    while (l1!=nullptr)
    {
        /* code */
        int value = l1->val + carry;
        ListNode* new_node = new ListNode();
        if (value >=10)
        {
            /* code */
            value = value%10;
            carry =1;
            // 创建新节点
            new_node->val = value;
        }
        else
        {
            carry = 0;
            new_node->val = value;
        }

        if (next == nullptr)
        {
            /* code */
            head->next = new_node;
            next = new_node;

        }
        else
        {
            next->next= new_node;
            next = next->next;
        }
        
        l1 = l1->next;
    }

    // L2 多出的部分
    while (l2!=nullptr)
    {
        /* code */
        int value = l2->val + carry;
        ListNode* new_node = new ListNode();
        if (value >=10)
        {
            /* code */
            value = value%10;
            carry =1;
            // 创建新节点
            new_node->val = value;
        }
        else
        {
            carry = 0;
            new_node->val = value;
        }

        if (next == nullptr)
        {
            /* code */
            head->next = new_node;
            next = new_node;

        }
        else
        {
            next->next= new_node;
            next = next->next;
        }
        
        l2 = l2->next;
    }

    // 最后一个进位
    if (carry==1)
    {
        /* code */
        ListNode* new_node = new ListNode(1);
        next->next= new_node;
    }
    
    return head;
}

int main() {
    Solution solution;

    // Example 1
    vector<int> nums1 = {2, 4, 3};
    vector<int> nums2 = {5, 6, 4};
    ListNode* l1 = createList(nums1);
    ListNode* l2 = createList(nums2);
    // ListNode* result = solution.addTwoNumbers(l1, l2);
    // printList(result);

    ListNode* result_hqq = add_two_number_hqq(l1, l2);
    printList(result_hqq);

    // Example 2
    // vector<int> nums3 = {0};
    // vector<int> nums4 = {0};
    // ListNode* l3 = createList(nums3);
    // ListNode* l4 = createList(nums4);
    // result = solution.addTwoNumbers(l3, l4);
    // printList(result);

    return 0;
}