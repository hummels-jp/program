#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
using namespace std;

template<typename K, typename V>
struct  HashNode
{
    /* data */
    K _key;
    V _value;

    HashNode(K key, V value)
        : _key(key)
        , _value(value)
    {

    }
};

template<typename K, typename V, typename Hash = std::hash<K>>
class MyUnorderedMap
{
private:
    static const size_t _default_bucket_count = 13; // default bucket count 
    vector<list<HashNode<K, V>>> _buckets; // container to store the hashnode
    size_t _size; // element count
    Hash _hash_func;

    // get the bucket index, by the hash 
    size_t get_index(const K& key) const
    {
        return _hash_func(key)%_buckets.size();
    }

public:
    // construct function
    MyUnorderedMap(int buckets_count = _default_bucket_count)
        :_buckets(buckets_count)
        , _size(0)
    {

    }

    size_t size()
    {
        return _size;
    }

    bool empty()
    {
        return _size == 0;
    }

    // override operator []
    V& operator[](const K& key)
    {
        size_t index = get_index(key);
        for (auto& node: _buckets[index])
        {
            if (node._key == key)
            {
                /* code */
                return node._value;
            }
        }
        _buckets[index].emplace_back(key, V());
        ++_size;

        return _buckets[index].back()._value;
        
    }

    // insert element
    void insert(const K& key, const V& value)
    {
        size_t index = get_index(key);

        for (auto& node : _buckets[index])
        {
            /* code */
            if (node._key==key)
            {
                /* code */
                node._value = value;
                return;
            }    
        }

        _buckets[index].emplace_back(key, value);
        ++_size;
    }

    // print 
    void print() const
    {
        for (size_t i = 0; i < _buckets.size(); i++)
        {
            /* code */
            for (const auto& node: _buckets[i])
            {
                /* code */
                cout << node._key << " : " << node._value << " | ";
            }
            
        }
        cout << endl;
    }

    // erase the element
    void erase(const K& key)
    {
        size_t index = get_index(key);
        for (auto it = _buckets[index].begin(); it != _buckets[index].end(); it++)
        {
            /* code */
            if (it->_key == key)
            {
                /* code */
                _buckets[index].erase(it);
                --_size;
                return;
            }
            
        }
        
    }

};

int main()
{
    MyUnorderedMap<string, int> ump;
    ump.insert("apple", 1);
    ump.insert("banana", 2);
    ump["orange"] = 3;
    ump["banana"] = 5;

    cout << "内容: ";
    ump.print();

    cout << "banana: " << ump["banana"] << endl;


    ump.erase("apple");
    cout << "删除 apple 后: ";
    ump.print();

    return 0;
}
