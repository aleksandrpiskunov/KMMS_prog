#include <cmath>
#include <iostream>

int main() {
    const int size = 10;
    double arr[size];

    for (int i = 0; i < size; ++i) {
        std::cout << "Введите " << i << " элемент" << std::endl;
        std::cin >> arr[i];
    }

    int i = 0;
    bool is_increasing = 1;
    while (i < size - 1) {
        if ((arr[i] > arr[i + 1]) ) {
            is_increasing = 0;
            break;
        } 
        ++i;
    }

    if (is_increasing) {
        std::cout << "Последовательность возрастающая" << std::endl;
    } else {
        std::cout << "Последовательность убывающая" << std::endl;
    }

    return 0;
}
