#include "io.hpp"
#include <iostream>

void biv::io::readInput(int arr[], int& n) {
    const int MAXN = 100;
    std::cout << "Введите размер последовательности (≤" << MAXN << "): ";
    std::cin >> n;
    std::cout << "Введите " << n << " чисел через пробел:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
}

void biv::io::printOutput(int seq[], int sequenceLength) {
    std::cout << "Длина LIS: " << sequenceLength << "\n";
    std::cout << "Сама подпоследовательность:\n";
    for (int i = 0; i < sequenceLength; ++i) {
        std::cout << seq[i] << " ";
    }
    std::cout << "\n";
}
