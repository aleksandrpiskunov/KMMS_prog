#include "io.hpp"
#include "lis.hpp"

int main() {
    const int MAX_SIZE = 100;
    int size;
    int array[MAX_SIZE];
    int lis_sequence[MAX_SIZE];
    int length;

    biv::read_input(array, size);
    biv::compute_lis(array, size, lis_sequence, length);
    biv::print_output(lis_sequence, length);

    return 0;
}
