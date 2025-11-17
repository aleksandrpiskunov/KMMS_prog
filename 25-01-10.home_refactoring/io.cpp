#include <iostream>
#include "io.hpp"

void pav::read_input(int arr[], int& size) {
    const int MAX_SIZE = 100;
    std::cout << "Введите размер последовательности (≤" << MAX_SIZE << "): ";
    std::cin >> size;
    std::cout << "Введите " << size << " чисел через пробел:\n";
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }
}

void pav::print_output(int sequence[], int sequence_length) {
    std::cout << "Длина LIS: " << sequence_length << "\n";
    std::cout << "Сама подпоследовательность:\n";
    for (int i = 0; i < sequence_length; ++i) {
        std::cout << sequence[i] << " ";
    }
    std::cout << "\n";
}
