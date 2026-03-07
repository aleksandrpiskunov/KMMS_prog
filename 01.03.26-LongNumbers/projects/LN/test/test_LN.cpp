#include "LongNumbers.hpp"
#include <gtest/gtest.h>
using pav::LongNumber;

TEST(LongNumberTest, ConstructorFromString) {
    LongNumber a("12345");
    EXPECT_EQ(a, LongNumber("12345"));
    LongNumber b("-987");
    EXPECT_EQ(b, LongNumber("-987"));
}

TEST(LongNumberTest, CopyConstructor) {
    LongNumber a("1234");
    LongNumber b(a);
    EXPECT_EQ(a, b);
}

TEST(LongNumberTest, MoveConstructor) {
    LongNumber a("5678");
    LongNumber b(std::move(a));
    EXPECT_EQ(b, LongNumber("5678"));
}

TEST(LongNumberTest, AssignmentOperator) {
    LongNumber a("111");
    LongNumber b;
    b = a;
    EXPECT_EQ(b, a);
}

TEST(LongNumberTest, MoveAssignmentOperator) {
    LongNumber a("222");
    LongNumber b;
    b = std::move(a);
    EXPECT_EQ(b, LongNumber("222"));
}

TEST(LongNumberTest, EqualityAndInequality) {
    LongNumber a("123");
    LongNumber b("123");
    LongNumber c("321");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
}

TEST(LongNumberTest, ComparisonOperators) {
    LongNumber a("100");
    LongNumber b("99");
    LongNumber c("100");
    LongNumber d("-101");
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
    EXPECT_TRUE(b < a);
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(a < c);
    EXPECT_FALSE(a > c);
    EXPECT_TRUE(d < a);
}

TEST(LongNumberTest, Addition) {
    LongNumber a("123");
    LongNumber b("456");
    EXPECT_EQ(a + b, LongNumber("579"));
    LongNumber c("-100");
    EXPECT_EQ(a + c, LongNumber("23"));
}

TEST(LongNumberTest, Subtraction) {
    LongNumber a("1000");
    LongNumber b("1");
    EXPECT_EQ(a - b, LongNumber("999"));
    EXPECT_EQ(b - a, LongNumber("-999"));
}

TEST(LongNumberTest, Multiplication) {
    LongNumber a("12");
    LongNumber b("13");
    EXPECT_EQ(a * b, LongNumber("156"));
    LongNumber c("-2");
    EXPECT_EQ(a * c, LongNumber("-24"));
}

TEST(LongNumberTest, Division) {
    LongNumber a("1234");
    LongNumber b("10");
    EXPECT_EQ(a / b, LongNumber("123"));
    LongNumber c("-2");
    EXPECT_EQ(a / c, LongNumber("-617"));
}

TEST(LongNumberTest, Modulo) {
    LongNumber a("1234");
    LongNumber b("10");
    EXPECT_EQ(a % b, LongNumber("4"));
}

