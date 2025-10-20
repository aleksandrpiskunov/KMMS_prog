#include "LIS.hpp"

void biv::LIS::findPos(int tails[], int length, int key, int& outPos) {
    int left = 0;
    int right = length - 1;
    outPos = length;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (tails[mid] >= key) {
            outPos = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
}

void biv::LIS::computeLIS(int arr[], const int n, int lisseq[], int& length) {
    int tails[100];       
    int prevIdx[100];     
    int pos[100];       
    length = 0;

    for (int i = 0; i < n; ++i) {
        int p; 
        findPos(tails, length, arr[i], p);

        tails[p] = arr[i];
        pos[p] = i;
        if (p > 0) {
            prevIdx[i] = pos[p - 1];
        } else {
            prevIdx[i] = -1;
        }

        if (p == length) {
            ++length;
        }
    }

    int k = pos[length - 1];
    for (int i = length - 1; i >= 0; --i) {
        lisseq[i] = arr[k];
        k = prevIdx[k];
    }
}
