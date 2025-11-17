#ifndef LIS_HPP
#define LIS_HPP

namespace pav {  
    void find_position(int tails[], int length, int key, int& out_pos);
    void compute_lis(int arr[], int n, int lis_sequence[], int& length);
}

#endif
