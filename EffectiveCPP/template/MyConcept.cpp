#include <type_traits>
#include <iostream>
#include <string>
using namespace std;

template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept CString = std::is_same_v<T, const char*> || std::is_same_v<T, char*>;

template<typename T>
concept StdString = std::is_same_v<T, std::string>;

void cout_type(Integral auto value)
{
    cout << "Integral type " << endl;
}

void cout_type(CString auto value)
{
    cout << "CString type " << endl;
}

void cout_type(StdString auto value)
{
    cout << "StdString type " << endl;
}

template<typename T>
requires(!Integral<T> && !CString<T> && !StdString<T>)
void cout_type(T value)
{
    cout << "other type " << endl;
}

int main()
{
    int x = 10;
    cout_type(x);

    const char* cstr = "hello";
    cout_type(cstr);

    string str("world");
    cout_type(str);

    double val =10.9;
    cout_type(val);
}
