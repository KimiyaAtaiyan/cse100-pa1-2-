#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "KDT.hpp"
#include "NaiveSearch.hpp"
#include "Point.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/**
 * A simple test fixture from which multiple tests can
 * be written. The structure of the KDT built from this
 * may vary. See test_BST.cpp for more information on
 * test fixtures.
 */
class SmallKDTFixture : public ::testing::Test {
  protected:
    vector<Point> vec;
    KDT kdt;
    KDT kdt1;
    vector<Point> vec1;
    KDT kdt2;
    vector<Point> vec2;

  public:
    SmallKDTFixture() {
        vec.emplace_back(Point({1.0, 3.2}));
        vec.emplace_back(Point({3.2, 1.0}));
        vec.emplace_back(Point({5.7, 3.2}));
        vec.emplace_back(Point({1.8, 1.9}));
        vec.emplace_back(Point({4.4, 2.2}));
        kdt.build(vec);



	vec1.emplace_back(Point({1,2,3}));
	vec1.emplace_back(Point({4,5,6}));
	vec1.emplace_back(Point({7,8,9}));
	vec1.emplace_back(Point({10,11,12}));
	kdt1.build(vec1);

	vec2.emplace_back(Point({0,0}));
	kdt2.build(vec2);
    }
};

TEST_F(SmallKDTFixture, TEST_SIZE) {
    // Assert that the kd tree has the correct size
    ASSERT_EQ(kdt.size(), 5);
}

TEST_F(SmallKDTFixture, TEST_TWO_SIZE){

	ASSERT_EQ(kdt1.size(),4);
	ASSERT_EQ(kdt1.height(), 2);
}
TEST_F(SmallKDTFixture, TEST_NEAREST_POINT) {
    NaiveSearch naiveSearch;
    naiveSearch.build(vec);
    Point queryPoint({5.81, 3.21});
    Point* closestPoint = naiveSearch.findNearestNeighbor(queryPoint);
    ASSERT_EQ(*kdt.findNearestNeighbor(queryPoint), *closestPoint);
}

TEST_F(SmallKDTFixture, TEST_NEAREST_TWO_POINT){

	NaiveSearch naiveSearch;
	naiveSearch.build(vec1);
	Point queryPoint({7,8,9});
	Point * closestPoint  = naiveSearch.findNearestNeighbor(queryPoint);
	ASSERT_EQ(*kdt1.findNearestNeighbor(queryPoint), *closestPoint);
}

TEST_F(SmallKDTFixture, TEST_EMPTY_NEAREST_POINT){
	NaiveSearch naiveSearch;
	naiveSearch.build(vec2);
	Point queryPoint({1,2});
	Point * closestPoint = naiveSearch.findNearestNeighbor(queryPoint);
	ASSERT_EQ(*kdt2.findNearestNeighbor(queryPoint), *closestPoint);
}

