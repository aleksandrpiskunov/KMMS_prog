
#include <gtest/gtest.h>
#include "doubly_linked_list.hpp"

using pav::DoublyLinkedList;

TEST(DoublyLinkedListTest, PushBackAndSize) {
	DoublyLinkedList<int> list;
	EXPECT_EQ(list.get_size(), 0);
	list.push_back(1);
	EXPECT_EQ(list.get_size(), 1);
	list.push_back(2);
	EXPECT_EQ(list.get_size(), 2);
}

TEST(DoublyLinkedListTest, HasItem) {
	DoublyLinkedList<int> list;
	list.push_back(42);
	EXPECT_TRUE(list.has_item(42));
	EXPECT_FALSE(list.has_item(13));
}

TEST(DoublyLinkedListTest, RemoveFirst) {
	DoublyLinkedList<int> list;
	list.push_back(5);
	list.push_back(10);
	EXPECT_TRUE(list.remove_first(5));
	EXPECT_FALSE(list.has_item(5));
	EXPECT_EQ(list.get_size(), 1);
	EXPECT_FALSE(list.remove_first(99));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
