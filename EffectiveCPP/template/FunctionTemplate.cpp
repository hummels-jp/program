#include <iostream>
#include <string>
using namespace std;


// function template
template<typename T>
T add(T a, T b)
{
    return a + b;
}

// full specification function template
template<>
const char* add<const char*>(const char* a, const char* b)
{
    static string result;
    result = string(a) + string(b);
    return result.c_str();
}


int main()
{
    cout << add<int>(2, 3) << endl;
    cout << add<const char*>("hello", " wrold") << endl;
}