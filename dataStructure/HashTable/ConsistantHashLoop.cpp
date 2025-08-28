#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

class ConsistentHashRing {
public:
    // construction function
    ConsistentHashRing(int virual_nodes_per_physical = 100): _virtual_nodes_per_physical(virual_nodes_per_physical)
    {

    }

    // add physical node
    void add_node(const string& node) {

        // first add the virutal node
        for (int i = 0; i < _virtual_nodes_per_physical; i++)
        {
            /* code */
            string vnode = node + "#" + to_string(i);
            size_t hash = _hash_fn(vnode);
            _ring[hash] = node;
        }

        _physical_nodes.push_back(node);
    }

        // remove physical node
    void remove_node(const string& node) {
        for (int i = 0; i < _virtual_nodes_per_physical; i++)
        {
            /* code */
            string vnode = node + "#" + to_string(i);
            size_t hash = _hash_fn(vnode);
            _ring.erase(hash);
        }

        erase_physical_node(node);
        
    }

    // query the node
    string get_node(const string& key) const {
        if (_ring.empty() == true) 
        {
            return "";
        }

        size_t hash = _hash_fn(key);
        auto it = _ring.lower_bound(hash);

        if (it == _ring.end())
        {
            /* code */
            it = _ring.begin();
        }

        return it->second;
        
        
    }


    // print the ring
    void print_ring() const {
        for (auto& [h, n] : _ring) {
            cout << h << " => " << n << endl;
        }
    }

private:
        // 删除 physical_nodes 中的指定节点
    void erase_physical_node(const string& node) 
    {
        _physical_nodes.erase(remove(_physical_nodes.begin(), _physical_nodes.end(), node)
        , _physical_nodes.end());
    }



private:
    map<size_t, string> _ring;
    vector<string> _physical_nodes;
    int _virtual_nodes_per_physical;
    hash<string> _hash_fn;

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