#ifndef S21_CONTAINERS_LIST
#define S21_CONTAINERS_LIST

#include <algorithm>
#include <cstdio>
#include <limits>
#include <new>
#include <stdexcept>

#include "./../array/s21_array.h"

namespace s21 {

    template <typename T>
    class list {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using size_type = size_t;

    private:
        struct m_Node {
            value_type data;
            m_Node* next;
            m_Node* prev;

            explicit m_Node(const value_type& val = value_type(), m_Node* n = nullptr, m_Node* p = nullptr) :
                data(val), next(n), prev(p) {}
        };

        class ListIterator {
        protected:
            m_Node* ptr;

        public:
            // cppcheck-suppress noExplicitConstructor
            ListIterator(m_Node* p = nullptr) : ptr(p) {};
            ListIterator(ListIterator& other) : ptr(other.get_node()) {};
            virtual ~ListIterator() = default;

            reference operator*() {
                if(ptr == nullptr) throw std::out_of_range("List is empty to deref anything from it");
                return ptr->data;
            }

            ListIterator& operator++() {
                ptr = ptr->next;
                return *this;
            }

            ListIterator operator++(int) {
                ListIterator temp = *this;
                ptr = ptr->next;
                return temp;
            }

            ListIterator& operator--() {
                ptr = ptr->prev;
                return *this;
            }

            ListIterator operator--(int) {
                ListIterator temp = *this;
                ptr = ptr->prev;
                return temp;
            }

            bool operator==(const ListIterator& other) const { return ptr == other.ptr; }
            bool operator!=(const ListIterator& other) const { return ptr != other.ptr; }

            bool operator<(const ListIterator& other) const {
                if(other == *this) return false;
                m_Node* current = ptr;
                while(current != nullptr && current != other.ptr) { current = current->next; }
                return current == other.ptr;
            }

            bool operator>(const ListIterator& other) const { return other < *this; }
            m_Node* get_node() const { return ptr; }
        };

        class ListConstIterator : public ListIterator {
        public:
            explicit ListConstIterator(const m_Node* p = nullptr) : ListIterator(const_cast<m_Node*>(p)) {};
            ListConstIterator(ListConstIterator& other) : ListIterator(other) {};
            ~ListConstIterator() override = default;

            // cppcheck-suppress duplInheritedMember
            const_reference operator*() { return ListIterator::operator*(); }

            // cppcheck-suppress duplInheritedMember
            ListConstIterator& operator++() {
                ListIterator::operator++();
                return *this;
            }

            // cppcheck-suppress duplInheritedMember
            ListConstIterator operator++(int) {
                ListConstIterator temp = *this;
                ListIterator::operator++();
                return temp;
            }

            // cppcheck-suppress duplInheritedMember
            ListConstIterator& operator--() {
                ListIterator::operator--();
                return *this;
            }

            // cppcheck-suppress duplInheritedMember
            ListConstIterator operator--(int) {
                ListConstIterator temp = *this;
                ListIterator::operator--();
                return temp;
            }

            bool operator==(const ListConstIterator& other) const { return ListIterator::operator==(other); }
            bool operator!=(const ListConstIterator& other) const { return ListIterator::operator!=(other); }
            bool operator<(const ListConstIterator& other) const { return ListIterator::operator<(other); }

            bool operator>(const ListConstIterator& other) const { return ListIterator::operator>(other); }

            // cppcheck-suppress duplInheritedMember
            const m_Node* get_node() const { return ListIterator::get_node(); };
        };

    public:
        using iterator = ListIterator;
        using const_iterator = ListConstIterator;

    private:
        m_Node* m_head;
        m_Node* m_tail;
        m_Node* m_end;
        size_type m_size;

    public:
        list() : m_head(nullptr), m_tail(nullptr), m_end(nullptr), m_size(0) {}

        explicit list(size_type n) : list() {
            for(size_type i = 0; i < n; ++i) { push_back(value_type()); }
        }

        explicit list(std::initializer_list<value_type> const& items) : list() {
            for(const value_type& item : items) { push_back(item); }
        }

        list(const list& other) : list() {
            for(iterator it = other.m_head; it != other.m_end; ++it) { push_back(*it); }
        }

        list(list&& other) noexcept : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size), m_end(other.m_end) {
            other.m_head = nullptr;
            other.m_end = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0;
        }

        ~list() { clear(); }

        list& operator=(const list& other) {
            if(this != &other) {
                list tmp(other);
                swap(tmp);
            }
            return *this;
        }

        list& operator=(list&& other) noexcept {
            if(this != &other) {
                clear();
                m_head = other.m_head;
                m_tail = other.m_tail;
                m_end = other.m_end;
                m_size = other.m_size;
                other.m_head = nullptr;
                other.m_tail = nullptr;
                other.m_end = nullptr;
                other.m_size = 0;
            }
            return *this;
        }

        const_reference front() const { return m_head->data; }
        const_reference back() const { return m_tail->data; }

        iterator begin() noexcept { return iterator(m_head); }
        iterator end() noexcept { return iterator(m_end); }
        const_iterator cbegin() const noexcept { return const_iterator(m_head); }
        const_iterator cend() const noexcept { return const_iterator(m_end); }

        bool empty() const noexcept { return m_size == 0; }
        size_type size() const noexcept { return m_size; }
        static size_type max_size() noexcept { return std::numeric_limits<size_type>::max() / sizeof(m_Node); }

        void clear() noexcept {
            while(!empty()) { pop_front(); }
        }

        // cppcheck-suppress passedByValue
        iterator insert(iterator pos, const_reference value) {
            if(pos < begin() || pos > end()) throw std::out_of_range("Position is out of range to insert");
            if(pos == begin()) {
                push_front(value);
                return begin();
            } else if(pos == end()) {
                push_back(value);
                return iterator(m_tail);
            } else {
                m_Node* current = pos.get_node();
                m_Node* new_node = new m_Node(value, current, current->prev);
                current->prev->next = new_node;
                current->prev = new_node;
                ++m_size;
                return iterator(new_node);
            }
        }

        // cppcheck-suppress passedByValue
        void erase(iterator pos) {
            if(m_size == 0) throw std::out_of_range("List is empty to erase anything from it");
            if(pos == end()) throw std::out_of_range("Position is out of range");

            m_Node* current = pos.get_node();
            if(current == m_head) {
                pop_front();
            } else if(current == m_tail) {
                pop_back();
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                --m_size;
            }
        }

        // cppcheck-suppress passedByValue
        void push_back(const_reference value) {
            auto* new_node = new m_Node(value, m_end, m_tail);

            if(empty()) {
                m_head = new_node;
                m_tail = new_node;
                m_end = new m_Node(T(), nullptr, new_node);
                if(nullptr == m_end) throw std::bad_alloc();
                new_node->next = m_end;
            } else {
                m_tail->next = new_node;
                m_tail = new_node;
                m_end->prev = new_node;
            }

            ++m_size;
        }

        // cppcheck-suppress passedByValue
        void push_front(const_reference value) {
            m_Node* new_node = new m_Node(value, m_head, nullptr);
            if(empty()) { m_end = new m_Node(T(), nullptr, new_node); }
            if(m_head) {
                m_head->prev = new_node;
            } else {
                m_tail = new_node;
                m_tail->next = m_end;
                m_end->prev = m_tail;
            }
            m_head = new_node;
            ++m_size;
        }

        void pop_back() {
            if(empty()) return;

            const m_Node* temp = m_tail;
            m_tail = m_tail->prev;
            m_end->prev = m_tail;
            if(m_size == 1) { m_head = nullptr; }
            delete temp;
            --m_size;
            if(m_size == 0) { delete m_end; }
        }

        void pop_front() {
            if(empty()) return;

            const m_Node* temp = m_head;
            m_head = m_head->next;
            if(!m_head) { m_tail = nullptr; }
            delete temp;
            --m_size;
            if(m_size == 0) { delete m_end; }
        }

        void swap(list& other) noexcept {
            std::swap(m_head, other.m_head);
            std::swap(m_tail, other.m_tail);
            std::swap(m_end, other.m_end);
            std::swap(m_size, other.m_size);
        }

        void merge(list& other) {
            splice(cend(), other);
            sort();
        }

        void splice(const_iterator pos, list& other) {
            if(this == &other || other.empty()) return;
            if(pos < cbegin() || pos > cend()) throw std::out_of_range("Position is out of range");

            m_Node* pos_node = const_cast<m_Node*>(pos.get_node());
            m_Node* other_first = other.m_head;
            m_Node* other_last = other.m_tail;

            other_first->prev = pos_node->prev;
            if(pos_node->prev != nullptr) {
                pos_node->prev->next = other_first;
            } else {
                m_head = other_first;
            }

            other_last->next = pos_node;
            pos_node->prev = other_last;

            m_size += other.m_size;

            other.m_head = other.m_tail = nullptr;
            other.m_size = 0;

            delete other.m_end;
            other.m_end = nullptr;
        }

        // cppcheck-suppress unusedFunction
        void reverse() noexcept {
            iterator it = begin();
            iterator end_it = --end();
            for(size_t i = 0; i < (size_t) (m_size / 2); ++i) {
                value_type temp = *it;
                *it = *end_it;
                *end_it = temp;
                ++it;
                --end_it;
            }
        }

        // cppcheck-suppress unusedFunction
        void unique() {
            if(empty() || size() == 1) return;

            iterator it = begin();
            iterator next_it = it;

            ++next_it;
            while(next_it != end()) {
                if(*it == *next_it) {
                    iterator temp = next_it;
                    ++temp;
                    erase(next_it);
                    next_it = temp;
                } else {
                    ++it;
                    ++next_it;
                }
            }
        }

        void sort() const {
            if(empty() || m_size == 1) return;

            for(m_Node* i = m_head; i != m_end; i = i->next) {
                for(m_Node* j = i->next; j != m_end; j = j->next) {
                    if(j->data < i->data) {
                        value_type temp = i->data;
                        i->data = j->data;
                        j->data = temp;
                    }
                }
            }
        }
        // cppcheck-suppress passedByValue
        reference operator[](const size_type index) const {
            if(index >= m_size) { throw std::out_of_range("Index out of range"); }
            size_type count = 0;
            m_Node* current = m_head;
            while(current != nullptr) {
                if(count == index) { return current->data; }
                current = current->next;
                ++count;
            }
            throw std::out_of_range("Index out of range");
        }

        template <typename... Args>
        iterator insert_many(const_iterator pos, Args&&... args) {
            if(pos < cbegin() || pos > cend()) throw std::out_of_range("Pos is out of range");
            array<value_type, sizeof...(args)> items{args...};
            for(size_type i = 0; i < items.size(); ++i) { insert(pos, items[i]); }
            return --pos;
        }

        template <typename... Args>
        // cppcheck-suppress unusedFunction
        void insert_many_back(Args&&... args) {
            array<value_type, sizeof...(args)> items{args...};
            for(size_type i = 0; i < items.size(); ++i) { push_back(items[i]); }
        };

        template <typename... Args>
        // cppcheck-suppress unusedFunction
        void insert_many_front(Args&&... args) {
            array<value_type, sizeof...(args)> items{args...};
            for(int i = items.size() - 1; i >= 0; --i) { push_front(items[i]); }
        };
    };

} // namespace s21

#endif
