#include "io.hpp"
#include "LIS.hpp"

int main() {
    const int MAXN = 100;
    int n;
    int arr[MAXN];
    int lisseq[MAXN];
    int length;

    biv::io::readInput(arr, n);
    biv::LIS::computeLIS(arr, n, lisseq, length);
    biv::io::printOutput(lisseq, length);

    return 0;
}
