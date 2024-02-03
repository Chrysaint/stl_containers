//
// Created by pinkod on 7/10/25.
//
#include <gtest/gtest.h>

#include <stdexcept>

#include "./../s21_array.h"
#include "./../testing_include/test_include.h"

using namespace s21;

TEST(arrayTest, DefaultConstructor) {
    array<int, 5> q;
    EXPECT_EQ(q.empty(), false);
}

TEST(arrayTest, ListConstructor) {
    array<int, 5> a{1, 2, 3, 4, 5};
    EXPECT_EQ(a.empty(), false);
    EXPECT_EQ(a.size(), 5);

    int ans[]{1, 2, 3, 4, 5};

    for(size_t i = 0; i < a.size(); ++i) { EXPECT_EQ(a[i], ans[i]); }
}

TEST(arrayTest, CopyConstructor) {
    array<int, 5> b{1, 2, 3, 4, 5};
    array<int, 5> a(b);

    int ans[]{1, 2, 3, 4, 5};

    for(size_t i = 0; i < a.size(); ++i) { EXPECT_EQ(a[i], ans[i]); }
}

TEST(arrayTest, CopyConstructorException) {
    try {
        array<int, 6> b{1, 2, 3, 4, 5, 6, 7, 8, 9};
    }
    catch(std::exception& ex) {
        EXPECT_STREQ("Too many items", ex.what());
    }
}

TEST(arrayTest, MoveConstructor) {
    array<int, 5> arr1{1, 2, 3, 4, 5};
    array<int, 5> arr2(std::move(arr1));

    for(size_t i = 0; i < arr2.size(); ++i) { EXPECT_EQ(arr2[i], i + 1); }
}

TEST(arrayTest, MoveOperator) {
    array<int, 5> a{1, 2, 3, 4, 5};

    int ans[]{1, 2, 3, 4, 5};

    array<int, 5> a2;
    a2 = std::move(a);

    for(size_t i = 0; i < a.size(); ++i) { EXPECT_EQ(a2[i], ans[i]); }
}

TEST(arrayTest, Front) {
    array<int, 5> a{1, 2, 3, 4, 5};
    EXPECT_EQ(a.front(), 1);
}

TEST(arrayTest, At) {
    array<int, 5> a{1, 2, 3, 4, 5};
    EXPECT_EQ(a.at(1), 2);
}

TEST(arrayTest, AtException) {
    array<int, 5> a{1, 2, 3, 4, 5};
    EXPECT_THROW(a.at(5), std::out_of_range);
}

TEST(arrayTest, Back) {
    array<int, 5> a{1, 2, 3, 4, 5};
    EXPECT_EQ(a.back(), 5);
}

TEST(arrayTest, Data) {
    array<int, 5> a{1, 2, 3, 4, 5};
    EXPECT_EQ(*a.data(), 1);
}

TEST(arrayTest, Begin) {
    array<int, 5> a{1, 2, 3, 4, 5};
    EXPECT_EQ(*a.begin(), 1);
}

TEST(arrayTest, End) {
    array<int, 5> a{1, 2, 3, 4, 5};
    EXPECT_EQ(*(a.end() - 1), 5);
}

TEST(arrayTest, Empty) {
    array<int, 5> a;
    EXPECT_EQ(a.empty(), false);
}

TEST(arrayTest, Size) {
    array<int, 5> a;
    EXPECT_EQ(a.size(), 5);
}

TEST(arrayTest, Maxsize) {
    array<int, 5> a;
    EXPECT_EQ(a.max_size(), 5);
}

TEST(arrayTest, Swap) {
    array<int, 5> a{3, 4, 3, 4, 5};
    array<int, 5> b{1, 2, 3, 4, 5};

    int ans[]{1, 2, 3, 4, 5};
    int ans2[]{3, 4, 3, 4, 5};

    for(size_t i = 0; i < a.size(); ++i) { EXPECT_EQ(a[i], ans2[i]); }

    for(size_t i = 0; i < b.size(); ++i) { EXPECT_EQ(b[i], ans[i]); }

    a.swap(b);

    for(size_t i = 0; i < a.size(); ++i) { EXPECT_EQ(a[i], ans[i]); }

    for(size_t i = 0; i < b.size(); ++i) { EXPECT_EQ(b[i], ans2[i]); }
}

TEST(arrayTest, Fill) {
    array<int, 5> a;
    a.fill(5);

    int ans[]{5, 5, 5, 5, 5};

    for(size_t i = 0; i < a.size(); ++i) { EXPECT_EQ(a[i], ans[i]); }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    UTIL(RUN_ALL_TESTS());
    return 0;
}
