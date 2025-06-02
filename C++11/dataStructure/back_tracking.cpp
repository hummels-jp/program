
#include <string>
#include <iostream>
using namespace std;

void func(int arr[], int i, int length)
{
    if (i == length) // 递归终止条件 StackOverFlow
    {
        for (int j = 0; j < length; ++j)
        {
            cout << arr[j] << " ";
        }
        cout << endl;
    }
    else
    {
        // A
        func(arr, i + 1, length);
        // B
        // func(arr, i + 1, length);
        // A::func i=1
    }
}

int main()
{
    int array[] = {1,2,3};
    int len = 3;

    func(array, 0, len);
}