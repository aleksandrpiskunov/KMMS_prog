#include "io.hpp"
#include <iostream>

void pav::print_array(const char* const comment, int* arr, const int size) {
    std::cout << comment << " ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << ", ";
    }
	
    std::cout << std::endl;
}
