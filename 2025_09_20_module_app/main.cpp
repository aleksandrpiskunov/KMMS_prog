// main.cpp
#include "io.hpp"
#include "LIS.hpp"

int main() {
    int n;
    int arr[MAXN];
    int lisseq[MAXN];
    int length;

    readInput(arr, n);
    computeLIS(arr, n, lisseq, length);
    printOutput(lisseq, length);

    return 0;
}
