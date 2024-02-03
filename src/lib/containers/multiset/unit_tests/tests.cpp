//
// Created by pinkod on 7/10/25.
//
#include <gtest/gtest.h>

#include "./../s21_multiset.h"
#include "./../testing_include/test_include.h"

using namespace s21;

TEST(MultisetTest, DefaultConstructor) {
    multiset<int> s;
    EXPECT_EQ(s.empty(), true);
}

TEST(MultisetTest, ListConstructor) {
    multiset<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = s.begin(); it != s.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }
}

TEST(MultisetTest, CopyConstructor) {
    multiset<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    multiset<int> s2 = s;

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = s2.begin(); it != s2.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }

    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);
}

TEST(MultisetTest, MoveConstructor) {
    multiset<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    multiset<int> s2 = std::move(s);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = s2.begin(); it != s2.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }

    EXPECT_EQ(s.empty(), true);
}

TEST(MultisetTest, MoveOperator) {
    multiset<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    multiset<int> s2;
    s2 = std::move(s);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = s2.begin(); it != s2.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }

    EXPECT_EQ(s.empty(), true);
}

// TEST(MultisetTest, MoveSelfOperator) {
//   multiset<int> s{1, 2, 3, 4, 5};
//   EXPECT_EQ(s.empty(), false);
//   EXPECT_EQ(s.size(), 5);

//   s = std::move(s);
// }

TEST(MultisetTest, Begin) {
    multiset<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    auto begin = s.begin();
    EXPECT_EQ(*begin, 1);
}

TEST(MultisetTest, End) {
    multiset<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    auto begin = s.end();
    EXPECT_EQ(*(--begin), 5);
}

TEST(MultisetTest, BeginException) {
    multiset<int> s;
    EXPECT_EQ(s.empty(), true);

    auto begin = s.begin();
    (void) begin;
}

TEST(MultisetTest, Empty) {
    multiset<int> s;
    EXPECT_EQ(s.empty(), true);
}

TEST(MultisetTest, Size) {
    multiset<int> s;
    EXPECT_EQ(s.size(), 0);
}

TEST(MultisetTest, MaxSize) {
    multiset<int> s;
    EXPECT_EQ((bool) s.max_size(), true);
}

TEST(MultisetTest, Clear) {
    multiset<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = s.begin(); it != s.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }

    s.clear();

    EXPECT_EQ(s.empty(), true);
}

TEST(MultisetTest, Insert) {
    multiset<int> s{1, 2, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 4);

    s.insert(0);
    s.insert(3);
    s.insert(3);
    s.insert(6);

    EXPECT_EQ(s.size(), 8);

    int ans[] = {0, 1, 2, 3, 3, 4, 5, 6};
    int ans_id = 0;

    for(auto it = s.begin(); it != s.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }
}

TEST(MultisetTest, Balance) {
    multiset<int> s;

    for(int i = 0; i < 100; ++i) { s.insert(i); }

    int count = 0;

    for(auto it = s.begin(); it != s.end(); ++it) { EXPECT_EQ(*it, count++); }
}

TEST(MultisetTest, Erase) {
    multiset<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    auto it = s.find(3);
    s.erase(it);

    EXPECT_EQ(s.size(), 4);

    int ans[] = {1, 2, 4, 5};
    int ans_id = 0;

    for(auto it2 = s.begin(); it2 != s.end(); ++it2) { EXPECT_EQ(*it2, ans[ans_id++]); }
}

TEST(MultisetTest, Swap) {
    multiset<int> s{5, 4, 3, 2, 1};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);
    multiset<int> s2{1, 2, 3, 4, 5};

    s.swap(s2);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = s.begin(); it != s.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }
}

TEST(MultisetTest, Merge) {
    multiset<int> s{5, 4, 3, 2, 1};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);
    multiset<int> s2{5, 6, 7, 8, 9};

    s.merge(s2);

    int ans[] = {1, 2, 3, 4, 5, 5, 6, 7, 8, 9};
    int ans_id = 0;

    for(auto it = s.begin(); it != s.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }
}

TEST(MultisetTest, Count) {
    multiset<int> s{5, 5, 4, 3, 2, 1};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 6);

    EXPECT_EQ(s.count(5), 2);
    EXPECT_EQ(s.count(1), 1);
}

TEST(MultisetTest, Find) {
    multiset<int> s{5, 4, 3, 2, 1};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    EXPECT_EQ(s.find(5), --(s.end()));
    EXPECT_EQ(s.find(2), ++(s.begin()));
    EXPECT_EQ(s.find(1), (s.begin()));
}

TEST(MultisetTest, Contains) {
    multiset<int> s{5, 4, 3, 2, 1};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    EXPECT_EQ(s.contains(1), true);
    EXPECT_EQ(s.contains(2), true);
    EXPECT_EQ(s.contains(3), true);
    EXPECT_EQ(s.contains(4), true);
    EXPECT_EQ(s.contains(5), true);
    EXPECT_EQ(s.contains(0), false);
}

TEST(MultisetTest, Equal_range) {
    multiset<int> s{5, 5, 4, 3, 2, 1};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 6);

    auto it = s.equal_range(5);
    EXPECT_EQ(*it.first, 5);
    EXPECT_EQ(it.second, s.end());
}

TEST(MultisetTest, Lower_bound) {
    multiset<int> s{5, 5, 4, 3, 2, 1};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 6);

    auto it = s.lower_bound(5);
    EXPECT_EQ(*it, 5);
}

TEST(MultisetTest, Upper_bound) {
    multiset<int> s{5, 5, 4, 3, 2, 1};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 6);

    auto it = s.upper_bound(0);
    EXPECT_EQ(*it, 1);
}

TEST(MultisetTest, InsertMany) {
    multiset<int> s{5, 4, 3, 2, 1};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    auto vec = s.insert_many(5, 6, 7, 8, 9);

    int vect[] = {5, 6, 7, 8, 9};
    int vect_id = 0;

    for(int i = 0; i < 5; ++i) { EXPECT_EQ(*((vec[i]).first), vect[vect_id++]); }

    int ans[] = {1, 2, 3, 4, 5, 5, 6, 7, 8, 9};
    int ans_id = 0;

    for(auto it = s.begin(); it != s.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    UTIL(RUN_ALL_TESTS());
    return 0;
}
