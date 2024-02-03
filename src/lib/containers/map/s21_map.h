#ifndef S21_CONTAINERS_MAP
#define S21_CONTAINERS_MAP

#include <functional>

#include "./../tree/s21_tree.h"
#include "./../vector/s21_vector.h"

namespace s21 {
    template <typename TKey, typename TValue, typename Compare = std::less<TKey>>
    class map {
    private:
        BinaryTree<TKey, TValue, Compare, std::pair<const TKey, TValue>> m_tree;

    public:
        using key_type = TKey;
        using mapped_type = TValue;
        using value_type = std::pair<const key_type, mapped_type>;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = typename BinaryTree<TKey, TValue, Compare, value_type>::iterator;
        using const_iterator = typename BinaryTree<TKey, TValue, Compare, value_type>::const_iterator;
        using size_type = size_t;

        map() = default;

        explicit map(std::initializer_list<value_type> const& list) {
            for(const auto& value : list) insert(value);
        }

        map(const map& other) : m_tree(other.m_tree) {};
        map(map&& other) noexcept = default;

        map& operator=(map&& other) noexcept = default;

        map& operator=(const map& other) {
            if(this != &other) { m_tree = other.m_tree; }
            return *this;
        }

        bool operator==(const map& other) const noexcept { return m_tree == other.m_tree; }
        mapped_type& operator[](const key_type& key) { return at(key); }

        const mapped_type& operator[](const key_type& key) const { return at(key); }

        ~map() = default;

        mapped_type& at(const key_type& key) {
            iterator it = m_tree.find(key);
            if(it == m_tree.end()) {
                auto res = insert({key, mapped_type()});
                return (*res.first).second;
            }
            return (*it).second;
        }

        iterator begin() const { return m_tree.begin(); }
        iterator end() const { return m_tree.end(); }
        bool empty() const { return m_tree.empty(); }
        size_type size() const { return m_tree.size(); }
        size_type max_size() const { return m_tree.max_size(); }
        void clear() { m_tree.clear(); }

        std::pair<iterator, bool> insert(const value_type& value) { return m_tree.insert_unique(value.first, value.second); }

        std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj) { return m_tree.insert_unique(key, obj); }

        // cppcheck-suppress unusedFunction
        std::pair<iterator, bool> insert_or_assign(const key_type& key, const mapped_type& obj) {
            std::pair<iterator, bool> res = m_tree.insert_unique(key, obj);
            if(res.first == end()) { (*m_tree.find(key)).second = obj; }
            return res;
        }

        // cppcheck-suppress passedByValue
        void erase(iterator pos) { m_tree.erase(pos); }
        void swap(map& other) noexcept { m_tree.swap(other.m_tree); }
        void merge(map& other) {
            if(*this == other) return;
            for(iterator it = other.begin(); it != other.end(); ++it) { insert(*it); }
            other.clear();
        }

        iterator find(const key_type& key) const { return m_tree.find(key); }
        bool contains(const key_type& key) const { return m_tree.contains(key); }

        template <typename... Args>
        s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
            s21::vector<std::pair<iterator, bool>> result;
            result.reserve(sizeof...(args));
            (result.push_back(insert(std::forward<Args>(args))), ...);
            return result;
        }
    };
} // namespace s21
#endif
