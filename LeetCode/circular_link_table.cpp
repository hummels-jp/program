#include <iostream>
#include <unordered_set>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 使用快慢指针法检测链表是否有环，并找到环的入口节点
// 时间复杂度 O(n)，空间复杂度 O(1)
ListNode* detectCycle(ListNode* head) {
    if (!head || !head->next) return nullptr;

    ListNode* slow = head;
    ListNode* fast = head;

    // Detect if a cycle exists
    while (fast && fast->next) 
    {
        slow = slow->next;
        fast = fast->next->next;
        // 找到相遇点
        if (slow == fast) {
            // Cycle detected, find the entry point
            ListNode* entry = head;
            while (entry != slow) {
                entry = entry->next;
                slow = slow->next;
            }
            return entry;
        }
    }

    return nullptr; // No cycle
}

int main() {
    // Example usage
    ListNode* head = new ListNode(3);
    head->next = new ListNode(2);
    head->next->next = new ListNode(0);
    head->next->next->next = new ListNode(-4);
    head->next->next->next->next = head->next; // Create a cycle

    ListNode* cycleNode = detectCycle(head);
    if (cycleNode) {
        std::cout << "Cycle detected at node with value: " << cycleNode->val << std::endl;
    } else {
        std::cout << "No cycle detected." << std::endl;
    }

    // Free allocated memory (ignoring cycle for simplicity)
    delete head->next->next->next;
    delete head->next->next;
    delete head->next;
    delete head;

    return 0;
}