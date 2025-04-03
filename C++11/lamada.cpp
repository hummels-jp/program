#include <iostream>
#include <functional>

int main() {
    int externalValue = 10;

    // Lambda function capturing externalValue by reference
    auto lambdaFunction = [&externalValue](int increment) {
        externalValue += increment;
        return externalValue;
    };

    std::cout << "Initial externalValue: " << externalValue << std::endl;

    int result = lambdaFunction(5); // Call lambda with an increment of 5
    std::cout << "After lambda call, externalValue: " << externalValue << std::endl;
    std::cout << "Lambda returned: " << result << std::endl;

    // Define a function pointer to point to the lambda function
    std::function<int(int)> functionPointer = lambdaFunction;

    // Use the function pointer to call the lambda function
    int resultFromPointer = functionPointer(10);
    std::cout << "After function pointer call, externalValue: " << externalValue << std::endl;
    std::cout << "Function pointer returned: " << resultFromPointer << std::endl;

    return 0;
}