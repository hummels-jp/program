#include <iostream>
#include <vector>
#include <list>
#include <functional>
using namespace std;

// 哈希桶节点
template<typename K, typename V>
struct HashNode {
    K key;
    V value;
    HashNode(const K& k, const V& v) : key(k), value(v) {}
};

// 自定义 unordered_map
template<typename K, typename V, typename Hash = std::hash<K>>
class MyUnorderedMap {
private:
    static const size_t DEFAULT_BUCKETS = 16;
    std::vector<std::list<HashNode<K, V>>> buckets;
    size_t sz;
    Hash hash_func;

    size_t get_index(const K& key) const {
        return hash_func(key) % buckets.size();
    }

public:
    MyUnorderedMap(size_t bucket_count = DEFAULT_BUCKETS)
        : buckets(bucket_count), sz(0) {}

    size_t size() const { return sz; }
    bool empty() const { return sz == 0; }

    void insert(const K& key, const V& value) {
        size_t idx = get_index(key);
        for (auto& node : buckets[idx]) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }
        buckets[idx].emplace_back(key, value);
        ++sz;
    }

    bool contains(const K& key) const {
        size_t idx = get_index(key);
        for (const auto& node : buckets[idx]) {
            if (node.key == key) return true;
        }
        return false;
    }

    V& operator[](const K& key) {
        size_t idx = get_index(key);
        for (auto& node : buckets[idx]) {
            if (node.key == key) return node.value;
        }
        buckets[idx].emplace_back(key, V());
        ++sz;
        return buckets[idx].back().value;
    }

    void erase(const K& key) {
        size_t idx = get_index(key);
        for (auto it = buckets[idx].begin(); it != buckets[idx].end(); ++it) {
            if (it->key == key) {
                buckets[idx].erase(it);
                --sz;
                return;
            }
        }
    }

    void print() const {
        for (size_t i = 0; i < buckets.size(); ++i) {
            for (const auto& node : buckets[i]) {
                cout << node.key << ": " << node.value << " | ";
            }
        }
        cout << endl;
    }
};

int main() {
    MyUnorderedMap<string, int> ump;
    ump.insert("apple", 1);
    ump.insert("banana", 2);
    ump["orange"] = 3;
    ump["banana"] = 5;

    cout << "内容: ";
    ump.print();

    cout << "banana: " << ump["banana"] << endl;
    cout << "是否有 grape: " << (ump.contains("grape") ? "有" : "没有") << endl;

    ump.erase("apple");
    cout << "删除 apple 后: ";
    ump.print();

    return 0;
}