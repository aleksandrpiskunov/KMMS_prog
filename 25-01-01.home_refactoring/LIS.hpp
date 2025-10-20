// lis.hpp
#ifndef LIS_HPP
#define LIS_HPP

namespace biv {
    namespace LIS{
        void findPos(int tails[], int length, int key, int& outPos);
        void computeLIS(int arr[], int n, int lisseq[], int& length);
    }
}
#endif 
