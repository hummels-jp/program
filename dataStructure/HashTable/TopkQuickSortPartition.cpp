#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// 快排分割法，返回前k小元素（无序）
int partition(vector<int>& nums, int left, int right) {
    int pivot = nums[left];
    int i = left + 1;
    int j = right;
    while (true)
    {
        // left
        while (i <= j && nums[i] < pivot)
        {
            /* code */
            i++;
        }

        // right
        while (i <=j && nums[j] > pivot)
        {
            /* code */
            j--;
        }

        if (i > j)
        {
            /* code */
            break;
        }

        swap(nums[i], nums[j]);
        i ++;
        j --;
    }

    swap(nums[left], nums[j]);
    return j;
    
}

vector<int> topk_smallest(vector<int>& nums, int k) {
    int left = 0;
    int right = nums.size() - 1;
    while (true)
    {
        int pos = partition(nums, left, right);
        if (pos == k-1)
        {
            /* code */
            break;
        }
        else if (pos < k-1)
        {
            /* code */
            left = pos + 1;
        }
        else
        {
            right = pos - 1;
        }
    }

    return vector<int>(nums.begin(), nums.begin() + k);
    
}

int main() {
    vector<int> nums = {7, 2, 5, 3, 9, 1, 6, 4, 8};
    int k = 4;
    vector<int> res = topk_smallest(nums, k);
    cout << "Top " << k << " smallest: ";
    for (int x : res) cout << x << " ";
    cout << endl;
    // 如需有序，可加 sort(res.begin(), res.end());
    return 0;
}