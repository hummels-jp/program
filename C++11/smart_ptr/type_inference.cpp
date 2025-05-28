#include <iostream>
#include <vector>
#include <typeinfo>

// 这个函数用于打印左值引用的值
void printLValueRef(const int& value) {
    std::cout << "LValue reference: " << value << std::endl;
}

// 这个函数用于打印右值引用的值
void printRValueRef(int&& value) {
    std::cout << "RValue reference: " << value << std::endl;
}

// 定义一个参数为右值引用类型的函数
void processRValue(int&& value) {
    // 函数参数 value 会转化为左值 
    //printRValueRef(value); // 报错， value是一个右值引用，不能绑定到左值引用
    // // 但是可以使用 std::move 将其转化为右值引用
    printRValueRef(std::move(value)); // 调用 printRValueRef
}


int main() {

    int lvalue = 10;
    printLValueRef(lvalue); // 调用左值引用函数

    printRValueRef(20); // 调用右值引用函数

    processRValue(30); // 调用右值引用参数函数

    return 0;
}