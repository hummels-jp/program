#include <iostream>
#include <unordered_set>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* getIntersectionNode(ListNode* head1, ListNode* head2) {
    if (!head1 || !head2) return nullptr;

    ListNode* a = head1;
    ListNode* b = head2;

    // Traverse both lists. When one pointer reaches the end, switch to the other list's head.
    while (a != b) {
        a = a ? a->next : head2;
        b = b ? b->next : head1;
    }

    return a; // Either the intersection node or nullptr if no intersection.
}

int main() {
    // Example usage
    ListNode* common = new ListNode(8);
    common->next = new ListNode(10);

    ListNode* head1 = new ListNode(3);
    head1->next = new ListNode(6);
    head1->next->next = common;

    ListNode* head2 = new ListNode(9);
    head2->next = common;

    ListNode* intersection = getIntersectionNode(head1, head2);
    if (intersection) {
        std::cout << "Intersection at node with value: " << intersection->val << std::endl;
    } else {
        std::cout << "No intersection." << std::endl;
    }

    // Clean up memory (not strictly necessary for this example, but good practice)
    delete head1->next;
    delete head1;
    delete head2;
    delete common->next;
    delete common;

    return 0;
}