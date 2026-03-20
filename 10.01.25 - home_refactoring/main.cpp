#include "io.hpp"
#include "lis.hpp"

int main() {
    const int MAX_SIZE = 100;
    int size;
    int array[MAX_SIZE];
    int lis_sequence[MAX_SIZE];
    int length;

    pav::read_input(array, size);
    pav::compute_lis(array, size, lis_sequence, length);
    pav::print_output(lis_sequence, length);

    return 0;
}
