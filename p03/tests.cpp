#include "funSearchProblem.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::Eq;

TEST(test, facingsun) {
    auto f = FunSearchProblem::facingSun;

    vector<int> v{4, 2, 5, 4, 6};
    ASSERT_EQ(f(v), 3);

    v = {};
    ASSERT_EQ(f(v), 0);

    v = {1, 1, 1, 1, 1, 1, 1, 1};
    ASSERT_EQ(f(v), 1);
}

TEST(test, squareR) {
    auto f = FunSearchProblem::squareR;

    ASSERT_EQ(f(25), 5);
    ASSERT_EQ(f(9), 3);
    ASSERT_EQ(f(0), 0);
    ASSERT_EQ(f(93), 9);
    ASSERT_EQ(f(10), 3);
    ASSERT_EQ(f(40), 6);
}

TEST(test, missingvalue) {
    auto f = FunSearchProblem::smallestMissingValue;

    vector<int> v{};
    ASSERT_EQ(f(v), 0);

    v = {0, 0, 0, 0};
    ASSERT_EQ(f(v), 0);

    v = {-1, -34, -12, -43};
    ASSERT_EQ(f(v), 0);

    v = {1, 2, 3, 4, 5, 6};
    ASSERT_EQ(f(v), 7);

    v = {1, 2, 3, 6, 7, 8};
    ASSERT_EQ(f(v), 4);

    v = {2, 6, 1, 2, 8, 7, 4, 3};
    ASSERT_EQ(f(v), 5);

    v = {2, -12, 6, 0, 1, -7, 2, 8, -123, 7, 4, 3, -5};
    ASSERT_EQ(f(v), 5);
}

TEST(test, minPages) {
    auto f = FunSearchProblem::minPages;

    vector<int> v{1, 2, 3, 4, 5, 6, 7};
    ASSERT_EQ(f(v, 3), 11);

    v = {4, 6, 2, 4};
    ASSERT_EQ(f(v, 2), 10);

    v = {1, 3, 12, 3};
    ASSERT_EQ(f(v, 4), 12);

    v = {10, 10, 10, 10};
    ASSERT_EQ(f(v, 2), 20);

    v = {10, 20, 30, 40};
    ASSERT_EQ(f(v, 2), 60);

    v = {20, 10};
    ASSERT_EQ(f(v, 3), -1);
}
