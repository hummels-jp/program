#include <vector>
#include <optional>
#include <iostream>
using namespace std;

class LinearHashTable {
public:
    LinearHashTable(size_t capacity) : table(capacity), size_(0) {}

    bool insert(int key, int value) {
        size_t idx = hash(key);
        size_t start = idx;
        do {
            if (!table[idx].has_value() || table[idx]->deleted) {
                table[idx] = Entry{key, value, false};
                ++size_;
                return true;
            }
            if (table[idx]->key == key && !table[idx]->deleted) {
                table[idx]->value = value; // update
                return true;
            }
            idx = (idx + 1) % table.size();
        } while (idx != start);
        return false; // table full
    }

    bool erase(int key) {
        size_t idx = hash(key);
        size_t start = idx;
        do {
            if (!table[idx].has_value()) return false;
            if (table[idx]->key == key && !table[idx]->deleted) {
                table[idx]->deleted = true;
                --size_;
                return true;
            }
            idx = (idx + 1) % table.size();
        } while (idx != start);
        return false;
    }

    optional<int> find(int key) const {
        size_t idx = hash(key);
        size_t start = idx;
        do {
            if (!table[idx].has_value()) return nullopt;
            if (table[idx]->key == key && !table[idx]->deleted)
                return table[idx]->value;
            idx = (idx + 1) % table.size();
        } while (idx != start);
        return nullopt;
    }

    size_t size() const { return size_; }

private:
    struct Entry {
        int key;
        int value;
        bool deleted;
    };
    vector<optional<Entry>> table;
    size_t size_;

    size_t hash(int key) const { return key % table.size(); }
};

int main() {
    LinearHashTable ht(7);
    ht.insert(1, 100);
    ht.insert(8, 200); // 8 % 7 == 1, collision
    ht.insert(15, 300); // 15 % 7 == 1, collision
    cout << ht.find(1).value_or(-1) << endl;   // 100
    cout << ht.find(8).value_or(-1) << endl;   // 200
    cout << ht.find(15).value_or(-1) << endl;  // 300
    ht.erase(8);
    cout << ht.find(8).value_or(-1) << endl;   // -1
    cout << "size: " << ht.size() << endl;     // 2
    return 0;
}