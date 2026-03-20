#include "sortings.hpp"
using namespace pav::sortings;
using namespace std;

void pav::sortings::bubble_sort(int* arr, const int size) {
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

void pav::sortings::shaker_sort(int* arr, const int size) {
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

void pav::sortings::odd_even_sort(int* arr, const int size) {
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

void pav::sortings::comb_sort(int* arr, const int size) {
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

void pav::sortings::quick_sort(int* arr, const int beg, const int end) {
    if (beg>=end) return;
    int pivot = arr[(beg + end) / 2];
    
    int i = beg;
    int j = end;
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i<= j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    quick_sort(arr, beg, j);
    quick_sort(arr, i, end);
}

void pav::sortings::merge(int *arr, int* buf, const int beg, const int mid, const int end){
    int i = beg, j = mid+1, k = beg;

    while ( i<= mid && j<= end) {
        if (arr[i] < arr[j]) buf[k++] = arr[i++];
        else buf[k++] = arr[j++];
    }

    if (i>mid) {
        while ( j<= end) buf[k++] = arr[j++];
    }else {
        while ( i<= mid) buf[k++] = arr[i++];
    }
    for (i = beg; i <= end; ++i) arr[i] = buf[i];
    
}
void pav::sortings::merge_reqursive(int *arr, int* buf, const int beg, const int end){
    if (beg >= end) return;

    int mid = (beg + end) / 2;

    merge_reqursive(arr, buf, beg, mid);
    merge_reqursive(arr, buf, mid + 1, end);

    merge(arr, buf, beg, mid, end);
}

void pav::sortings::selection_sort(int* arr, const int size) {
    for (int i = 0; i < size - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

void pav::sortings::insertion_sort(int* arr, const int size) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void pav::sortings::shell_sort(int* arr, const int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; ++i) {
            int temp = arr[i];
            int j = i;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void pav::sortings::heapify(int* arr, const int size, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != root) {
        int temp = arr[root];
        arr[root] = arr[largest];
        arr[largest] = temp;
        heapify(arr, size, largest);
    }
}

void pav::sortings::heap_sort(int* arr, const int size) {
    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify(arr, size, i);
    }

    for (int i = size - 1; i > 0; --i) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

