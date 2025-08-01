#include <vector>
#include <string>
#include <functional>
#include <iostream>
using namespace std;

class BloomFilter {
public:
    BloomFilter(size_t size, size_t hash_count)
        : bits(size, false), size_(size), hash_count_(hash_count) {}

    void add(const string& s) {
        for (size_t i = 0; i < hash_count_; ++i) {
            size_t hash = hash_i(s, i);
            bits[hash % size_] = true;
        }
    }

    bool possibly_contains(const string& s) const {
        for (size_t i = 0; i < hash_count_; ++i) {
            size_t hash = hash_i(s, i);
            if (!bits[hash % size_])
                return false;
        }
        return true;
    }

private:
    vector<bool> bits; 
    size_t size_;
    size_t hash_count_;

    // 简单多哈希函数实现
    size_t hash_i(const string& s, size_t i) const {
        return hash<string>{}(s) + i * 0x9e3779b9;
    }
};

int main() {
    BloomFilter bf(1000, 3);
    bf.add("apple");
    bf.add("banana");
    bf.add("orange");

    cout << bf.possibly_contains("apple") << endl;   // 1
    cout << bf.possibly_contains("banana") << endl;  // 1
    cout << bf.possibly_contains("grape") << endl;   // 0 (大概率)
    return 0;
}