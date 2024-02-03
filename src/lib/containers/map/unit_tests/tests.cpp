//
// Created by pinkod on 7/10/25.
//
#include <gtest/gtest.h>

#include "./../s21_map.h"
#include "./../testing_include/test_include.h"

using namespace s21;

TEST(mapTest, DefaultConstructor) {
    map<int, int> m;
    EXPECT_EQ(m.empty(), true);
}

TEST(mapTest, ListConstructor) {
    map<int, int> m{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = m.begin(); it != m.end(); ++it) { EXPECT_EQ((*it).second, ans[ans_id++]); }
}

TEST(mapTest, CopyConstructor) {
    map<int, int> m{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    map<int, int> m2 = m;

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = m2.begin(); it != m2.end(); ++it) { EXPECT_EQ((*it).second, ans[ans_id++]); }

    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);
}

TEST(mapTest, MoveConstructor) {
    map<int, int> m{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    map<int, int> m2 = std::move(m);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = m2.begin(); it != m2.end(); ++it) { EXPECT_EQ((*it).second, ans[ans_id++]); }

    EXPECT_EQ(m.empty(), true);
}

TEST(mapTest, MoveOperator) {
    map<int, int> m{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    map<int, int> m2;
    m2 = std::move(m);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = m2.begin(); it != m2.end(); ++it) { EXPECT_EQ((*it).second, ans[ans_id++]); }

    EXPECT_EQ(m.empty(), true);
}

TEST(mapTest, MoveSelfOperator) {
    map<int, int> m{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    m = std::move(m);
}

TEST(mapTest, Begin) {
    map<int, int> m{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    auto begin = m.begin();
    EXPECT_EQ((*begin).first, 1);
}

TEST(mapTest, BeginException) {
    map<int, int> s;
    EXPECT_EQ(s.empty(), true);

    auto begin = s.begin();
    (void) begin;
}

TEST(mapTest, End) {
    map<int, int> m{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    auto begin = m.end();
    EXPECT_EQ((*(--begin)).first, 5);
}

TEST(mapTest, Empty) {
    map<int, int> m;
    EXPECT_EQ(m.empty(), true);
}

TEST(mapTest, Size) {
    map<int, int> m;
    EXPECT_EQ(m.size(), 0);
}

TEST(mapTest, MaxSize) {
    map<int, int> m;
    EXPECT_EQ((bool) m.max_size(), true);
}

TEST(mapTest, Clear) {
    map<int, int> m{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = m.begin(); it != m.end(); ++it) { EXPECT_EQ((*it).second, ans[ans_id++]); }

    m.clear();

    EXPECT_EQ(m.empty(), true);
}

TEST(mapTest, InsertPair) {
    map<int, int> m{{1, 1}, {2, 2}, {4, 4}, {5, 5}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 4);

    m.insert({0, 0});
    m.insert({3, 3});
    m.insert({3, 3});
    m.insert({6, 6});

    EXPECT_EQ(m.size(), 7);
}

TEST(mapTest, InsertKeyVal) {
    map<int, int> m{{1, 1}, {2, 2}, {4, 4}, {5, 5}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 4);

    m.insert(0, 0);
    m.insert(3, 3);
    m.insert(3, 3);
    m.insert(6, 6);

    EXPECT_EQ(m.size(), 7);
}

TEST(mapTest, InsertOrAssign) {
    map<int, int> m{{1, 1}, {2, 2}, {4, 4}, {5, 5}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 4);

    m.insert_or_assign(0, 0);
    EXPECT_EQ(m.size(), 5);
    m.insert_or_assign(3, 3);
    EXPECT_EQ(m.size(), 6);
    m.insert_or_assign(3, 33);
    EXPECT_EQ(m.size(), 6);
}

TEST(mapTest, Balance) {
    map<int, int> m{{1, 1}, {2, 2}, {4, 4}, {5, 5}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 4);

    for(int i = 0; i < 100; ++i) { m.insert({i, i}); }

    int count = 0;

    for(auto it = m.begin(); it != m.end(); ++it) { EXPECT_EQ((*it).second, count++); }
}

TEST(mapTest, Erase) {
    map<int, int> m{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    auto it = m.find(3);
    m.erase(it);

    EXPECT_EQ(m.size(), 4);

    int ans[] = {1, 2, 4, 5};
    int ans_id = 0;

    for(auto it2 = m.begin(); it2 != m.end(); ++it2) { EXPECT_EQ((*it2).second, ans[ans_id++]); }
}

TEST(mapTest, Swap) {
    map<int, int> m{{5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);
    map<int, int> m2{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

    m.swap(m2);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = m.begin(); it != m.end(); ++it) { EXPECT_EQ((*it).second, ans[ans_id++]); }
}

TEST(mapTest, Merge) {
    map<int, int> m{{5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);
    map<int, int> m2{{5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};

    m.merge(m2);

    int ans[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int ans_id = 0;

    for(auto it = m.begin(); it != m.end(); ++it) { EXPECT_EQ((*it).second, ans[ans_id++]); }
}

TEST(mapTest, Find) {
    map<int, int> m{{5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    EXPECT_EQ(m.find(5), --(m.end()));
    EXPECT_EQ(m.find(2), ++(m.begin()));
    EXPECT_EQ(m.find(1), (m.begin()));
}

TEST(mapTest, Contains) {
    map<int, int> m{{5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    EXPECT_EQ(m.contains(1), true);
    EXPECT_EQ(m.contains(2), true);
    EXPECT_EQ(m.contains(3), true);
    EXPECT_EQ(m.contains(4), true);
    EXPECT_EQ(m.contains(5), true);
    EXPECT_EQ(m.contains(0), false);
}

TEST(mapTest, At) {
    map<int, int> m{{5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    EXPECT_EQ(m.at(1), 1);
    EXPECT_EQ(m.at(2), 2);
    EXPECT_EQ(m.at(3), 3);
    EXPECT_EQ(m.at(4), 4);
    EXPECT_EQ(m.at(5), 5);
}

TEST(mapTest, AtException) {
    map<int, int> m{{5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    try {
        m.at(0);
    }
    catch(std::exception& ex) {
        EXPECT_STREQ("Key not found", ex.what());
    }
}

TEST(mapTest, SquareBrackets) {
    map<int, int> m{{5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    EXPECT_EQ(m[1], 1);
    EXPECT_EQ(m[2], 2);
    EXPECT_EQ(m[3], 3);
    EXPECT_EQ(m[4], 4);
    EXPECT_EQ(m[5], 5);
}

TEST(mapTest, InsertMany) {
    map<int, int> m{{5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1}};
    EXPECT_EQ(m.empty(), false);
    EXPECT_EQ(m.size(), 5);

    auto vec = m.insert_many(std::make_pair(5, 5), std::make_pair(6, 6), std::make_pair(7, 7), std::make_pair(8, 8),
                             std::make_pair(9, 9));

    int vect[] = {5, 6, 7, 8, 9};
    int vect_id = 0;

    for(int i = 0; i < 5; ++i) { EXPECT_EQ((*((vec[i]).first)).second, vect[vect_id++]); }

    int ans[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int ans_id = 0;

    for(auto it = m.begin(); it != m.end(); ++it) { EXPECT_EQ((*it).second, ans[ans_id++]); }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    UTIL(RUN_ALL_TESTS());
    return 0;
}
