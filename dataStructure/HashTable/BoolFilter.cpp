#include <vector>
#include <string>
#include <functional>
#include <iostream>
using namespace std;

class BloomFilter {
public:
    // constructor
    BloomFilter(size_t size = 100, size_t hash_count=3)
        : _size(size)
        , _bits(size, false)
        , _hash_count(hash_count)
    {
    }

    // add element into bloomfilter
    void add(const string& s)
    {
        for (size_t i = 0; i < _hash_count; i++)
        {
            /* code */
            size_t hash = hash_i(s, i);
            size_t index = hash % _size;
            _bits[index] = true;
            
        }   
    }

    // whther the element is exist, exist is not 100 percent, not exist is 100 percent
    bool possibly_contains(const string& s) const {
        for (size_t i = 0; i < _hash_count; i++)
        {
            /* code */
            size_t hash = hash_i(s, i);
            size_t index = hash%_size;
            if (_bits[index] == false)
            {
                /* code */
                return false;
            }
        }

        return true;
        
    }

private:
    vector<bool> _bits; // bit array
    size_t _size; // size of bit array
    size_t _hash_count; // hash count

    // multiple hash
    size_t hash_i(const string& s, size_t i) const
    {
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