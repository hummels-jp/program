#include <queue>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    // 大顶堆（默认）
    priority_queue<int> max_heap;
    max_heap.push(5);
    max_heap.push(2);
    max_heap.push(8);
    cout << "大顶堆堆顶: " << max_heap.top() << endl; // 8

    // 小顶堆
    priority_queue<int, vector<int>, greater<int>> min_heap;
    min_heap.push(5);
    min_heap.push(2);
    min_heap.push(8);
    cout << "小顶堆堆顶: " << min_heap.top() << endl; // 2

    return 0;
}