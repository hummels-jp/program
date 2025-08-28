#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

// 求topk大值，使用小根堆
vector<int> topk_largest(const vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> min_heap;
    for (int num : nums) {
        if (min_heap.size() < k) {
            min_heap.push(num);
        } else if (num > min_heap.top()) {
            min_heap.pop();
            min_heap.push(num);
        }
    }
    vector<int> result;
    while (!min_heap.empty()) {
        result.push_back(min_heap.top());
        min_heap.pop();
    }
    // 可选：从小到大排序
    sort(result.begin(), result.end());
    return result;
}

int main() {
    vector<int> nums = {5, 2, 9, 1, 7, 6, 8, 3};
    int k = 3;
    vector<int> res = topk_largest(nums, k);
    cout << "Top " << k << " largest values: ";
    for (int x : res) cout << x << " ";
    cout << endl;
    return 0;
}