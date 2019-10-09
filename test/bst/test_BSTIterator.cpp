#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_ITERATOR_TEST, TEST_ITERATOR_INCREMENT) {
    BSTNode<int> node(3);
    BSTIterator<int> iter(&node);

    ASSERT_NE(iter, nullptr);

    iter++;

    ASSERT_EQ(iter, nullptr);
}

TEST(BST_ITERATOR_TEST, ITERATOR_EQUAL_TEST){

	BSTNode<int>node(3);
	BSTIterator<int> iter1(&node);
	BSTIterator<int> iter2(&node);

	bool test = (iter1 == iter2);
	ASSERT_EQ(test,true);
}


TEST(BST_ITERATOR_TEST, ITERTATOR_NOT_EQUAL_TEST){

	BSTNode<int> node(3);
	BSTIterator<int> iter1(&node);
	BSTNode<int> node2(100);
	BSTIterator<int> iter2(&node2);
	bool test = (iter1 != iter2);
	ASSERT_EQ(test,true);
}
