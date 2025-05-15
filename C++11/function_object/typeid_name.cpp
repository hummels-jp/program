#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>

int add(int a, int b) { return a + b; }

int main() {
    int i = 0;
    double d = 0.0;
    float f = 0.0f;
    char c = 'a';
    bool b = true;
    long l = 0L;
    short s = 0;
    unsigned int ui = 0;
    unsigned long ul = 0;
    long long ll = 0;
    unsigned long long ull = 0;
    wchar_t wc = L'a';
    char16_t c16 = u'a';
    char32_t c32 = U'a';
    std::string str = "hello";
    const char* cstr = "world";
    int arr[5] = {1,2,3,4,5};
    std::vector<int> vec = {1,2,3};
    void* p = nullptr;
    int (*func_ptr)(int, int) = add;

    std::cout << "int: " << typeid(i).name() << std::endl; // int: i
    std::cout << "double: " << typeid(d).name() << std::endl; // double: d
    std::cout << "float: " << typeid(f).name() << std::endl; // float: f
    std::cout << "char: " << typeid(c).name() << std::endl; // char: c
    std::cout << "bool: " << typeid(b).name() << std::endl; // bool: b
    std::cout << "long: " << typeid(l).name() << std::endl; // long: l
    std::cout << "short: " << typeid(s).name() << std::endl; // short: s
    std::cout << "unsigned int: " << typeid(ui).name() << std::endl; // unsigned int: j
    std::cout << "unsigned long: " << typeid(ul).name() << std::endl; // unsigned long: k
    std::cout << "long long: " << typeid(ll).name() << std::endl; // long long: x
    std::cout << "unsigned long long: " << typeid(ull).name() << std::endl; // unsigned long long: y
    std::cout << "wchar_t: " << typeid(wc).name() << std::endl; // wchar_t: w
    std::cout << "char16_t: " << typeid(c16).name() << std::endl; // char16_t: t
    std::cout << "char32_t: " << typeid(c32).name() << std::endl; // char32_t: u
    std::cout << "std::string: " << typeid(str).name() << std::endl; // std::string: NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
    std::cout << "const char*: " << typeid(cstr).name() << std::endl; // const char*: PKc
    std::cout << "int[5]: " << typeid(arr).name() << std::endl; // int[5]: A5_i
    std::cout << "std::vector<int>: " << typeid(vec).name() << std::endl; // std::vector<int>: St6vectorIiSaIiEE
    std::cout << "void*: " << typeid(p).name() << std::endl; // void*: Pv
    std::cout << "int(*)(int, int): " << typeid(func_ptr).name() << std::endl; // int(*)(int, int): PFiiiE

    return 0;
}