/*
 * Author: Kimiya Ataiyan
 * UserID: kataiyan
 * Date: 10/7/19
 * Source of help: none
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_NODE_TESTS, TEST_SUCCESSOR) {
    BSTNode<int>* node = new BSTNode<int>(3);
    ASSERT_EQ(node->successor(), nullptr);

    BSTNode<int>* node1 = new BSTNode<int>(6);
    node1->parent = node;
    node->right = node1;

    BSTNode<int>* node2 = new BSTNode<int>(2);
    node2->parent = node;
    node->left = node2;

    BSTNode<int>* node3 = new BSTNode<int>(4);
    node3->parent = node1;
    node1->left = node3;

    BSTNode<int>* node4 = new BSTNode<int>(8);
    node4->parent = node1;
    node1->right = node4;

    BSTNode<int>* node5 = new BSTNode<int>(1);
    node5->parent = node2;
    node2->left = node5;

    ASSERT_EQ(node5->successor(), node2);
    ASSERT_EQ(node1->successor(), node4);
    ASSERT_EQ(node3->successor(), node1);
    ASSERT_EQ(node4->successor(), nullptr);

    delete node;
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
}
