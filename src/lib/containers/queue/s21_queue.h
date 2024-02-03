#ifndef S21_CONTAINERS_QUEUE
#define S21_CONTAINERS_QUEUE

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

#include "./../array/s21_array.h"
#include "./../list/s21_list.h"
namespace s21 {
    template <typename T, typename container = list<T>>
    class queue {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using size_type = size_t;

    protected:
        container m_data;

    public:
        queue() : m_data() {};
        explicit queue(std::initializer_list<value_type> const& items) : m_data(items) {};
        queue(const queue& s) : m_data(s.m_data) {};
        queue(queue&& s) noexcept : m_data(std::move(s.m_data)) {};
        ~queue() { m_data.clear(); };

        queue& operator=(const queue& s) {
            if(this != &s) { m_data = s.m_data; }
            return *this;
        };

        queue& operator=(queue&& s) noexcept {
            if(this != &s) { m_data = std::move(s.m_data); }
            return *this;
        };

        const_reference front() { return m_data.front(); };
        const_reference back() { return m_data.back(); };

        bool empty() { return m_data.empty(); };
        size_type size() { return m_data.size(); };

        // cppcheck-suppress passedByValue
        void push(const_reference value) { m_data.push_back(value); };
        // cppcheck-suppress unusedFunction
        void pop() {
            if(empty()) throw std::out_of_range("Stack is empty to pop");
            m_data.pop_front();
        };
        void swap(queue& other) noexcept { m_data.swap(other.m_data); };

        template <typename... Args>
        void insert_many_back(Args&&... args) {
            array<value_type, sizeof...(args)> items{args...};
            for(size_t i = 0; i < sizeof...(args); ++i) { push(items[i]); }
        }
    };

} // namespace s21

#endif
