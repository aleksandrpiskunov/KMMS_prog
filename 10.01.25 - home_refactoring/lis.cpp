#include "lis.hpp"

void pav::find_position(int tails[], int length, int key, int& out_pos) {
    int left = 0;
    int right = length - 1;
    out_pos = length;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        if (tails[mid] >= key) {
            out_pos = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
}

void pav::compute_lis(int arr[], int n, int lis_sequence[], int& length) {
    const int MAX_SIZE = 100;
    int tails[MAX_SIZE];       
    int prev_idx[MAX_SIZE];     
    int pos[MAX_SIZE];       
    length = 0;

    for (int i = 0; i < n; ++i) {
        int position; 
        find_position(tails, length, arr[i], position);

        tails[position] = arr[i];
        pos[position] = i;
        if (position > 0) {
            prev_idx[i] = pos[position - 1];
        } else {
            prev_idx[i] = -1;
        }

        if (position == length) {
            ++length;
        }
    }

    int current_pos = pos[length - 1];
    for (int i = length - 1; i >= 0; --i) {
        lis_sequence[i] = arr[current_pos];
        current_pos = prev_idx[current_pos];
    }
}
