#ifndef S21_CONTAINERS_MULTISET
#define S21_CONTAINERS_MULTISET

#include <functional>

#include "./../tree/s21_tree.h"
#include "./../vector/s21_vector.h"

namespace s21 {
    template <typename TKey, typename Compare = std::less<TKey>>
    class set {
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

        set() = default;

        explicit set(std::initializer_list<TKey> const& list) {
            for(const auto& value : list) insert(value);
        }

        set(const set& other) : m_tree(other.m_tree) {};
        set(set&& other) noexcept = default;

        set& operator=(set&& other) noexcept = default;

        set& operator=(const set& other) {
            if(this != &other) { m_tree = other.m_tree; }
            return *this;
        }

        bool operator==(const set& other) const noexcept { return m_tree == other.m_tree; }
        ~set() = default;

        iterator begin() const { return m_tree.begin(); }
        iterator end() const { return m_tree.end(); }
        bool empty() const { return m_tree.empty(); }
        size_type size() const { return m_tree.size(); }
        size_type max_size() const { return m_tree.max_size(); }
        void clear() { m_tree.clear(); }

        std::pair<iterator, bool> insert(const value_type& value) { return m_tree.insert_unique(value, value); }

        // cppcheck-suppress passedByValue
        void erase(iterator pos) { m_tree.erase(pos); }
        void swap(set& other) noexcept { m_tree.swap(other.m_tree); }
        void merge(set& other) {
            if(*this == other) return;
            for(iterator it = other.begin(); it != other.end(); ++it) { insert(*it); }
            other.clear();
        }
        iterator find(const key_type& key) const { return m_tree.find(key); }
        bool contains(const key_type& key) const { return m_tree.contains(key); }

        template <typename... Args>
        s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
            s21::vector<std::pair<iterator, bool>> result;
            (result.push_back(insert(std::forward<Args>(args))), ...);
            return result;
        }
    };
} // namespace s21
#endif
