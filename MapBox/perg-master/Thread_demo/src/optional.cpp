#include <iostream>
#include <memory>
#include <optional>
using namespace std;
#include "optional.h"

class User {
    string name;
    optional<string> nickName;
    optional<int> age;

public:
    User(const string& name, optional<string> nickName = {}, optional<int> age = {})
        : name(name), nickName(nickName), age(age)
    {}

    friend ostream& operator<<(ostream& os, const User& user);
};

ostream& operator<<(ostream& os, const User& user) {
    os << user.name << " ";
    if (user.nickName) {
        os << *user.nickName << " "; // use * to dereference the optional
    }
    if (user.age) {
        os << "age-of-" << *user.age; // use * to dereference the optional
    }
    return os;
}

int optional_demo() {
    User user1("Alice", "Ally", 25);
    User user2("Bob");
    User user3("Charlie", {}, 30);

    cout << user1 << endl;
    cout << user2 << endl;
    cout << user3 << endl;

    return 0;
}