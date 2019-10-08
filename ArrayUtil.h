//
// Created by Eduardo Ribeiro da Silva on 08/10/19.
//

#ifndef PERMUTEBYSORTING_ARRAYUTIL_H
#define PERMUTEBYSORTING_ARRAYUTIL_H

#include <iostream>
#include <random>
#include <iterator>
#include <map>

using namespace std;

template <typename T>
class ArrayUtil {
public:
    ArrayUtil() = default;
    ~ArrayUtil() = default;

    void permuteBySort(T array[], size_t length) const;
    void permuteInPlace(T array[], size_t length) const;

private:
    void swap(T array[], int origin, int target) const;
};

template<typename T>
void ArrayUtil<T>::permuteBySort(T array[], size_t length) const {
    int *p_array = new int[length];

    // Random instrumentation
    random_device rd;     // only used once to initialise (seed) engine
    mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    uniform_int_distribution<int> uni(0, length-1); // guaranteed unbiased

    // Create the random array (is not permitted repeated values, than use a map to control this rule)
    size_t index = 0;
    map<int, int> noRepeatedValues;
    int randomValue;

    while (index < length) {
        randomValue = uni(rng);
        if (noRepeatedValues.find(randomValue) == noRepeatedValues.end()) {
            noRepeatedValues.insert(pair<int, int>(randomValue, randomValue));
            p_array[index++] = randomValue;
        }
    }

    // Use random array to sort target array
    // Make a copy of original array
    T *copiedArray = new T[length];
    copy(array, array+length, copiedArray);

    // The p_array contains the POSITION of element
    // Ex: [12,23,31,45] x [3,1,0,2] = [45,23,12,31]
    for (size_t i = 0; i < length; i++) {
        array[i] = copiedArray[p_array[i]];
    }
}

template<typename T>
void ArrayUtil<T>::permuteInPlace(T array[], size_t length) const {
    int *p_array = new int[length];

    // Random instrumentation
    random_device rd;     // only used once to initialise (seed) engine
    mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    uniform_int_distribution<int> uni(0, length-1); // guaranteed unbiased

    map<int, int> noRepeatedValues;
    int randomValue;

    for (size_t i = 0; i < length; i++) {
        while (true) {
            randomValue = uni(rng);
            if (noRepeatedValues.find(randomValue) == noRepeatedValues.end()) {
                noRepeatedValues.insert(pair<int, int>(randomValue, randomValue));
                swap(array, i, randomValue);
                break;
            }
        }
    }
}

template<typename T>
inline void ArrayUtil<T>::swap(T *array, int origin, int target) const {
    T temp = array[origin];
    array[origin] = array[target];
    array[target] = temp;
}

#endif //PERMUTEBYSORTING_ARRAYUTIL_H
