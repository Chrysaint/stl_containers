//
// Created by pinkod on 7/10/25.
//
#include <gtest/gtest.h>

#include "../s21_stack.h"
#include "./../testing_include/test_include.h"

using namespace s21;

TEST(stackTest, DefaultConstructor) {
    stack<int> s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(stackTest, InitializerListConstructor) {
    stack<int> s{1, 2, 3, 4, 5};
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 5);

    EXPECT_EQ(s.top(), 5);
    s.pop();
    EXPECT_EQ(s.top(), 4);
    s.pop();
    EXPECT_EQ(s.top(), 3);
    s.pop();
    EXPECT_EQ(s.top(), 2);
    s.pop();
    EXPECT_EQ(s.top(), 1);
    s.pop();
    EXPECT_TRUE(s.empty());
}

TEST(stackTest, CopyConstructor) {
    stack<int> s1{1, 2, 3};
    stack<int> s2(s1);

    EXPECT_EQ(s2.top(), 3);
    s2.pop();
    EXPECT_EQ(s2.top(), 2);
    s2.pop();
    EXPECT_EQ(s2.top(), 1);
    s2.pop();
    EXPECT_TRUE(s2.empty());
}

TEST(stackTest, MoveConstructor) {
    stack<int> s1{1, 2, 3};
    stack<int> s2(std::move(s1));

    EXPECT_TRUE(s1.empty());
    EXPECT_EQ(s2.size(), 3);
    EXPECT_EQ(s2.top(), 3);
}

TEST(stackTest, MoveConstructorOperator) {
    stack<int> s1{1, 2, 3};
    stack<int> s2 = s1;

    EXPECT_EQ(s2.top(), 3);
    s2.pop();
    EXPECT_EQ(s2.top(), 2);
    s2.pop();
    EXPECT_EQ(s2.top(), 1);
    s2.pop();
    EXPECT_TRUE(s2.empty());
}

TEST(stackTest, PushAndTop) {
    stack<int> s;
    s.push(10);
    EXPECT_EQ(s.top(), 10);
    s.push(20);
    EXPECT_EQ(s.top(), 20);
}

TEST(stackTest, Pop) {
    stack<int> s{1, 2, 3};
    s.pop();
    EXPECT_EQ(s.top(), 2);
    s.pop();
    EXPECT_EQ(s.top(), 1);
}

TEST(stackTest, Swap) {
    stack<int> s1{1, 2, 3};
    stack<int> s2{4, 5};

    s1.swap(s2);

    EXPECT_EQ(s1.size(), 2);
    EXPECT_EQ(s1.top(), 5);

    EXPECT_EQ(s2.size(), 3);
    EXPECT_EQ(s2.top(), 3);
}

TEST(stackTest, InsertManyBack) {
    stack<int> s1{1, 2, 3};

    s1.insert_many_back(4, 5, 6);

    EXPECT_EQ(s1.size(), 6);
    EXPECT_EQ(s1.top(), 6);
    s1.pop();
    EXPECT_EQ(s1.size(), 5);
    EXPECT_EQ(s1.top(), 5);
    s1.pop();
    EXPECT_EQ(s1.size(), 4);
    EXPECT_EQ(s1.top(), 4);
    s1.pop();
    EXPECT_EQ(s1.size(), 3);
    EXPECT_EQ(s1.top(), 3);
    s1.pop();
    EXPECT_EQ(s1.size(), 2);
    EXPECT_EQ(s1.top(), 2);
    s1.pop();
    EXPECT_EQ(s1.size(), 1);
    EXPECT_EQ(s1.top(), 1);
}
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    UTIL(RUN_ALL_TESTS());
    return 0;
}
