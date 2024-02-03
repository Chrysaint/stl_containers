//
// Created by pinkod on 7/10/25.
//

#ifndef S21_VECTOR_TEST_CPP
#define S21_VECTOR_TEST_CPP

#include <iostream>
#include <stdexcept>
#include <vector>

#include "../s21_vector.h"
#include "./../testing_include/test_include.h"
#include "gtest/gtest.h"

using namespace s21;

TEST(vectorTest, defaultConstructor) {
    s21::vector<int> x;
    EXPECT_EQ((size_t) 0, x.size());
}

TEST(vectorTest, parameterizedConstructor) {
    s21::vector<int> x(5);
    EXPECT_EQ((size_t) 5, x.size());
}

TEST(vectorTest, initializerListConstructor) {
    s21::vector<int> x{1, 2, 3};
    EXPECT_EQ(x.size(), (size_t) 3);
}

TEST(vectorTest, copyConstructor) {
    s21::vector<int> x{1, 2, 3};
    s21::vector<int> y(x);
    EXPECT_EQ(y.size(), (size_t) 3);
    EXPECT_EQ(x.size(), (size_t) 3);
}

TEST(vectorTest, moveConstructor) {
    s21::vector<int> x{1, 2, 3};
    s21::vector<int> y(std::move(x));
    EXPECT_EQ(y.size(), (size_t) 3);
    EXPECT_EQ(x.size(), (size_t) 0);
}

TEST(vectorTest, operatorEqual) {
    s21::vector<int> x{1, 2, 3};
    s21::vector<int> y = x;
    EXPECT_EQ(y.size(), (size_t) 3);
    EXPECT_EQ(x.size(), (size_t) 3);
}

TEST(vectorTest, operatorEqual2) {
    s21::vector<int> x;
    x = {1, 2, 3};
    EXPECT_EQ(x.size(), (size_t) 3);
}

TEST(vectorTest, at) {
    s21::vector<int> v{1, 2, 3};
    EXPECT_THROW(v.at(3), std::out_of_range);
    EXPECT_EQ(v.at(0), 1);
}

TEST(vectorTest, operatorAccessesElement) {
    s21::vector<int> v{1, 2, 3};
    EXPECT_THROW(v[3], std::out_of_range);
    EXPECT_EQ(v[0], 1);
}

TEST(vectorTest, front) {
    s21::vector<int> v{1, 2, 3};
    EXPECT_EQ(v.front(), 1);
}

TEST(vectorTest, back) {
    s21::vector<int> v{1, 2, 3};
    EXPECT_EQ(v.back(), 3);
}

TEST(vectorTest, data) {
    s21::vector<int> v{1, 2, 3};
    EXPECT_EQ(v.data()[1], 2);
}

TEST(vectorTest, begin) {
    s21::vector<int> v{1, 2, 3};
    EXPECT_EQ(*v.begin(), 1);
}

TEST(vectorTest, end) {
    s21::vector<int> v{1, 2, 3};
    EXPECT_EQ(*(v.end() - 1), 3);
}

TEST(vectorTest, empty) {
    s21::vector<int> v;
    EXPECT_TRUE(v.empty());
}

TEST(vectorTest, size) {
    s21::vector<int> x(5);
    EXPECT_EQ(x.size(), (size_t) 5);
}

TEST(vectorTest, MaxSize) {
    s21::vector<int> x;
    EXPECT_EQ((bool) x.max_size(), true);
}

TEST(vectorTest, capacity) {
    s21::vector<char> x{'D', 'e', 'n'};
    EXPECT_EQ((size_t) 3, x.capacity());
}

TEST(vectorTest, reserve) {
    s21::vector<int> v{1, 2, 3};
    v.reserve(10);
    EXPECT_EQ(v.capacity(), (size_t) 10);
}

TEST(vectorTest, shrinkToFit) {
    s21::vector<int> v{1, 2, 3};
    v.reserve(10);
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), (size_t) 3);
}

TEST(vectorTest, clear) {
    s21::vector<int> v{1, 2, 3};
    v.clear();
    EXPECT_TRUE(v.empty());
}

TEST(vectorTest, insert) {
    s21::vector<int> v{1, 2, 3};
    v.insert(v.end(), 15);
    EXPECT_EQ(v.size(), (size_t) 4);
    EXPECT_EQ(v.at(3), 15);
}

TEST(vectorTest, erase) {
    s21::vector<int> v{1, 2, 3};
    v.erase(v.begin());
    EXPECT_EQ(v.size(), (size_t) 2);
    EXPECT_EQ(v.at(0), 2);
}

TEST(vectorTest, eraseOutOfRange) {
    s21::vector<int> v{1, 2, 3};
    EXPECT_THROW(v.erase(v.end()), std::out_of_range);
}
TEST(vectorTest, pushBack) {
    s21::vector<int> v{1, 2, 3};
    v.push_back(16);
    EXPECT_EQ(v.size(), (size_t) 4);
    EXPECT_EQ(v.at(3), 16);
}

TEST(vectorTest, popBack) {
    s21::vector<int> v{1, 2, 3};
    v.pop_back();
    EXPECT_EQ(v.size(), (size_t) 2);
    EXPECT_EQ(*(v.end() - 1), 2);
}

TEST(vectorTest, popBackEmpty) {
    s21::vector<int> v;
    EXPECT_THROW(v.pop_back(), std::out_of_range);
}

TEST(vectorTest, swap) {
    s21::vector<int> v1{1, 2, 3};
    s21::vector<int> v2{4, 5, 6};
    v1.swap(v2);
    EXPECT_EQ(v1.at(0), 4);
    EXPECT_EQ(v2.at(2), 3);
}

TEST(vectorTest, insertMany) {
    s21::vector<int> v1{1, 2, 3};
    v1.insert_many(v1.begin() + 1, 6, 7, 8);
    std::vector<int> result = {1, 6, 7, 8, 2, 3};
    EXPECT_EQ(v1.size(), result.size());
    for(int i = 0; i < v1.size(); ++i) { EXPECT_EQ(v1.at(i), result.at(i)); }
}

TEST(vectorTest, insertManyEnd) {
    s21::vector<int> v1{1, 2, 3};
    v1.insert_many(v1.end(), 6, 7, 8);
    std::vector<int> result = {1, 2, 3, 6, 7, 8};
    EXPECT_EQ(v1.size(), result.size());
    for(int i = 0; i < v1.size(); ++i) { EXPECT_EQ(v1.at(i), result.at(i)); }
}

TEST(vectorTest, insertManyBegin) {
    s21::vector<int> v1{1, 2, 3};
    v1.insert_many(v1.begin(), 6, 7, 8);
    std::vector<int> result = {6, 7, 8, 1, 2, 3};
    EXPECT_EQ(v1.size(), result.size());
    for(int i = 0; i < v1.size(); ++i) { EXPECT_EQ(v1.at(i), result.at(i)); }
}

TEST(vectorTest, insertManyOutOfRange) {
    s21::vector<int> v1{1, 2, 3};
    EXPECT_THROW(v1.insert_many(v1.begin() - 1, 1, 2, 3), std::out_of_range);
    EXPECT_THROW(v1.insert_many(v1.end() + 1, 1, 2, 3), std::out_of_range);
}

TEST(vectorTest, insertManyBack) {
    s21::vector<int> v1{1, 2, 3};
    v1.insert_many_back(4, 5, 6);
    std::vector<int> result = {1, 2, 3, 4, 5, 6};
    EXPECT_EQ(v1.size(), result.size());
    for(int i = 0; i < v1.size(); ++i) { EXPECT_EQ(v1.at(i), result.at(i)); }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    UTIL(RUN_ALL_TESTS());
    return 0;
}

#endif // S21_VECTOR_TEST_CPP
