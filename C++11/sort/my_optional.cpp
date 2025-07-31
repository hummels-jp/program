#include <iostream>
#include <optional>
using namespace std;

optional<int> find_even(int value)
{
    if (value % 2 == 0)
    {
        /* code */
        return value;
    }
    else
    {
        return nullopt;
    }
    
}

int main()
{
    auto result = find_even(6);
    if (result.has_value())
    {
        /* code */
        cout << "Even " << result.value() << endl;
    }
    else
    {
        cout << "Not Even " << result.value_or(-1) << endl;
    }
    
}