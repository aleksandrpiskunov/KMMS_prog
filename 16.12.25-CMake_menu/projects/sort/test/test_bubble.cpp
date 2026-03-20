#include <gtest/gtest.h>
#include "bubble_sort.hpp"


TEST(BubbleSortTest, SingleElement) {
    int a[] = {42};
    const int n = 1;
    pav::sortings::bubble_sort(a, n);
    ASSERT_EQ(a[0], 42);
}

TEST(BubbleSortTest, TwoElements) {
    int a[] = {2, 1};
    const int n = 2;
    pav::sortings::bubble_sort(a, n);
    ASSERT_LE(a[0], a[1]);
}

