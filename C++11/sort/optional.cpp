#include <iostream>
#include <optional>
using namespace std;

optional<int> find_even(int x) {
    if (x % 2 == 0)
        return x;
    else
        return nullopt; // 没有值时返回nullopt
}

int main() {
    auto result = find_even(5);
    if (result.has_value()) {
        cout << "Even: " << result.value() << endl;
    } else {
        cout << "Not even" << endl;
    }

    result = find_even(8);
    cout << result.value_or(-1) << endl; // 没有值时返回-1

    result = find_even(5);
    cout << result.value_or(-1) << endl; // 没有值时返回-1

    return 0;
}