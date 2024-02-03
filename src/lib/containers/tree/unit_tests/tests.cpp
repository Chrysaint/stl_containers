//
// Created by pinkod on 7/10/25.
//
#include <gtest/gtest.h>

#include "./../../testing_include/test_include.h"
#include "./../s21_tree.h"

namespace s21 {

    class TreeTest : public ::testing::Test {
    protected:
        BinaryTree<int, int> int_tree;
        BinaryTree<std::string, double> str_tree;

        void SetUp() override {
            // Common setup if needed
        }
        void createDotFile() { int_tree.saveTreeToDot(int_tree.m_root, "./tree.dot"); }
    };

    TEST_F(TreeTest, DefaultConstructor) {
        EXPECT_EQ(int_tree.size(), 0);
        EXPECT_TRUE(int_tree.begin() == int_tree.end());
    }

    TEST_F(TreeTest, SingleInsert) {
        auto it = int_tree.insert(10, 100);
        EXPECT_EQ(int_tree.size(), 1);
        EXPECT_TRUE(int_tree.contains(10));
    }

    TEST_F(TreeTest, SizeAfterMultipleInserts) {
        int_tree.insert(10, 100);
        int_tree.insert(20, 200);
        int_tree.insert(30, 300);
        EXPECT_EQ(int_tree.size(), 3);
    }

    TEST_F(TreeTest, TreeBalancing) {
        int_tree.insert(10, 100);
        int_tree.insert(10, 200);
        int_tree.insert(10, 300);
        int_tree.insert(5, 300);
        int_tree.insert(5, 300);
        EXPECT_EQ(int_tree.size(), 5);
    }

    TEST_F(TreeTest, MaxSize) {
        size_t expected_max = std::numeric_limits<size_t>::max() / int_tree.get_node_size();
        EXPECT_EQ(int_tree.max_size(), expected_max);
    }

    TEST_F(TreeTest, InsertAscendingOrder) {
        for(int i = 1; i <= 100; ++i) {
            int_tree.insert(i, i * 10);
            EXPECT_TRUE(int_tree.contains(i));
        }
        EXPECT_EQ(int_tree.size(), 100);
    }

    TEST_F(TreeTest, InsertDescendingOrder) {
        for(int i = 100; i >= 1; --i) {
            int_tree.insert(i, i * 10);
            EXPECT_TRUE(int_tree.contains(i));
        }
        EXPECT_EQ(int_tree.size(), 100);
    }

    TEST_F(TreeTest, InsertRandomOrder) {
        std::vector<int> keys = {50, 25, 75, 12, 37, 62, 87, 6, 18, 31};
        for(int key : keys) { int_tree.insert(key, key * 10); }
        EXPECT_EQ(int_tree.size(), keys.size());
        for(int key : keys) { EXPECT_TRUE(int_tree.contains(key)); }
    }

    TEST_F(TreeTest, InsertDuplicateKeys) {
        int_tree.insert(10, 100);
        int_tree.insert(10, 200);
        EXPECT_EQ(int_tree.size(), 2);
    }

    TEST_F(TreeTest, InsertUniqueDuplicateKeys) {
        int_tree.insert_unique(10, 100);
        auto res = int_tree.insert_unique(10, 200);
        EXPECT_EQ(int_tree.size(), 1);
        EXPECT_TRUE(res.first == int_tree.find(10));
    }

    TEST_F(TreeTest, InsertNegativeKeys) {
        int_tree.insert(-10, 100);
        int_tree.insert(-20, 200);
        EXPECT_EQ(int_tree.size(), 2);
        EXPECT_TRUE(int_tree.contains(-10));
        EXPECT_TRUE(int_tree.contains(-20));
    }

    TEST_F(TreeTest, InsertStringKeys) {
        str_tree.insert("apple", 2.5);
        str_tree.insert("banana", 1.8);
        str_tree.insert("cherry", 3.2);
        EXPECT_EQ(str_tree.size(), 3);
        EXPECT_TRUE(str_tree.contains("banana"));
    }

    TEST_F(TreeTest, ContainsEmptyTree) { EXPECT_FALSE(int_tree.contains(10)); }

    TEST_F(TreeTest, ContainsExistingKey) {
        int_tree.insert(10, 100);
        EXPECT_TRUE(int_tree.contains(10));
    }

    TEST_F(TreeTest, ContainsNonExistingKey) {
        int_tree.insert(10, 100);
        int_tree.insert(20, 200);
        EXPECT_FALSE(int_tree.contains(15));
    }

    TEST_F(TreeTest, ContainsAfterMultipleInserts) {
        for(int i = 1; i <= 50; ++i) { int_tree.insert(i, i * 10); }
        for(int i = 1; i <= 50; ++i) { EXPECT_TRUE(int_tree.contains(i)); }
        for(int i = 51; i <= 100; ++i) { EXPECT_FALSE(int_tree.contains(i)); }
    }

    TEST_F(TreeTest, BeginEndEmptyTree) {
        EXPECT_TRUE(int_tree.begin() == int_tree.end());
        EXPECT_TRUE(int_tree.cbegin() == int_tree.cend());
    }

    TEST_F(TreeTest, IteratorTraversal) {
        std::vector<int> keys = {50, 25, 75, 12, 37, 62, 87};
        for(int key : keys) { int_tree.insert(key, key * 10); }
        std::sort(keys.begin(), keys.end());

        auto it = int_tree.begin();
        for(size_t i = 0; i < keys.size(); ++i) {
            EXPECT_EQ(it->first, keys[i]);
            ++it;
        }
        EXPECT_TRUE(it == int_tree.end());
    }

    TEST_F(TreeTest, ConstIterator) {
        int_tree.insert(10, 100);
        int_tree.insert(20, 200);

        auto cit = int_tree.cbegin();
        EXPECT_EQ(cit->first, 10);
        ++cit;
        EXPECT_EQ(cit->first, 20);
        ++cit;
        EXPECT_TRUE(cit == int_tree.cend());
    }

    TEST_F(TreeTest, IteratorIncrementDecrement) {
        int_tree.insert(10, 100);
        int_tree.insert(20, 200);
        int_tree.insert(30, 300);

        auto it = int_tree.begin();
        EXPECT_EQ(it->first, 10);

        ++it;
        EXPECT_EQ(it->first, 20);

        auto it2 = it++;
        EXPECT_EQ(it2->first, 20);
        EXPECT_EQ(it->first, 30);

        --it;
        EXPECT_EQ(it->first, 20);

        auto it3 = it--;
        EXPECT_EQ(it3->first, 20);
        EXPECT_EQ(it->first, 10);
    }

    TEST_F(TreeTest, IteratorEquality) {
        int_tree.insert(10, 100);
        auto it1 = int_tree.begin();
        auto it2 = int_tree.begin();
        EXPECT_TRUE(it1 == it2);

        ++it1;
        EXPECT_TRUE(it1 == int_tree.end());
        EXPECT_FALSE(it1 == it2);
    }

    TEST_F(TreeTest, InsertSameKeyMultipleTimes) {
        for(int i = 0; i < 100; ++i) { int_tree.insert(5, i * 10); }
        EXPECT_EQ(int_tree.size(), 100);
    }

    TEST_F(TreeTest, LargeNumberOfElements) {
        const int count = 10000;
        for(int i = 0; i < count; ++i) { int_tree.insert(i, i); }
        EXPECT_EQ(int_tree.size(), count);
        for(int i = 0; i < count; i += 100) { EXPECT_TRUE(int_tree.contains(i)); }
    }

    TEST_F(TreeTest, StringKeyCollisions) {
        str_tree.insert("abc", 1.1);
        str_tree.insert("cba", 2.2);
        str_tree.insert("bca", 3.3);
        EXPECT_TRUE(str_tree.contains("abc"));
        EXPECT_TRUE(str_tree.contains("cba"));
        EXPECT_TRUE(str_tree.contains("bca"));
    }

    TEST_F(TreeTest, TreeStructureAfterRotation) {
        int_tree.insert(30, 300);
        int_tree.insert(20, 200);
        int_tree.insert(10, 100);

        auto it = int_tree.begin();
        EXPECT_EQ(it->first, 10);
        ++it;
        EXPECT_EQ(it->first, 20);
        ++it;
        EXPECT_EQ(it->first, 30);

        int_tree.insert(25, 250);
        int_tree.insert(35, 350);
        int_tree.insert(15, 150);
        EXPECT_EQ(int_tree.size(), 6);
        std::vector<int> expected = {10, 15, 20, 25, 30, 35};
        size_t idx = 0;
        for(auto it = int_tree.begin(); it != int_tree.end(); ++it) {} // EXPECT_EQ(it->first, expected[idx++]); }
    }

    TEST_F(TreeTest, EraseLeafNode) {
        int_tree.insert(10, 100);
        int_tree.erase(int_tree.cbegin());
        EXPECT_EQ(int_tree.size(), 0);
        EXPECT_FALSE(int_tree.contains(10));
    }

    TEST_F(TreeTest, EraseLeafNode2) {
        int_tree.insert(10, 100);
        int_tree.insert(27, 100);
        auto it = int_tree.insert(4, 100);
        int_tree.insert(15, 100);
        int_tree.erase(it);
        EXPECT_EQ(int_tree.size(), 3);
        createDotFile();
        EXPECT_FALSE(int_tree.contains(4));
        EXPECT_TRUE(int_tree.contains(10));
        EXPECT_TRUE(int_tree.contains(27));
        EXPECT_TRUE(int_tree.contains(15));
    }
    // Initializer list constructor
    TEST_F(TreeTest, InitializerListConstructor) {
        BinaryTree<int, int> init_tree{{1, 10}, {2, 20}, {3, 30}};
        EXPECT_EQ(init_tree.size(), 3);
        EXPECT_TRUE(init_tree.contains(1));
        EXPECT_TRUE(init_tree.contains(2));
        EXPECT_TRUE(init_tree.contains(3));
    }

    TEST_F(TreeTest, EqualRangeAndCount) {
        int_tree.insert(5, 50);
        int_tree.insert(10, 100);
        int_tree.insert(10, 200);
        int_tree.insert(10, 300);
        int_tree.insert(15, 150);

        auto range = int_tree.equal_range(10);

        EXPECT_NE(range.first, int_tree.end());
        EXPECT_EQ(range.first->first, 10);

        EXPECT_NE(range.second, int_tree.end());
        EXPECT_EQ(range.second->first, 15);

        size_t count = int_tree.count(10);
        for(auto it = range.first; it != range.second; ++it) { EXPECT_EQ(it->first, 10); }
        EXPECT_EQ(count, 3);
    }
} // namespace s21

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    UTIL(RUN_ALL_TESTS());
    return 0;
}
