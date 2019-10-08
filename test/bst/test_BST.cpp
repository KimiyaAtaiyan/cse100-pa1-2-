/*
 * Author: Kimiya Ataiyan
 * UserID: kataiyan
 * Date: 10/7/19
 * Filename: test_BST.cpp
 * Description: contains test methods to test the implementation
 * 	         of the methods implemented in BST.hpp
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "BSTNode.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty BST test starts here */

TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);
}
TEST(BSTTests, EMPTY_TREE_SIZE_TEST){

	BST<int>bst;
	ASSERT_EQ(bst.size(), 0);
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;
    BST<int> bst1;
    BST<int> bst2;
    BST<int> bst3;

  public:
    SmallBSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, 100, -33};
        insertIntoBST(input, bst);

        vector<int> input1{100, 4, 205, -2, 5, 6, 300, 200};
        insertIntoBST(input1, bst1);

	vector<int>input3{3,4,5,6,7,8};
	insertIntoBST(input3, bst3);

    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    ASSERT_EQ(bst.size(), 5);
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(3));
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATE2_TEST) {
    ASSERT_FALSE(bst.insert(-33));
}

TEST_F(SmallBSTFixture, SMALL_INSERT_NORMAL_TEST) {
    // assert true for normal insertion( non duplicate)
    ASSERT_TRUE(bst.insert(101));
}

TEST_F(SmallBSTFixture, SMALL_INSERT_LHS_TEST){

	ASSERT_TRUE(bst.insert(99));
}

TEST_F(SmallBSTFixture, IN_ORDER_TRAVERSAL_TEST) {
    vector<int> list{-33, 1, 3, 4, 100};
    ASSERT_EQ(bst.inorder(), list);
}

TEST_F(SmallBSTFixture, IN_ORDER_TRAVERSAL_BIG_TEST) {
    vector<int> list{-2, 4, 5, 6, 100, 200, 205, 300};
    ASSERT_EQ(bst1.inorder(), list);
}

TEST_F(SmallBSTFixture, ROOT_INSERTION_TEST) { ASSERT_TRUE(bst2.insert(4)); }

TEST_F(SmallBSTFixture, IN_ORDER_TRAVERSE_UNBALANCED_TEST){

	vector<int>list{3,4,5,6,7,8};
	ASSERT_EQ(bst3.inorder(),list);
}

/*TEST_F(SmallBSTFixture, FIND_NODE_TEST){


        BSTIterator<int> iter(&);

        ASSERT_EQ(bst.find(node.data) ,iter);


}*/

