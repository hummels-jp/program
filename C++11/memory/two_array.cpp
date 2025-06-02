#include <iostream>

using namespace std;

 
int main() {

    int row =3;
    int col = 4;

    // 创建一个二维数组
    int **arr = new int*[row]; // 分配行指针数组
    for (int i = 0; i < row; i++) {
        arr[i] = new int[col]; // 为每一行分配列数组
    }//

    return 0;
}

