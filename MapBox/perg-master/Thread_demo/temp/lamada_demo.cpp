#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void lamada_demo1(int flag)
{
    vector<int> vec = {1, 2, 3, 4, 5};
    auto iter = find_if(vec.begin(), vec.end(), 
    [flag](int item)->bool{return item > flag;});

    cout << *iter << endl;

}

int main()
{
    int flag = 4;
    lamada_demo1(flag);
}