//
// Created by pinkod on 7/10/25.
//
#include <gtest/gtest.h>

#include "../s21_queue.h"
#include "./../testing_include/test_include.h"

using namespace s21;

TEST(QueueTest, DefaultConstructor) {
    queue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, InitializerListConstructor) {
    queue<int> q{1, 2, 3};
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, CopyConstructor) {
    queue<int> orig{1, 2, 3};
    queue<int> copy(orig);

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.front(), 1);
    EXPECT_EQ(copy.back(), 3);

    copy.pop();
    EXPECT_EQ(copy.front(), 2);
    EXPECT_EQ(orig.front(), 1); // Original unchanged
}

TEST(QueueTest, MoveConstructor) {
    queue<int> orig{1, 2, 3};
    queue<int> moved(std::move(orig));

    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(moved.front(), 1);
    EXPECT_EQ(moved.back(), 3);
    EXPECT_TRUE(orig.empty());
}

TEST(QueueTest, MoveAssignment) {
    queue<int> orig{1, 2, 3};
    queue<int> moved;
    moved = std::move(orig);

    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(moved.front(), 1);
    EXPECT_EQ(moved.back(), 3);
    EXPECT_TRUE(orig.empty());
}

TEST(QueueTest, FrontBack) {
    queue<std::string> q;
    q.push("first");
    q.push("middle");
    q.push("last");

    EXPECT_EQ(q.front(), "first");
    EXPECT_EQ(q.back(), "last");

    q.pop();
    EXPECT_EQ(q.front(), "middle");
    EXPECT_EQ(q.back(), "last");
}

TEST(QueueTest, EmptySize) {
    queue<double> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);

    q.push(3.14);
    EXPECT_FALSE(q.empty());
    EXPECT_EQ(q.size(), 1);
}

TEST(QueueTest, PushPop) {
    queue<int> q;
    q.push(10);
    q.push(20);

    EXPECT_EQ(q.front(), 10);
    EXPECT_EQ(q.back(), 20);

    q.pop();
    EXPECT_EQ(q.front(), 20);
    EXPECT_EQ(q.back(), 20);

    q.pop();
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, PopEmptyThrows) {
    queue<int> q;
    EXPECT_THROW(q.pop(), std::out_of_range);
}

TEST(QueueTest, Swap) {
    queue<int> q1{1, 2, 3};
    queue<int> q2{4, 5};

    q1.swap(q2);

    EXPECT_EQ(q1.size(), 2);
    EXPECT_EQ(q1.front(), 4);
    EXPECT_EQ(q1.back(), 5);

    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q2.front(), 1);
    EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, SelfAssignment) {
    queue<int> q{1, 2, 3};
    q = q;
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.front(), 1);

    q = std::move(q);
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.front(), 1);
}

TEST(QueueTest, Chars) {
    queue<char> char_q;
    char_q.push('a');
    char_q.push('b');
    EXPECT_EQ(char_q.front(), 'a');
    EXPECT_EQ(char_q.back(), 'b');
}

TEST(QueueTest, InsertManyBack) {
    queue<int> q{1, 2, 3};
    q.insert_many_back(4, 5, 6, 7);
    EXPECT_EQ(q.back(), 7);
    EXPECT_EQ(q.size(), 7);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    UTIL(RUN_ALL_TESTS());
    return 0;
}
