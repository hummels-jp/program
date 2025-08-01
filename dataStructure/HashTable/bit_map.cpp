#include <vector>
#include <iostream>
using namespace std;

class BitMap {
public:
    BitMap(size_t size) : bits((size + 31) / 32, 0), size_(size) {}

    void set(size_t pos) {
        if (pos >= size_) return;
        bits[pos / 32] |= (1U << (pos % 32));
    }

    bool test(size_t pos) const {
        if (pos >= size_) return false;
        return bits[pos / 32] & (1U << (pos % 32));
    }

private:
    vector<unsigned int> bits;
    size_t size_;
};

int main() {
    vector<int> data = {5, 2, 9, 1, 5, 6, 2, 9, 7};
    BitMap bm(100); // 假设数据范围在0~99

    cout << "去重后数据: ";
    for (int x : data) {
        if (!bm.test(x)) {
            cout << x << " ";
            bm.set(x);
        }
    }
    cout << endl;
    return 0;
}