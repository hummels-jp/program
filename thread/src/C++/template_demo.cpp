#include <iostream>
#include "template_pair.h" // 包含 Pair 类的头文件
#include "fixedArray.h"
#include "template_template_parameter.h"
#include "template_full_specification.h"
#include "template_partial_specification.h"
#include "function_template_full_specification.h"
#include <array>
#include <vector>
using namespace std;


int main() {
    // 使用通用函数模板
    printValue(42);               // 输出: Generic Template: 42
    printValue(3.14);             // 输出: Generic Template: 3.14

    // 使用全特化函数模板
    printValue<std::string>("Hello, World!"); // 输出: Specialized Template for std::string: Hello, World!

    return 0;
}

