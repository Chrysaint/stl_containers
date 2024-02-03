//
// Created by pinkod on 7/10/25.
//
#include <gtest/gtest.h>

#include <cstdio>
#include <stdexcept>

#include "./../s21_list.h"
#include "./../testing_include/test_include.h"

using namespace s21;

// Тест конструктора по умолчанию
TEST(ListTest, DefaultConstructor) {
    const list<int> list1;
    EXPECT_TRUE(list1.empty());
    EXPECT_EQ(list1.size(), 0u);
}

// Тест конструктора с размером
TEST(ListTest, SizeConstructor) {
    list<int> list1(5);
    EXPECT_EQ(list1.size(), 5u);
    for(int i = 0; i < 5; ++i) {
        EXPECT_EQ(list1[i], 0); // Проверяем значения по умолчанию
    }
}

// Тест push_back
TEST(ListTest, PushBack) {
    list<int> list1;
    list1.push_back(10);
    EXPECT_EQ(list1.size(), 1u);
    EXPECT_EQ(list1[0], 10);

    list1.push_back(20);
    EXPECT_EQ(list1.size(), 2u);
    EXPECT_EQ(list1[1], 20);
}

// Тест push_front
TEST(ListTest, PushFront) {
    list<int> list1;
    list1.push_front(10);
    EXPECT_EQ(list1.size(), 1u);
    EXPECT_EQ(list1[0], 10);

    list1.push_front(20);
    EXPECT_EQ(list1.size(), 2u);
    EXPECT_EQ(list1[0], 20);
}

// Тест pop_back
TEST(ListTest, PopBack) {
    list<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    list1.pop_back();

    EXPECT_EQ(list1.size(), 1u);
    EXPECT_EQ(list1[0], 10);

    list1.pop_back();
    EXPECT_TRUE(list1.empty());
}

// Тест pop_front
TEST(ListTest, PopFront) {
    list<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    list1.pop_front();

    EXPECT_EQ(list1.size(), 1u);
    EXPECT_EQ(list1[0], 20);

    list1.pop_front();
    EXPECT_TRUE(list1.empty());
}

// Тест оператора []
TEST(ListTest, IndexOperator) {
    list<int> list1;
    list1.push_back(10);
    list1.push_back(20);

    EXPECT_EQ(list1[0], 10);
    EXPECT_EQ(list1[1], 20);

    EXPECT_THROW(list1[2], std::out_of_range); // Проверка исключения
}

// Тест метода clear
TEST(ListTest, Clear) {
    list<int> list1(5);
    EXPECT_EQ(list1.size(), 5u);

    list1.clear();
    EXPECT_TRUE(list1.empty());
}

// Тест swap
TEST(ListTest, Swap) {
    list<int> list1(3);
    list<int> list2(2);

    list1.swap(list2);

    EXPECT_EQ(list1.size(), 2u);
    EXPECT_EQ(list2.size(), 3u);
}

// Тест reverse
TEST(ListTest, Reverse) {
    list<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    list1.reverse();

    EXPECT_EQ(list1[0], 3);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 1);
}

TEST(ListTest, ReverseEmpty) {
    list<int> list1{1, 2, 3, 4};
    list1.reverse();

    EXPECT_EQ(list1[0], 4);
    EXPECT_EQ(list1[1], 3);
    EXPECT_EQ(list1[2], 2);
    EXPECT_EQ(list1[3], 1);
}
// Тест unique
TEST(ListTest, Unique) {
    list<int> list1;
    list1.push_back(1);
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(3);

    list1.unique();

    EXPECT_EQ(list1.size(), 3u);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 3);
}

// Тест merge
TEST(ListTest, Merge) {
    list<int> list1;
    list<int> list2;

    list1.push_back(1);
    list1.push_back(2);

    list2.push_back(3);
    list2.push_back(4);

    list1.merge(list2);

    EXPECT_EQ(list1.size(), 4u);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 3);
    EXPECT_EQ(list1[3], 4);

    EXPECT_TRUE(list2.empty()); // Проверка, что list2 очистился
}

// Тест итераторов
TEST(ListTest, IteratorTest) {
    list<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);

    // Проверка итераторов с использованием цикла
    int expected[] = {10, 20, 30};
    int index = 0;
    for(auto it = list1.begin(); it != list1.end(); ++it) {
        EXPECT_EQ(*it, expected[index]);
        ++index;
    }
}

// Тест для итератора: разыменование итератора на пустом списке
TEST(ListTest, IteratorDereferenceOnEmptyList) {
    list<int> list1;

    auto it = list1.begin();
    EXPECT_THROW(*it, std::out_of_range); // Разыменование на пустом списке
                                          // должно вызвать исключение
}

// Тест для const_iterator
TEST(ListTest, ConstIteratorTest) {
    list<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    const list<int>& constList = list1;

    int expected[] = {1, 2, 3};
    int index = 0;
    for(auto it = constList.cbegin(); it != constList.cend(); ++it) {
        EXPECT_EQ(*it, expected[index]);
        ++index;
    }
}

// Тест работы итераторов на пустом списке
TEST(ListTest, IteratorOnEmptyList) {
    list<int> list1;

    auto it = list1.begin();
    auto constIt = list1.begin();

    // Итераторы на пустом списке должны быть равны `end()`
    EXPECT_EQ(it, list1.end());
    EXPECT_EQ(constIt, list1.end());
}

// Тест копирования и присваивания итераторов
TEST(ListTest, IteratorCopyAndAssignment) {
    list<int> list1;
    list1.push_back(10);
    list1.push_back(20);

    auto it1 = list1.begin();
    auto it2 = it1; // Копирование итератора

    EXPECT_EQ(*it1, 10);
    EXPECT_EQ(*it2, 10);

    ++it1;
    EXPECT_EQ(*it1, 20); // Убедимся, что it1 изменился
    EXPECT_EQ(*it2, 10); // it2 не должен измениться

    it2 = it1; // Присваивание итератора
    EXPECT_EQ(*it2, 20);
}

// Тест вставки в начало списка
TEST(ListTest, InsertAtBeginning) {
    list<int> list1;
    list1.push_back(2);
    list1.push_back(3);

    auto it = list1.insert(list1.begin(), 1);

    EXPECT_EQ(list1.size(), 3u);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 3);
    EXPECT_EQ(*it, 1); // Проверка, что итератор указывает на новый элемент
}

// Тест вставки в середину списка
TEST(ListTest, InsertInMiddle) {
    list<int> list1;
    list1.push_back(1);
    list1.push_back(3);

    auto it = list1.insert(++list1.begin(), 2);

    EXPECT_EQ(list1.size(), 3u);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 3);
    EXPECT_EQ(*it, 2); // Проверка, что итератор указывает на новый элемент
}

// Тест вставки в конец списка
TEST(ListTest, InsertAtEnd) {
    list<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    auto it = list1.insert(list1.end(), 3);

    EXPECT_EQ(list1.size(), 3u);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 3);
    EXPECT_EQ(*it, 3); // Проверка, что итератор указывает на новый элемент
}

// Тест вставки в пустой список
TEST(ListTest, InsertInEmptyList) {
    list<int> list1;

    auto it = list1.insert(list1.begin(), 1);

    EXPECT_EQ(list1.size(), 1u);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(*it, 1); // Проверка, что итератор указывает на новый элемент
}

// Тест удаления из начала списка
TEST(ListTest, EraseAtBeginning) {
    list<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    auto it = list1.begin();
    list1.erase(it);

    EXPECT_EQ(list1.size(), 2u);
    EXPECT_EQ(list1[0], 2);
    EXPECT_EQ(list1[1], 3);
}

// Тест удаления из середины списка
TEST(ListTest, EraseInMiddle) {
    list<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    auto it = ++list1.begin(); // Указатель на второй элемент
    list1.erase(it);

    EXPECT_EQ(list1.size(), 2u);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 3);
}

// Тест удаления из пустого списка
TEST(ListTest, EraseFromEmptyList) {
    list<int> list1;
    EXPECT_THROW(list1.erase(list1.begin()), std::out_of_range);
}

// Тест удаления с использованием end()
TEST(ListTest, EraseEndIterator) {
    list<int> list1;
    list1.push_back(1);
    EXPECT_THROW(list1.erase(list1.end()), std::out_of_range);
}

TEST(ListTest, SpliceAtBeginning) {
    list<int> list1;
    list<int> list2;

    list1.push_back(3);
    list1.push_back(4);

    list2.push_back(1);
    list2.push_back(2);

    list1.splice(list1.cbegin(), list2);

    EXPECT_EQ(list1.size(), 4u);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 3);
    EXPECT_EQ(list1[3], 4);
    EXPECT_TRUE(list2.empty());
}

// Тест для метода splice
TEST(ListTest, Splice) {
    list<int> list1;
    list<int> list2;
    // Заполняем первый список
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    // Заполняем второй список
    list2.push_back(4);
    list2.push_back(5);

    // Используем splice для вставки второго списка в первый
    list1.splice(list1.cend(), list2);

    // Проверяем размер и содержимое первого списка
    EXPECT_EQ(list1.size(), 5u);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 3);
    EXPECT_EQ(list1[3], 4);
    EXPECT_EQ(list1[4], 5);

    // Проверяем, что второй список пуст
    EXPECT_TRUE(list2.empty());
}

// Тест для метода splice, когда второй список пуст
TEST(ListTest, SpliceEmptyList) {
    list<int> list1;
    list<int> list2;

    // Заполняем первый список
    list1.push_back(1);
    list1.push_back(2);

    // Используем splice с пустым вторым списком
    list1.splice(list1.cend(), list2);

    // Проверяем размер и содержимое первого списка
    EXPECT_EQ(list1.size(), 2u);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 2);
}

// Тест для метода sort
TEST(ListTest, Sort) {
    list<int> list1;
    list1.push_back(3);
    list1.push_back(1);
    list1.push_back(4);
    list1.push_back(2);

    list1.sort();

    EXPECT_EQ(list1.size(), 4u);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 3);
    EXPECT_EQ(list1[3], 4);
}

// Тест для метода sort с уже отсортированным списком
TEST(ListTest, SortAlreadySorted) {
    list<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);

    list1.sort();

    EXPECT_EQ(list1.size(), 4u);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 3);
    EXPECT_EQ(list1[3], 4);
}

// Тест для метода sort с пустым списком
TEST(ListTest, SortEmptyList) {
    list<int> list1;

    list1.sort();

    EXPECT_TRUE(list1.empty());
}

// Тест для метода sort с одним элементом
TEST(ListTest, SortSingleElement) {
    list<int> list1;
    list1.push_back(42);

    list1.sort();

    EXPECT_EQ(list1.size(), 1u);
    EXPECT_EQ(list1[0], 42);
}

// Тест для метода sort с дубликатами
TEST(ListTest, SortWithDuplicates) {
    list<int> list1;
    list1.push_back(3);
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(2);

    list1.sort();

    EXPECT_EQ(list1.size(), 5u);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 2);
    EXPECT_EQ(list1[3], 3);
    EXPECT_EQ(list1[4], 3);
}

TEST(ListTest, InitializerListConstructor) {
    list<int> list1{1, 2, 3, 4, 5};
    EXPECT_EQ(list1.size(), 5u);
    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 3);
    EXPECT_EQ(list1[3], 4);
    EXPECT_EQ(list1[4], 5);
}

// Тест конструктора копирования
TEST(ListTest, CopyConstructor) {
    list<int> original{1, 2, 3};
    list<int> copy(original);

    EXPECT_EQ(copy.size(), 3u);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
    EXPECT_EQ(copy[2], 3);

    // Убедимся, что изменения в копии не влияют на оригинал
    copy[0] = 52;
    EXPECT_EQ(copy[0], 52);
    EXPECT_EQ(original[0], 1);
}

// Тест конструктора перемещения
TEST(ListTest, MoveConstructor) {
    list<int> original{1, 2, 3};
    list<int> moved(std::move(original));

    EXPECT_EQ(moved.size(), 3u);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[1], 2);
    EXPECT_EQ(moved[2], 3);

    // Убедимся, что оригинальный список стал пустым
    EXPECT_TRUE(original.empty());
}

// Тест оператора присваивания перемещением
TEST(ListTest, MoveAssignmentOperator) {
    list<int> original{1, 2, 3};
    list<int> moved;
    moved = std::move(original);

    EXPECT_EQ(moved.size(), 3u);
    EXPECT_EQ(moved[0], 1);
    EXPECT_EQ(moved[1], 2);
    EXPECT_EQ(moved[2], 3);

    // Убедимся, что оригинальный список стал пустым
    EXPECT_TRUE(original.empty());
}

TEST(ListTest, InsertMany) {
    list<int> list{1, 2, 3};
    auto it = list.cbegin();
    ++it;
    list.insert_many(it, 4, 5, 6);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 4);
    EXPECT_EQ(list[2], 5);
    EXPECT_EQ(list[3], 6);
    EXPECT_EQ(list[4], 2);
    EXPECT_EQ(list[5], 3);
    EXPECT_EQ(list.size(), 6);

    EXPECT_THROW(list.insert_many(++list.cend(), 6, 7, 8), std::out_of_range);
}

TEST(ListTest, InsertManyBack) {
    list<int> list1{1, 2, 3};
    list1.insert_many_back(4, 5, 6);
    EXPECT_EQ(list1[2], 3);
    EXPECT_EQ(list1[3], 4);
    EXPECT_EQ(list1[4], 5);
    EXPECT_EQ(list1[5], 6);
    EXPECT_EQ(list1.size(), 6);

    list<int> list2;
    list2.insert_many_back(4, 5, 6);

    EXPECT_EQ(list2[0], 4);
    EXPECT_EQ(list2[1], 5);
    EXPECT_EQ(list2[2], 6);
}

TEST(ListTest, InsertManyFront) {
    list<int> list1{1, 2, 3};
    list1.insert_many_front(4, 5, 6);
    EXPECT_EQ(list1[0], 4);
    EXPECT_EQ(list1[1], 5);
    EXPECT_EQ(list1[2], 6);
    EXPECT_EQ(list1[3], 1);
    EXPECT_EQ(list1[4], 2);
    EXPECT_EQ(list1[5], 3);
    EXPECT_EQ(list1.size(), 6);

    list<int> list2;
    list2.insert_many_front(4, 5, 6);

    EXPECT_EQ(list2[0], 4);
    EXPECT_EQ(list2[1], 5);
    EXPECT_EQ(list2[2], 6);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    UTIL(RUN_ALL_TESTS());
    return 0;
}
