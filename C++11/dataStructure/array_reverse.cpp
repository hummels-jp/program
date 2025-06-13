#include <iostream>

void reverseArray(int* arr, int size) {
    int left = 0;
    int right = size - 1;
    while (left < right) {
        std::swap(arr[left], arr[right]);
        ++left;
        --right;
    }
}

void splitArray(int* arr, int size) {
    int left = 0;
    int right = size - 1;

    while (left < right)
    {
        /* code */
    }
    
    }

    // Reverse the first part
    reverseArray(arr, splitIndex);
    // Reverse the second part
    reverseArray(arr + splitIndex, size - splitIndex);
    // Reverse the whole array
    reverseArray(arr, size);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original array: ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    reverseArray(arr, size);

    std::cout << "Reversed array: ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}