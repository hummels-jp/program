#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

class ConsistentHashRing {
public:
    ConsistentHashRing(int virtual_nodes = 100)
        : virtual_nodes_per_physical(virtual_nodes) {}

    // add physical node
    void add_node(const string& node) {
        for (int i = 0; i < virtual_nodes_per_physical; ++i) {
            string vnode = node + "#" + to_string(i);
            size_t hash = hash_fn(vnode);
            ring[hash] = node;
        }
        physical_nodes.push_back(node);
    }

    // remove physical node
    void remove_node(const string& node) {
        for (int i = 0; i < virtual_nodes_per_physical; ++i) {
            string vnode = node + "#" + to_string(i);
            size_t hash = hash_fn(vnode);
            ring.erase(hash);
        }
        erase_physical_node(node);
    }

    // query the node
    string get_node(const string& key) const {
        if (ring.empty()) return "";
        size_t hash = hash_fn(key);
        auto it = ring.lower_bound(hash);
        if (it == ring.end()) it = ring.begin();
        return it->second;
    }

    // print the ring
    void print_ring() const {
        for (auto& [h, n] : ring) {
            cout << h << " => " << n << endl;
        }
    }

private:
    // 删除 physical_nodes 中的指定节点
    void erase_physical_node(const string& node) 
    {
        physical_nodes.erase(
            remove(physical_nodes.begin(), physical_nodes.end(), node),
            physical_nodes.end()
        );
    }


private:
    map<size_t, string> ring; // store the hash loop,key is the hash value of node, string is the node name
    vector<string> physical_nodes; // physical node 
    int virtual_nodes_per_physical; // one physical node correspond virtural node
    hash<string> hash_fn; // hash function, convert key to hash value
};

int main() {
    ConsistentHashRing ring(10);
    ring.add_node("NodeA");
    ring.add_node("NodeB");
    ring.add_node("NodeC");

    vector<string> keys = {"apple", "banana", "orange", "grape", "melon"};
    for (const auto& key : keys) {
        cout << key << " is mapped to " << ring.get_node(key) << endl;
    }

    cout << "Remove NodeB..." << endl;
    ring.remove_node("NodeB");
    for (const auto& key : keys) {
        cout << key << " is mapped to " << ring.get_node(key) << endl;
    }
    return 0;
}