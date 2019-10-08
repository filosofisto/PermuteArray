#include <iostream>
#include <chrono>
#include <iomanip>
#include "ArrayUtil.h"

using namespace std;
using namespace std::chrono;

int main()
{
    int array[6] = { 1, 2, 3, 4, 5, 6 };
    int sizeArray = size(array);
    ArrayUtil<int> arrayUtil;

    auto start = high_resolution_clock::now();
    arrayUtil.permuteBySort(array, sizeArray);
    auto stop = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop - start);

    for (int i: array) {
        cout << i << ", ";
    }
    cout << endl << "permuteBySort: " << duration1.count() << " msecs" << endl;

    start = high_resolution_clock::now();
    arrayUtil.permuteInPlace(array, sizeArray);
    stop = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop - start);

    for (int i: array) {
        cout << i << ", ";
    }
    cout << endl << "permuteInPlace (swap): " << duration2.count() << " msecs" << endl;

    float diff = abs(static_cast<float>(duration2.count()) - static_cast<float>(duration1.count())) /
                 static_cast<float>(duration1.count()) * 100;
    cout << std::fixed << std::setprecision( 0 ) << "Diferenca Percentual: " << diff << "%" << endl;

    // Shuffle
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    start = high_resolution_clock::now();
    shuffle(begin(array), end(array), default_random_engine(seed));
    stop = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop - start);

    for (int i: array) {
        cout << i << ", ";
    }

    cout << endl << "Shuffle: " << duration3.count() << " msecs" << endl;
    diff = abs(static_cast<float>(duration3.count()) - static_cast<float>(duration2.count())) /
           static_cast<float>(duration2.count()) * 100;
    cout << std::fixed << std::setprecision( 0 ) << "Diferenca Percentual (shuffle): " << diff << "%" << endl;

    return EXIT_SUCCESS;
}