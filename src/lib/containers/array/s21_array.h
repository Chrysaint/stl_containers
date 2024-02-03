#ifndef S21_CONTAINERS_ARRAY
#define S21_CONTAINERS_ARRAY

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace s21 {
    template <typename T, size_t length>
    class array {
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using iterator = T*;
        using const_iterator = const T*;
        using size_type = size_t;

    private:
        T* m_data;
        size_type m_size;
        void init_array(size_t size) {
            m_data = new value_type[size]();
            m_size = size;
        }

    public:
        array() : m_data(nullptr), m_size(length) { init_array(length); };

        explicit array(std::initializer_list<value_type> const& items) : m_data(nullptr), m_size(0) {
            init_array(items.size());
            m_size = items.size();
            std::copy(items.begin(), items.end(), m_data);
        };

        array(const array& a) {
            init_array(a.m_size);
            m_size = a.m_size;
            std::copy(a.m_data, a.m_data + a.m_size, m_data);
        };

        array(array&& a) noexcept : m_data(a.m_data), m_size(a.m_size) {
            a.m_data = nullptr;
            a.m_size = 0;
        };

        ~array() {
            delete[] m_data;
            m_size = 0;
        }

        iterator begin() const { return m_data; };
        iterator end() const { return m_data + m_size; };
        const_iterator cbegin(void) const { return m_data; };
        const_iterator cend(void) const { return m_data + m_size; };

        // cppcheck-suppress functionConst
        // cppcheck-suppress passedByValue
        reference at(size_type pos) {
            if(pos >= m_size) { throw std::out_of_range("At method: pos index is out of bounds"); }
            return m_data[pos];
        };

        // cppcheck-suppress passedByValue
        const_reference at(size_type pos) const {
            if(pos >= m_size) { throw std::out_of_range("At method: pos index is out of bounds"); }
            return m_data[pos];
        };

        // cppcheck-suppress functionConst
        reference front() {
            if(m_size == 0) throw std::out_of_range("array is empty");
            return m_data[0];
        };

        const_reference front() const {
            if(m_size == 0) throw std::out_of_range("array is empty");
            return m_data[0];
        };

        // cppcheck-suppress functionConst
        reference back() {
            if(m_size == 0) throw std::out_of_range("array is empty");
            return m_data[m_size - 1];
        };
        const_reference back() const {
            if(m_size == 0) throw std::out_of_range("array is empty");
            return m_data[m_size - 1];
        };

        // cppcheck-suppress unusedFunction
        iterator data() const { return m_data; };

        bool empty() const { return m_size == 0; };

        size_type size() const { return m_size; };
        size_type max_size() const { return m_size; };

        void swap(array& a) noexcept {
            std::swap(m_data, a.m_data);
            std::swap(m_size, a.m_size);
        };
        // cppcheck-suppress passedByValue
        void fill(const_reference value) const { std::fill(begin(), end(), value); };

        array& operator=(const array& a) {
            if(this != &a) {
                delete[] m_data;
                init_array(a.m_size);
                std::copy(a.m_data, a.m_data + a.m_size, m_data);
            }
            return *this;
        };
        array& operator=(array&& a) noexcept {
            if(this != &a) {
                delete[] m_data;
                m_data = a.m_data;
                m_size = a.m_size;
                a.m_data = nullptr;
                a.m_size = 0;
            }
            return *this;
        };

        // cppcheck-suppress passedByValue
        reference operator[](size_type pos) { return at(pos); };
        // cppcheck-suppress passedByValue
        const_reference operator[](size_type pos) const { return at(pos); };
    };
} // namespace s21

#endif
