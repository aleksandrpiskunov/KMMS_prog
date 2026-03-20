#include "bubble_sort.hpp"

using namespace pav::sortings;

void pav::sortings::bubble_sort(int* arr, const int size) {
   if (size <= 1) {
        return; 
    }

    bool is_swapped = false;
    int i = 0;
    do{
        is_swapped = false;
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
                is_swapped = true;  
            }
        }
        ++i;
    } while (is_swapped);
}
