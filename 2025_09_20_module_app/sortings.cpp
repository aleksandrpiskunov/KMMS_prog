#include "sortings.hpp"
using namespace biv::sortings;
using namespace std;

void biv::sortings::bubble_sort(int* arr, const int size) {
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

void biv::sortings::shaker_sort(int* arr, const int size) {
    bool swapped = true;
    int begin = 0;
    int end = size - 1;

    while (swapped) {
        swapped = false;

        for (int i = begin; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                int j = arr[i+1];
                arr[i + 1] = arr[i];
                arr[i] = j;
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        --end;

        for (int i = end; i > begin; --i) {
            if (arr[i] < arr[i - 1]) {
                int j = arr[i-1];
                arr[i - 1] = arr[i];
                arr[i] = j;
                swapped = true;
            }
        }
        ++begin;
    }
}

void biv::sortings::odd_even_sort(int* arr, const int size) {
    bool sorted = false;

    while (!sorted) {
        sorted = true;

        for (int i = 1; i < size - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                int j = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = j;
                sorted = false;
            }
        }

        for (int i = 0; i < size - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                int j = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = j;
                sorted = false;
            }
        }
    }
}

void comb_sort(int* arr, const int size) {
    int step = size;
    bool swapped = true;

    while (step > 1 || swapped) {
        if (step > 1) {
            step = static_cast<int>(step / 1.3);
        }

        swapped = false;

        for (int i = 0; i + step < size; ++i) {
            if (arr[i] > arr[i + step]) {
                int j = arr[i];
                arr[i] = arr[i + step];
                arr[i + step] = j;
                swapped = true;
            }
        }
    }
}