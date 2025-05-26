#include <iostream>
#include <functional>

// 普通函数
void normalFunction(int x) {
    std::cout << "普通函数被调用，参数: " << x << std::endl;
}

// 函数对象
struct FunctionObject {
    void operator()(int x) const {
        std::cout << "函数对象被调用，参数: " << x << std::endl;
    }
};

// 类对象转换为可调用对象
struct CallableClass {
    void call(int x) const {
        std::cout << "类对象转换为可调用对象，参数: " << x << std::endl;
    }

    // 定义 operator() 使类对象可调用
    void operator()(int x) const {
        call(x);
    }
};

// 将类的成员函数转换为可调用对象
struct MemberFunctionClass {
    void memberFunction(int x) const {
        std::cout << "类成员函数被调用，参数: " << x << std::endl;
    }
};

// 将类的静态成员函数转换为可调用对象
struct StaticMemberFunctionClass {
    static void staticMemberFunction(int x) {
        std::cout << "类静态成员函数被调用，参数: " << x << std::endl;
    }
};

// 将类的成员函数转换为可调用对象
struct MemberToCallable {
    MemberFunctionClass obj;

    std::function<void(int)> getCallable() {
        return std::bind(&MemberFunctionClass::memberFunction, obj, std::placeholders::_1);
    }
};

// 将类的静态成员对象转换为可调用对象
struct StaticMemberObjectClass {
    static inline FunctionObject staticMemberObject;

    std::function<void(int)> getCallable() {
        return staticMemberObject;
    }
};

// Lambda 表达式
auto lambdaFunction = [](int x) {
    std::cout << "Lambda 表达式被调用，参数: " << x << std::endl;
};

// 将类的成员变量转换为可调用对象
struct MemberVariableToCallable {
    int memberVariable = 42;
};

int main() {
    // 使用函数指针调用普通函数
    void (*funcPtr)(int) = &normalFunction;
    funcPtr(10);

    // 使用 std::function 调用普通函数
    std::function<void(int)> func1 = normalFunction;
    func1(20);

    // 使用 std::function 调用函数对象
    FunctionObject funcObj;
    std::function<void(int)> func2 = funcObj;
    func2(30);

    // 使用 std::function 调用 Lambda 表达式
    std::function<void(int)> func3 = lambdaFunction;
    func3(40);

    CallableClass callableObj;
    // 使用 std::function 调用类对象    
    std::function<void(int)> func4 = callableObj;
    func4(50);

    // 使用 std::function 调用类成员函数
    MemberFunctionClass memberObj;  
    std::function<void(int)> func5 = std::bind(&MemberFunctionClass::memberFunction, memberObj, std::placeholders::_1);
    func5(60);

    // 使用 std::function 调用类静态成员函数
    std::function<void(int)> func6 = &StaticMemberFunctionClass::staticMemberFunction;
    func6(70);

    // 使用 std::function 调用类的成员函数转换为可调用对象
    MemberToCallable memberToCallableObj;   
    std::function<void(int)> func7 = memberToCallableObj.getCallable();
    func7(80);

    // 使用 std::function 调用类的静态成员对象转换为可调用对象
    std::function<void(int)> func8 = StaticMemberObjectClass::staticMemberObject;
    func8(90);

    using ptr = int MemberVariableToCallable::*;
    ptr memberPtr = &MemberVariableToCallable::memberVariable;
    MemberVariableToCallable obj;
    std::cout << "成员变量的值: " << obj.*memberPtr << std::endl;
    


    return 0;
}