#include <iostream>
#include <memory>

class Node {
public:
    int value;
    std::shared_ptr<Node> next; // Shared ownership of the next node
    std::weak_ptr<Node> prev;  // Weak reference to the previous node

    Node(int val) : value(val) {
        std::cout << "Node created with value: " << value << std::endl;
    }

    ~Node() {
        std::cout << "Node destroyed with value: " << value << std::endl;
    }
};

int main() {
    // Create two nodes
    std::shared_ptr<Node> node1 = std::make_shared<Node>(1);
    std::shared_ptr<Node> node2 = std::make_shared<Node>(2);

    // Establish links between nodes
    node1->next = node2;       // node1 owns node2
    node2->prev = node1;       // node2 has a weak reference to node1

    // Access node2 from node1
    if (auto nextNode = node1->next) {
        std::cout << "Node1's next value: " << nextNode->value << std::endl;
    }

    // Access node1 from node2 using weak_ptr
    if (auto prevNode = node2->prev.lock()) { // Convert weak_ptr to shared_ptr
        std::cout << "Node2's previous value: " << prevNode->value << std::endl;
    }

    // Nodes will be automatically destroyed when shared_ptr goes out of scope
    return 0;
}