//
// Created by pinkod on 7/10/25.
//
#include <gtest/gtest.h>

#include "./../s21_set.h"
#include "./../testing_include/test_include.h"

using namespace s21;

TEST(SetTest, DefaultConstructor) {
    set<int> s;
    EXPECT_EQ(s.empty(), true);
}

TEST(SetTest, ListConstructor) {
    set<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = s.begin(); it != s.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }
}

TEST(SetTest, CopyConstructor) {
    set<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    set<int> s2 = s;

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = s2.begin(); it != s2.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }

    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);
}

TEST(SetTest, MoveConstructor) {
    set<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    set<int> s2 = std::move(s);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = s2.begin(); it != s2.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }

    EXPECT_EQ(s.empty(), true);
}

TEST(SetTest, MoveOperator) {
    set<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    set<int> s2;
    s2 = std::move(s);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = s2.begin(); it != s2.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }

    EXPECT_EQ(s.empty(), true);
}

TEST(SetTest, MoveSelfOperator) {
    set<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    s = std::move(s);
}

TEST(SetTest, Begin) {
    set<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    auto begin = s.begin();
    EXPECT_EQ(*begin, 1);
}

TEST(SetTest, End) {
    set<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    auto begin = s.end();
    EXPECT_EQ(*(--begin), 5);
}

TEST(SetTest, BeginException) {
    set<int> s;
    EXPECT_EQ(s.empty(), true);

    auto begin = s.begin();
    (void) begin;
}

TEST(SetTest, Empty) {
    set<int> s;
    EXPECT_EQ(s.empty(), true);
}

TEST(SetTest, Size) {
    set<int> s;
    EXPECT_EQ(s.size(), 0);
}

TEST(SetTest, MaxSize) {
    set<int> s;
    EXPECT_EQ((bool) s.max_size(), true);
}

TEST(SetTest, Clear) {
    set<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = s.begin(); it != s.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }

    s.clear();

    EXPECT_EQ(s.empty(), true);
}

TEST(SetTest, Insert) {
    set<int> s{1, 2, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 4);

    s.insert(0);
    s.insert(3);
    s.insert(3);
    s.insert(6);

    EXPECT_EQ(s.size(), 7);
}

TEST(SetTest, Balance) {
    set<int> s{1, 2, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 4);

    for(int i = 0; i < 100; ++i) { s.insert(i); }

    int count = 0;

    for(auto it = s.begin(); it != s.end(); ++it) { EXPECT_EQ(*it, count++); }
}

TEST(SetTest, Erase) {
    set<int> s{1, 2, 3, 4, 5};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    auto it = s.find(3);
    s.erase(it);

    EXPECT_EQ(s.size(), 4);

    int ans[] = {1, 2, 4, 5};
    int ans_id = 0;

    for(auto it2 = s.begin(); it2 != s.end(); ++it2) { EXPECT_EQ(*it2, ans[ans_id++]); }
}

TEST(SetTest, Swap) {
    set<int> s{5, 4, 3, 2, 1};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);
    set<int> s2{1, 2, 3, 4, 5};

    s.swap(s2);

    int ans[] = {1, 2, 3, 4, 5};
    int ans_id = 0;

    for(auto it = s.begin(); it != s.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }
}

TEST(SetTest, Merge) {
    set<int> s{5, 4, 3, 2, 1};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);
    set<int> s2{5, 6, 7, 8, 9};

    s.merge(s2);

    int ans[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int ans_id = 0;

    for(auto it = s.begin(); it != s.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }
}

TEST(SetTest, Find) {
    set<int> s{5, 4, 3, 2, 1};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    EXPECT_EQ(s.find(5), --(s.end()));
    EXPECT_EQ(s.find(2), ++(s.begin()));
    EXPECT_EQ(s.find(1), (s.begin()));
}

TEST(SetTest, Contains) {
    set<int> s{5, 4, 3, 2, 1};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    EXPECT_EQ(s.contains(1), true);
    EXPECT_EQ(s.contains(2), true);
    EXPECT_EQ(s.contains(3), true);
    EXPECT_EQ(s.contains(4), true);
    EXPECT_EQ(s.contains(5), true);
    EXPECT_EQ(s.contains(0), false);
}

TEST(SetTest, InsertMany) {
    set<int> s{5, 4, 3, 2, 1};
    EXPECT_EQ(s.empty(), false);
    EXPECT_EQ(s.size(), 5);

    auto vec = s.insert_many(5, 6, 7, 8, 9);

    int vect[] = {5, 6, 7, 8, 9};
    int vect_id = 0;

    for(int i = 0; i < 5; ++i) { EXPECT_EQ(*((vec[i]).first), vect[vect_id++]); }

    int ans[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int ans_id = 0;

    for(auto it = s.begin(); it != s.end(); ++it) { EXPECT_EQ(*it, ans[ans_id++]); }
}

TEST(SetIteratorTest, DecrementOperator) {
    set<int> s{10, 20, 30, 40};

    auto it = s.find(30);
    --it;

    EXPECT_EQ(*it, 20);
}

TEST(SetIteratorTest, DecrementOperator2) {
    set<int> s{10, 20, 30, 40};

    auto it = s.find(40);
    --it;

    EXPECT_EQ(*it, 30);
    --it;

    EXPECT_EQ(*it, 20);
    --it;

    EXPECT_EQ(*it, 10);
}

TEST(SetEraseTest, EraseTwoChild) {
    set<int> s{10, 5, 15, 12, 20};

    auto it = s.find(15);
    s.erase(it);

    EXPECT_EQ(s.find(15), s.end());
    EXPECT_EQ(*s.find(12), 12);
}

TEST(SetEraseTest, EraseOneChild) {
    set<int> s{10, 5, 15};

    auto it = s.find(5);
    s.erase(it);

    EXPECT_EQ(s.find(5), s.end());
    EXPECT_EQ(*s.find(15), 15);
}

TEST(SetEraseTest, EraseNoChild) {
    set<int> s{10, 5, 15};

    auto it = s.find(5);
    s.erase(it);

    EXPECT_EQ(s.find(5), s.end());
}

TEST(SetEraseTest, EraseRoot) {
    set<int> s{10, 5, 15};

    auto it = s.find(10);
    s.erase(it);

    EXPECT_EQ(s.find(10), s.end());
    EXPECT_EQ(*s.find(5), 5);
}

TEST(SetEraseTest, EraseNoChild2) {
    set<int> s{10, 5, 15, 30};

    auto it = s.find(5);
    s.erase(it);

    EXPECT_EQ(s.find(5), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseChild3) {
    set<int> s{10, 5, 15, 3};

    auto it = s.find(5);
    s.erase(it);

    EXPECT_EQ(s.find(5), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseChild4) {
    set<int> s{10, 5, 15, 2, 6};

    auto it = s.find(15);
    s.erase(it);

    EXPECT_EQ(s.find(15), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseChild5) {
    set<int> s{10, 5, 15, 20, 25, 17};

    auto it = s.find(5);
    s.erase(it);

    EXPECT_EQ(s.find(5), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseChild6) {
    set<int> s{10, 5, 15, 20, 25, 30};

    auto it = s.find(15);
    s.erase(it);

    EXPECT_EQ(s.find(15), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseChild7) {
    set<int> s{10, 20, 25, 30, 40, 35, 50};

    auto it = s.find(20);
    s.erase(it);

    EXPECT_EQ(s.find(20), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseRoot2) {
    set<int> s{10, 20, 25, 30, 40, 35, 50};

    auto it = s.find(30);
    s.erase(it);

    EXPECT_EQ(s.find(30), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseLeaf2) {
    set<int> s{10, 20, 25, 30, 40, 50};

    auto it = s.find(25);
    s.erase(it);

    EXPECT_EQ(s.find(25), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseLeaf3) {
    set<int> s{10, 20, 25, 30, 40, 35, 50};

    auto it = s.find(25);
    s.erase(it);

    EXPECT_EQ(s.find(25), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseLeaf4) {
    set<int> s{10, 20, 25, 30, 40, 35, 50};

    auto it = s.find(10);
    s.erase(it);

    EXPECT_EQ(s.find(10), s.end());
    EXPECT_EQ(*s.find(25), 25);
}

TEST(SetEraseTest, EraseLeaf5) {
    set<int> s{10, 20, 25, 30, 40, 35, 50};

    auto it = s.find(50);
    s.erase(it);

    EXPECT_EQ(s.find(50), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseLeaf6) {
    set<int> s{10, 20, 25, 30, 40, 35, 50};

    auto it = s.find(35);
    s.erase(it);

    EXPECT_EQ(s.find(35), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseComplement) {
    set<int> s{10, 20, 25, 30, 40, 50, 70, 60, 55, 80};

    auto it = s.find(25);
    s.erase(it);

    EXPECT_EQ(s.find(25), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseComplement2) {
    set<int> s{10, 20, 25, 30, 40, 50, 70, 60, 55, 80};

    auto it = s.find(40);
    s.erase(it);

    EXPECT_EQ(s.find(40), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseComplement3) {
    set<int> s{10, 20, 25, 30, 40, 50, 70, 60, 55, 80};

    auto it = s.find(55);
    s.erase(it);

    EXPECT_EQ(s.find(55), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseComplement4) {
    set<int> s{10, 20, 25, 30, 40, 50, 70, 60, 55, 80};

    auto it = s.find(20);
    s.erase(it);

    EXPECT_EQ(s.find(20), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseComplement5) {
    set<int> s{10, 20, 25, 30, 40, 50, 70, 60, 55, 80};

    auto it = s.find(60);
    s.erase(it);

    EXPECT_EQ(s.find(60), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseComplement6) {
    set<int> s{10, 20, 25, 30, 40, 50, 70, 60, 55, 80};

    auto it = s.find(80);
    s.erase(it);

    EXPECT_EQ(s.find(80), s.end());
    EXPECT_EQ(*s.find(10), 10);
}

TEST(SetEraseTest, EraseRoot3) {
    set<int> s{10, 20, 25, 30, 40, 50, 70, 60, 55, 80};

    auto it = s.find(50);
    s.erase(it);

    EXPECT_EQ(s.find(50), s.end());
    EXPECT_EQ(*s.find(10), 10);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    UTIL(RUN_ALL_TESTS());
    return 0;
}
