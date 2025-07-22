
#include <iostream>
#include "global.h"
using namespace std;

int main() {
    cout << "Global Age: " << global_age << endl;
    cout << "Global Name: " << global_name << endl;

    // Modify global variables
    global_age = 25;
    global_name = "John Doe";

    cout << "Updated Global Age: " << global_age << endl;
    cout << "Updated Global Name: " << global_name << endl;

    // Call the function to print global info
    print_global_info();

    return 0;
}