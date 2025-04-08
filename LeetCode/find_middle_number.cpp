#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        if (m > n) {
            // Ensure nums1 is the smaller array
            return findMedianSortedArrays(nums2, nums1);
        }

        int imin = 0, imax = m, halfLen = (m + n + 1) / 2;
        while (imin <= imax) {
            int i = (imin + imax) / 2;
            int j = halfLen - i;
            if (i < m && nums1[i] < nums2[j - 1]) {
                // i is too small
                imin = i + 1;
            } else if (i > 0 && nums1[i - 1] > nums2[j]) {
                // i is too big
                imax = i - 1;
            } else {
                // i is perfect
                int maxOfLeft;
                if (i == 0) {
                    maxOfLeft = nums2[j - 1];
                } else if (j == 0) {
                    maxOfLeft = nums1[i - 1];
                } else {
                    maxOfLeft = max(nums1[i - 1], nums2[j - 1]);
                }

                if ((m + n) % 2 == 1) {
                    return maxOfLeft;
                }

                int minOfRight;
                if (i == m) {
                    minOfRight = nums2[j];
                } else if (j == n) {
                    minOfRight = nums1[i];
                } else {
                    minOfRight = min(nums1[i], nums2[j]);
                }

                return (maxOfLeft + minOfRight) / 2.0;
            }
        }

        return 0.0;
    }
};

vector<int> merge_sorted_array(vector<int>& num1, vector<int>& num2)
{
    int len1 = num1.size();
    int len2 = num2.size();

    vector<int> result = vector<int>(len1 + len2);

    int i =0, j=0;k=0;
    while (i<len1&&j<len2)
    {
        /* code */
        if (num1[i] < num2[j])
        {
            /* code */
            result[k++] = num1[i++];
        }
        else
        {
            result[k++] = num2[j++];
        }
    }

    while (i<len1)
    {
        /* code */
        result[k++] = num1[i++];
    }

    while (j<len2)
    {
        /* code */
        result[k++] = num2[j++];
    }
    
    return result;
    
}

int find_middle_number(vector<int>& num1, vector<int>& num2)
{
    int len1 = num1.size();
    int len2 = num2.size();

    vector<int> merged_array = merge_sorted_array(num1, num2);

    int middle = 0;

    if ((len1 + len2)%2 == 1)
    {
        /* code */
        return merged_array[(len1+len2)/2];
    }
    else
    {
        return (merged_array[(len1+len2)/2] + merged_array[(len1+len2)/2 + 1])/2;
    }
    
    
    
}

int main() {
    Solution solution;
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};
    // cout << "Median: " << solution.findMedianSortedArrays(nums1, nums2) << endl;
    cout << "Median: " << find_middle_number(nums1, nums2) << endl;

    nums1 = {1, 2};
    nums2 = {3, 4};
    // cout << "Median: " << solution.findMedianSortedArrays(nums1, nums2) << endl;
    cout << "Median: " << find_middle_number(nums1, nums2) << endl;

    return 0;
}