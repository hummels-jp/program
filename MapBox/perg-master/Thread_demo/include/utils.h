#ifndef MAX_UTILS_H
#define MAX_UTILS_H

template<typename T>
T maxValue(T a, T b) {
    return (a > b) ? a : b;
}

template<typename T>
T minValue(T a, T b) {
    return (a < b) ? a : b;
}

template<int N>
/**
 * @brief Multiplies the given integer value by a constant.
 * 
 * @param value The integer value to be multiplied.
 * @return The result of multiplying the input value by a constant.
 */
int multiplyByConstant(int value) {
    return value * N;
}

#endif
// MAX_UTILS_H