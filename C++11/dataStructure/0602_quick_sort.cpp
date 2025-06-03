#include <vector>
#include <ctime>
#include <iostream>
using namespace std;

// 快速排序，使用基准，对数列进行分割
int split_range(vector<int> & vec, int left, int right)
{

    int pivot = vec[left];
    int i = left;
    int j = right;

    while (i < j)
    {
        /* code */
        // 从右向左进行查询，找到第一个小于 pivot 的值
        while (i < j && vec[j] > pivot)
        {
            /* code */
            j--;
        }

        // 将右边的小于pivot的值，复制到左边，并且移动左边指针
        if (i < j)
        {
            /* code */
            vec[i] = vec[j];
            i++;
        }

        // 从左向右查找，找到第一个大于 pivot 的值
        while (i<j&& vec[i]< pivot)
        {
            /* code */
            i++;
        }

        // 将坐标大于Pivot 的值，复制到右边，并且移动右指针
        if (i<j)
        {
            /* code */
            vec[j] = vec[i];
            j--;
        }    
    }

    vec[i] = pivot;
    return i;   
}

void quick_sort(vector<int>& vec, int left, int right)
{
    if (left >=right)
    {
        /* code */
        return;
    }
    

    int pos = split_range(vec, left, right);
    quick_sort(vec, left, pos -1);
    quick_sort(vec, pos+1, right);
}

int main()
{
    const int len = 10;
    vector<int> vec;
    srand(time(0));
    for (int i = 0; i < len; i++)
    {
        /* code */
        vec.push_back(std::rand() % 100);
    }

    for (int i = 0; i < len; i++)
    {
        /* code */
        cout << vec[i] << " ";
    }
    cout << endl;
    
    quick_sort(vec, 0, vec.size()-1);

    for (int i = 0; i < len; i++)
    {
        /* code */
        cout << vec[i] << " ";
    }
    cout << endl;


    
}
