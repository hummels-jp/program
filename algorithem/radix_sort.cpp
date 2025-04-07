#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to get the maximum value in the array
int getMax(const vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

// Counting sort for a specific digit represented by exp
void countingSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n); // Output array
    int count[10] = {0};   // Count array for digits 0-9

    // Count occurrences of each digit
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // Update count[i] to store the position of the digit in output[]
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy the sorted elements back to the original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Radix Sort function
void radixSort(vector<int>& arr) {
    int maxVal = getMax(arr);

    // Perform counting sort for each digit
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSort(arr, exp);
    }
}

// 基数排序，分配10个桶，不需要排序算法
void radix_sort_hqq(vector<int>& arr)
{
    // 先找到数组中的最大值，计算相应的位数
    int max = *max_element(arr.begin(), arr.end());

    // 计算最大值的位数
    int bit_num = 0;
    while (max >0)
    {
        /* code */
        max = max /10;
        bit_num ++;
    }

    // 创建桶, 每个桶中存储的是 vector<int> 对象
    vector<vector<int>> buckets(10);
    int mod = 10;
    int dev = 1;

    // 遍历数字位
    for (int i = 0; i < bit_num; i++)
    {
        /* code */
            // 遍历原始数组，将原始数据加入到对应的桶中去
        for (int  j = 0; j < arr.size(); j++)
        {
            int index = arr[j]%mod/dev;
            buckets[index].push_back(arr[j]);
        }

        // 一次遍历完成后，需要根据桶序，刷新原始的队列
        int k = 0;
        for (auto bucket: buckets)
        {
            for (auto vec: bucket)
            {
                arr[k++] = vec;
            }
        }

        // 取完数据之后，需要将bucket充值，以变进行下一位的桶排序
        buckets.assign(10, vector<int>());
        
        mod *=10;
        dev *=10;
    }
    

    
    
}

// Main function to test the Radix Sort
int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    cout << "Original array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // radixSort(arr);
    radix_sort_hqq(arr);

    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}