#ifndef S21_CONTAINERS_MULTISET
#define S21_CONTAINERS_MULTISET

#include <functional>

#include "./../tree/s21_tree.h"
#include "./../vector/s21_vector.h"

namespace s21 {
    template <typename TKey, typename Compare = std::less<TKey>>
    class multiset {
    private:
        BinaryTree<TKey, TKey, Compare, const TKey> m_tree;

    public:
        using key_type = TKey;
        using value_type = TKey;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = typename BinaryTree<TKey, TKey, Compare, const TKey>::iterator;
        using const_iterator = typename BinaryTree<TKey, TKey, Compare, const TKey>::const_iterator;
        using size_type = size_t;

        multiset() = default;

        explicit multiset(std::initializer_list<TKey> const& list) {
            for(const auto& value : list) insert(value);
        }

        multiset(const multiset& other) : m_tree(other.m_tree) {};
        multiset(multiset&& other) noexcept = default;

        multiset& operator=(multiset&& other) noexcept = default;

        multiset& operator=(const multiset& other) {
            if(this != &other) { m_tree = other.m_tree; }
            return *this;
        }
        ~multiset() = default;

        iterator begin() const { return m_tree.begin(); }
        iterator end() const { return m_tree.end(); }
        bool empty() const { return m_tree.empty(); }
        size_type size() const { return m_tree.size(); }
        size_type max_size() const { return m_tree.max_size(); }
        void clear() { m_tree.clear(); }

        iterator insert(const value_type& value) { return m_tree.insert(value, value); }

        // cppcheck-suppress passedByValue
        void erase(iterator pos) { m_tree.erase(pos); }
        void swap(multiset& other) { m_tree.swap(other.m_tree); }
        void merge(multiset& other) { m_tree.merge(other.m_tree); }

        size_type count(const key_type& key) const { return m_tree.count(key); }
        iterator find(const key_type& key) const { return m_tree.find(key); }
        bool contains(const key_type& key) const { return m_tree.contains(key); }

        std::pair<iterator, iterator> equal_range(const key_type& key) const { return m_tree.equal_range(key); }

        iterator lower_bound(const key_type& key) const { return m_tree.lower_bound(key); }
        iterator upper_bound(const key_type& key) const { return m_tree.upper_bound(key); }

        template <typename... Args>
        s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
            s21::vector<std::pair<iterator, bool>> result;
            (result.push_back({insert(std::forward<Args>(args)), true}), ...);
            return result;
        }
    };
} // namespace s21
#endif
