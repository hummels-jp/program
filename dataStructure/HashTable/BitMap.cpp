#include <vector>
#include <iostream>
using namespace std;

class BitMap {
public:
    BitMap(size_t size=100): _bits(size/32 + 1), _size(size)
    {

    }

    // set the bit into true
    void set(size_t pos)
    {
        if (pos > _size)
        {
            /* code */
            return;
        }
        else
        {
            int index = pos/32;
            int offset = pos % 32;
            _bits[index] = _bits[index] | (1 << offset);
        }
        
    }

    // get the bit value
    bool test(size_t pos) const
    {
        if (pos >= _size)
        {
            /* code */
            return false;
        }
        else
        {
            int index = pos/32;
            int offset = pos % 32;
            return _bits[index] & (1 << offset);
        }
        
    }

private:
    vector<unsigned int> _bits; // bits to store bit
    size_t _size; // the length of bits
};

int main() {
    vector<int> data = {5, 2, 9, 1, 5, 6, 2, 9, 7};
    BitMap bm(100); // 假设数据范围在0~99

    cout << "去重后数据: ";
    for (int x : data) {
        if (bm.test(x)==false) {
            cout << x << " ";
            bm.set(x);
        }
    }
    cout << endl;
    return 0;
}