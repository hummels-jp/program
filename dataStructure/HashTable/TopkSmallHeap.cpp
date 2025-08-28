#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

// 求topk大值，使用小根堆
vector<int> topk_largest(const vector<int>& nums, int k) {
    // create min heap
    priority_queue<int, vector<int>, greater<int>> min_heap;
    for (int num: nums)
    {
        /* code */
        if (min_heap.size() < k)
        {
            /* code */
            min_heap.push(num);
        }
        else if (num > min_heap.top())
        {
            /* code */
            min_heap.pop();
            min_heap.push(num);
        }
    }

    vector<int> result;
    while (min_heap.empty() == false)
    {
        /* code */
        result.push_back(min_heap.top());
        min_heap.pop();
    }
    
    sort(result.begin(), result.end());
    
    return result;
}

// 求topk小值，使用小根堆
vector<int> topk_smallest(const vector<int>& nums, int k) {
    // create  max heap
    priority_queue<int> max_heap;
    for (int num: nums)
    {
        /* code */
        if (max_heap.size() < k)
        {
            /* code */
            max_heap.push(num);
        }
        else if (num < max_heap.top())
        {
            /* code */
            max_heap.pop();
            max_heap.push(num);
        }  
    }

    vector<int> result;
    while (max_heap.empty() == false)
    {
        /* code */
        result.push_back(max_heap.top());
        max_heap.pop();
    }

    sort(result.begin(), result.end());

    return result;
    
    
}

int main() {
    vector<int> nums = {5, 2, 9, 1, 7, 6, 8, 3};
    int k = 3;
    // vector<int> res = topk_largest(nums, k);
    vector<int> res = topk_smallest(nums, k);
    cout << "Top " << k << " largest values: ";
    for (int x : res) cout << x << " ";
    cout << endl;
    return 0;
}