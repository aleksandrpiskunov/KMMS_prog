#include "vector.hpp"
#include <gtest/gtest.h>

using pav::Vector;

TEST(VectorTest, PushBackAndSize) {
	Vector<int> v;
	EXPECT_EQ(v.get_size(), 0);
	v.push_back(10);
	EXPECT_EQ(v.get_size(), 1);
	v.push_back(20);
	EXPECT_EQ(v.get_size(), 2);
}

TEST(VectorTest, HasItem) {
	Vector<int> v;
	v.push_back(42);
	EXPECT_TRUE(v.has_item(42));
	EXPECT_FALSE(v.has_item(13));
}

TEST(VectorTest, Insert) {
	Vector<int> v;
	v.push_back(1);
	v.push_back(3);
	EXPECT_TRUE(v.insert(1, 2)); 
	EXPECT_EQ(v.get_size(), 3);
	EXPECT_TRUE(v.has_item(2));
	EXPECT_FALSE(v.insert(100, 5)); 
}

TEST(VectorTest, RemoveFirst) {
	Vector<int> v;
	v.push_back(5);
	v.push_back(10);
	EXPECT_TRUE(v.remove_first(5));
	EXPECT_FALSE(v.has_item(5));
	EXPECT_EQ(v.get_size(), 1);
	EXPECT_FALSE(v.remove_first(99));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
