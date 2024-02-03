#ifndef S21_CONTAINERS_VECTOR
#define S21_CONTAINERS_VECTOR

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {
    template <typename T>
    class vector {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = T*;
        using const_iterator = const T*;
        using size_type = size_t;

    private:
        T* m_data;
        size_t m_size;
        size_t m_capacity;

        void check_capacity() {
            if(m_size + 1 >= m_capacity) { reserve(m_capacity * 2); }
        }

        T* resize(T* old_data, const size_t new_capacity) {
            if(new_capacity == 0) {
                delete[] old_data;
                return nullptr;
            }

            T* new_data = new T[new_capacity];

            try {
                for(size_t i = 0; i < m_size; ++i) { new_data[i] = std::move(old_data[i]); }
            }
            catch(...) {
                delete[] new_data;
                throw std::bad_alloc();
            }

            delete[] old_data;
            return new_data;
        }

    public:
        vector() : m_data(nullptr), m_size(0), m_capacity(0) { reserve(5); }

        explicit vector(size_type n) : m_data(nullptr), m_size(0), m_capacity(0) {
            reserve(n);
            m_size = n;
            std::fill_n(m_data, n, T());
        }

        explicit vector(std::initializer_list<value_type> const& items) : m_data(nullptr), m_size(0), m_capacity(0) {
            reserve(items.size());
            m_size = items.size();
            std::copy(items.begin(), items.end(), m_data);
        }

        vector(const vector<T>& v) : m_data(nullptr), m_size(0), m_capacity(0) {
            reserve(v.m_size);
            m_size = v.m_size;
            std::copy(v.m_data, v.m_data + v.m_size, m_data);
        }

        vector(vector<T>&& v) noexcept : m_data(v.m_data), m_size(v.m_size), m_capacity(v.m_capacity) {
            v.m_data = nullptr;
            v.m_size = 0;
            v.m_capacity = 0;
        }

        ~vector() { delete[] m_data; }

        vector& operator=(vector&& v) noexcept {
            if(this != &v) {
                delete[] m_data;
                m_data = v.m_data;
                m_size = v.m_size;
                m_capacity = v.m_capacity;
                v.m_data = nullptr;
                v.m_size = 0;
                v.m_capacity = 0;
            }
            return *this;
        }

        vector& operator=(std::initializer_list<value_type> const& items) {
            reserve(items.size());
            m_size = items.size();
            std::copy(items.begin(), items.end(), m_data);
            return *this;
        }

        // cppcheck-suppress passedByValue
        reference at(size_type pos) const {
            if(pos >= m_size) { throw std::out_of_range("Index out of range"); }
            return m_data[pos];
        }

        // cppcheck-suppress passedByValue
        reference operator[](size_type pos) const {
            if(pos >= m_size) { throw std::out_of_range("Hello world"); }
            return *(m_data + pos);
        }

        const_reference front() const { return *m_data; }

        const_reference back() const { return m_data[m_size - 1]; }

        T* data() const { return m_data; }

        iterator begin() const { return m_data; };

        iterator end() const { return m_data + m_size; }

        bool empty() const { return m_size == 0; }

        // cppcheck-suppress functionStatic
        size_type max_size() const noexcept { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

        // cppcheck-suppress passedByValue
        void reserve(size_type size) {
            if(m_capacity >= size) return;
            m_data = resize(m_data, size);
            if(nullptr == m_data) { throw std::bad_alloc(); }
            m_capacity = size;
        }

        // cppcheck-suppress unusedFunction
        void shrink_to_fit() {
            if(m_capacity > m_size) {
                m_data = resize(m_data, m_size);
                if(nullptr == m_data) { throw std::bad_alloc(); }
                m_capacity = m_size;
            }
        }

        void clear() { m_size = 0; }

        inline size_type size() const { return m_size; }
        // cppcheck-suppress unusedFunction
        inline size_type capacity() const { return m_capacity; }

        // cppcheck-suppress passedByValue
        iterator insert(iterator pos, const_reference value) {
            if(pos < begin() || pos > end()) { throw std::out_of_range("Insert position out of range"); }

            const size_t index = pos - begin();

            if(m_size >= m_capacity) { reserve(m_capacity ? m_capacity * 2 : 1); }

            pos = begin() + index;

            if(pos < end()) { std::move_backward(pos, end(), end() + 1); }

            *pos = value;
            ++m_size;

            return pos;
        }

        void erase(iterator pos) {
            if(pos < begin() || pos >= end()) { throw std::out_of_range("Hello world"); }
            std::move(pos + 1, end(), pos);
            m_size--;
        }

        // cppcheck-suppress passedByValue
        void push_back(const_reference value) {
            if(m_size == m_capacity) { reserve(m_capacity ? m_capacity * 2 : 1); }
            m_data[m_size] = value;
            m_size++;
        }

        void pop_back() {
            if(empty()) throw std::out_of_range("There are nothing to pop");
            m_size--;
        }

        void swap(vector& other) noexcept {
            std::swap(m_data, other.m_data);
            std::swap(m_size, other.m_size);
            std::swap(m_capacity, other.m_capacity);
        }

        template <typename... Args>
        iterator insert_many(const_iterator pos, Args&&... args) {
            if(pos < begin() || pos > end()) throw std::out_of_range("Pos is out of range");
            size_type offset = pos - begin();
            while(m_size + sizeof...(args) > m_capacity) { check_capacity(); }
            iterator insert_pos = begin() + offset;
            std::move(begin() + offset, end(), begin() + offset + sizeof...(args));
            std::initializer_list<value_type> items = {args...};
            std::copy(items.begin(), items.end(), insert_pos);
            m_size += sizeof...(args);
            return begin() + offset;
        }

        template <typename... Args>
        void insert_many_back(Args&&... args) {
            insert_many(end(), args...);
        }
    };
} // namespace s21

#endif
