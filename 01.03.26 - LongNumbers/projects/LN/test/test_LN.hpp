#ifndef TEST_LN_HPP
#define TEST_LN_HPP

#include <gtest/gtest.h>
#include "LongNumbers.hpp"

using pav::LongNumber;

// Фикстура для сравнений
class FComparisons : public testing::Test {
public:
    LongNumber 
        n_2, n_1, n_1_copy,
        p_1, p_1_copy, p_12;

    FComparisons()
        : n_2("-2"), n_1("-1"), n_1_copy("-1"),
          p_1("1"), p_1_copy("1"), p_12("12") {}
};

// Фикстура для арифметики
class FArithmetic : public testing::Test {
public:
    LongNumber 
        n_19602, n_99, n_87, n_17, n_16, n_15, n_7, n_4, n_3, n_2, n_1,
        p_0, p_1, p_1_copy, p_2, p_3, p_4, p_6, p_12, p_16, p_17, p_99, p_99_copy, p_113, p_198, p_1188, p_19602,
        n_100, n_6, p_100, p__;

    FArithmetic()
        : n_19602("-19602"), n_99("-99"), n_87("-87"), n_17("-17"),
          n_16("-16"), n_15("-15"), n_7("-7"), n_4("-4"), n_3("-3"), n_2("-2"), n_1("-1"),
          p_0("0"), p_1("1"), p_1_copy("1"), p_2("2"), p_3("3"), p_4("4"), p_6("6"), p_12("12"), p_16("16"), p_17("17"),
          p_99("99"), p_99_copy("99"), p_113("113"), p_198("198"), p_1188("1188"), p_19602("19602"),
          n_100("-100"), n_6("-6"), p_100("100"), p__("6") {}
};

#endif // TEST_LN_HPP