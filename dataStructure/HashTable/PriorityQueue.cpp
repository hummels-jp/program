#include <queue>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    // default max heap
    priority_queue<int> max_queue;
    max_queue.push(2);
    max_queue.push(8);
    max_queue.push(5);
    cout << "max queue top " << max_queue.top() << endl;


    // min heap
    priority_queue<int, vector<int>, greater<int>> min_queue;
    min_queue.push(2);
    min_queue.push(8);
    min_queue.push(5);
    cout << "min queue top " << min_queue.top() << endl;

    return 0;
}