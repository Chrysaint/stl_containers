#ifndef S21_CONTAINERS_TREE
#define S21_CONTAINERS_TREE

#include <cstddef>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <limits>
#include <ostream>
#include <type_traits>
#include <utility>
namespace s21 {
    template <typename TKey, typename TValue, typename Compare = std::less<TKey>,
              typename IterReturnType = std::pair<const TKey, TValue>>
    class BinaryTree {
    private:
        using key_type = TKey;
        using value_type = TValue;
        using reference = value_type&;
        using const_reference = const value_type&;
        using size_type = size_t;
        using comparator = Compare;

        typedef enum { red, black } colors;

        typedef struct m_Node {
            colors color;
            m_Node* parent;
            m_Node* left;
            m_Node* right;
            std::pair<const key_type, value_type> data;

            m_Node() : color(red), parent(nullptr), left(nullptr), right(nullptr), data({key_type(), value_type()}) {};

            explicit m_Node(std::pair<key_type, value_type> data) :
                color(red), parent(nullptr), left(nullptr), right(nullptr), data(data) {};

        } m_Node;

        m_Node* m_root;
        m_Node* m_end;
        size_type m_size;
        friend class TreeTest;
        friend class TreeIterator;

    public:
        class TreeIterator {
            friend class BinaryTree;

        private:
            m_Node* ptr;
            m_Node* end;

        public:
            using reference = IterReturnType&;

            TreeIterator() : ptr(nullptr), end(nullptr) {}
            TreeIterator(m_Node* node, m_Node* end) : ptr(node), end(end) {}

            bool operator==(const TreeIterator& other) const { return this->ptr == other.ptr; }

            bool operator!=(const TreeIterator& other) const { return this->ptr != other.ptr; }

            TreeIterator& operator++() {
                this->ptr = next(ptr);
                return *this;
            }

            TreeIterator operator++(int) {
                TreeIterator tmp = *this;
                ++(*this);
                return tmp;
            }

            TreeIterator& operator--() {
                this->ptr = previous(ptr);
                return *this;
            }

            TreeIterator operator--(int) {
                TreeIterator tmp = *this;
                --(*this);
                return tmp;
            }

            reference operator*() const {
                if constexpr(std::is_same_v<IterReturnType, TKey> || std::is_same_v<IterReturnType, const TKey>) {
                    return const_cast<reference>(ptr->data.first);
                } else {
                    return ptr->data;
                }
            }

            const IterReturnType* operator->() const { return &(operator*()); }

            operator bool() const { return ptr != nullptr && ptr != end; }

        protected:
            m_Node* next(m_Node* ptr) {
                if(ptr->right) {
                    ptr = ptr->right;
                    while(ptr->left) ptr = ptr->left;
                    return ptr;
                }

                m_Node* parent = ptr->parent;
                while(parent && ptr == parent->right) {
                    ptr = parent;
                    parent = parent->parent;
                }

                return parent;
            }

            m_Node* previous(m_Node* ptr) {
                if(ptr->left) {
                    ptr = ptr->left;
                    while(ptr->right) ptr = ptr->right;
                    return ptr;
                }

                m_Node* parent = ptr->parent;
                while(parent && ptr == parent->left) {
                    ptr = parent;
                    parent = parent->parent;
                }

                return parent;
            }
        };
        class ConstTreeIterator : public TreeIterator {
        public:
            using Base = TreeIterator;
            using const_reference = const IterReturnType&;

            ConstTreeIterator() : Base() {}
            ConstTreeIterator(const m_Node* node, const m_Node* end) :
                Base(const_cast<m_Node*>(node), const_cast<m_Node*>(end)) {}

            // cppcheck-suppress duplInheritedMember
            const_reference operator*() const { return Base::operator*(); }

            // cppcheck-suppress duplInheritedMember
            const IterReturnType* operator->() const { return &(Base::operator*()); }
        };

    public:
        using iterator = TreeIterator;
        using const_iterator = ConstTreeIterator;

        BinaryTree() : m_root(nullptr), m_end(nullptr), m_size(0) {};
        explicit BinaryTree(std::initializer_list<value_type> const& list) : BinaryTree() {
            for(const auto& value : list) { insert(value.first, value.second); }
        };

        explicit BinaryTree(std::initializer_list<std::pair<const key_type, value_type>> const& list) : BinaryTree() {
            for(const auto& value : list) { insert(value.first, value.second); }
        };

        BinaryTree(const BinaryTree& other) : BinaryTree() {
            for(iterator it = other.begin(); it != other.end(); ++it) {
                if constexpr(std::is_same_v<IterReturnType, key_type> || std::is_same_v<IterReturnType, const key_type>) {
                    insert(*it, *it);
                } else {
                    insert((*it).first, (*it).second);
                }
            }
        };

        BinaryTree(BinaryTree&& other) noexcept : m_root(other.m_root), m_end(other.m_end), m_size(other.m_size) {
            other.m_root = nullptr;
            other.m_end = nullptr;
            other.m_size = 0;
        };

        BinaryTree& operator=(BinaryTree&& other) noexcept {
            if(*this != other) {
                m_size = other.m_size;
                m_root = other.m_root;
                m_end = other.m_end;
                other.m_size = 0;
                other.m_root = nullptr;
                other.m_end = nullptr;
            }
            return *this;
        }
        bool operator==(const BinaryTree& other) const {
            if(size() != other.size()) return false;
            auto it1 = begin();
            auto it2 = other.begin();
            while(it1 != end() && it2 != other.end()) {
                if(!(*it1 == *it2)) return false;
                ++it1;
                ++it2;
            }
            return true;
        }

        bool operator!=(const BinaryTree& other) const { return !(*this == other); }

        ~BinaryTree() {
            clear();
            delete m_end;
        };

        inline size_type size() const noexcept { return m_size; }

        inline bool empty() const noexcept { return m_size == 0; }

        inline iterator begin() const noexcept {
            m_Node* mostleft = m_root;
            while(mostleft && mostleft->left) mostleft = mostleft->left;
            return iterator(mostleft, m_end);
        }

        inline const_iterator cbegin() const noexcept {
            m_Node* mostleft = m_root;
            while(mostleft && mostleft->left) mostleft = mostleft->left;
            return const_iterator(mostleft, m_end);
        }

        iterator end() const noexcept { return iterator(m_end, m_end); }

        const_iterator cend() const noexcept { return const_iterator(m_end, m_end); }

        iterator insert(const TKey& key, const TValue& value) {
            if(m_root == nullptr) {
                m_root = new m_Node({key, value});
                m_end = new m_Node({TKey(), TValue()});
                m_root->color = black;
                link_end();
                ++m_size;
                return iterator(m_root, m_end);
            }
            unlink_end();
            m_Node* new_node = new m_Node({key, value});
            m_Node* current = m_root;
            m_Node* parent = nullptr;

            while(exists(current)) {
                parent = current;
                if(Compare()(key, current->data.first)) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }

            new_node->parent = parent;
            if(parent == nullptr) {
                m_root = new_node;
            } else if(Compare()(key, parent->data.first)) {
                parent->left = new_node;
            } else {
                parent->right = new_node;
            }

            balance_after_insertion(new_node);
            ++m_size;
            link_end();
            return iterator(new_node, m_end);
        }

        std::pair<iterator, bool> insert_unique(const TKey& key, const TValue& value) {
            if(contains(key)) return {find(key), false};
            return {insert(key, value), true};
        }

        void balance_after_insertion(m_Node* node) {
            while(node != m_root && node->parent->color == red) {
                m_Node* parent = node->parent;
                m_Node* grandfather = get_grandfather(node);
                m_Node* uncle = get_uncle(node);

                if(parent == grandfather->left) {
                    if(exists(uncle) && uncle->color == red) {
                        parent->color = black;
                        uncle->color = black;
                        grandfather->color = red;
                        node = grandfather;
                    } else {
                        if(node == parent->right) {
                            node = parent;
                            rotateLeft(node);
                            parent = node->parent;
                            grandfather = get_grandfather(node);
                        }
                        parent->color = black;
                        grandfather->color = red;
                        rotateRight(grandfather);
                    }
                } else {
                    if(exists(uncle) && uncle->color == red) {
                        parent->color = black;
                        uncle->color = black;
                        grandfather->color = red;
                        node = grandfather;
                    } else {
                        if(node == parent->left) {
                            node = parent;
                            rotateRight(node);
                            parent = node->parent;
                            grandfather = get_grandfather(node);
                        }
                        parent->color = black;
                        grandfather->color = red;
                        rotateLeft(grandfather);
                    }
                }
            }

            m_root->color = black;
        }

        void erase(iterator pos) noexcept {
            m_Node* current = pos.ptr;
            if(!exists(current)) { return; }
            unlink_end();

            m_Node* child = nullptr;
            m_Node* parent = nullptr;
            colors init_color = current->color;

            if(!exists(current->left)) {
                child = current->right;
                parent = current->parent;
                replace_node(current, current->right);
            } else if(!exists(current->right)) {
                child = current->left;
                parent = current->parent;
                replace_node(current, current->left);
            } else {
                m_Node* right_most_left_child = current->right;
                while(exists(right_most_left_child->left)) { right_most_left_child = right_most_left_child->left; }

                init_color = right_most_left_child->color;
                child = right_most_left_child->right;
                parent = current->parent;

                if(right_most_left_child->parent != current) {
                    replace_node(right_most_left_child, right_most_left_child->right);
                    right_most_left_child->right = current->right;
                    if(exists(current->right)) { current->right->parent = right_most_left_child; }
                } else {
                    parent = right_most_left_child;
                }
                replace_node(current, right_most_left_child);
                right_most_left_child->left = current->left;
                if(exists(current->left)) { current->left->parent = right_most_left_child; }
                right_most_left_child->color = current->color;
            }

            delete current;
            --m_size;

            if(init_color == black) { balance_after_erase(exists(child) ? child : parent); }

            link_end();
        }

        void balance_after_erase(m_Node* node) noexcept {
            while(exists(node) && node != m_root && is_black(node)) {
                m_Node* parent = node->parent;
                m_Node* brother = get_brother(node);
                if(is_left_subtree(node) && exists(brother)) {
                    if(!is_black(brother)) {
                        brother->color = black;
                        parent->color = red;
                        rotateLeft(parent);
                        brother = parent->right;
                    }
                    if(is_black(brother->left) && is_black(brother->right)) {
                        brother->color = red;
                        node = parent;
                    } else {
                        if(is_black(brother->right) && exists(brother->right)) {
                            brother->left->color = black;
                            brother->color = red;
                            rotateRight(brother);
                            brother = parent->right;
                        }
                        brother->color = parent->color;
                        parent->color = black;
                        brother->right->color = black;
                        rotateLeft(parent);
                        node = m_root;
                    }
                } else if(!is_left_subtree(node) && exists(brother)) {
                    if(!is_black(brother)) {
                        brother->color = black;
                        parent->color = red;
                        rotateRight(parent);
                        brother = parent->left;
                    }
                    if(is_black(brother->left) && is_black(brother->right)) {
                        brother->color = red;
                        node = parent;
                    } else {
                        if(is_black(brother->left)) {
                            brother->right->color = black;
                            brother->color = black;
                            rotateLeft(brother);
                            brother = parent->left;
                        }
                        brother->color = parent->color;
                        parent->color = black;
                        brother->left->color = black;
                        rotateRight(parent);
                        node = m_root;
                    }
                } else {
                    node = m_root;
                }
            }
            if(exists(node)) { node->color = black; }
        }

        void merge(BinaryTree& other) {
            if(*this == other) return;
            for(iterator it = other.begin(); it != other.end(); ++it) {
                if constexpr(std::is_same_v<IterReturnType, key_type> || std::is_same_v<IterReturnType, const key_type>) {
                    insert(*it, *it);
                } else {
                    insert((*it).fisrt, (*it).second);
                }
            }
            other.clear();
        }

        size_type count(const key_type& key) const {
            size_type counter = 0;
            for(std::pair<iterator, iterator> its = equal_range(key); its.first != its.second; ++its.first, ++counter) {}
            return counter;
        }

        iterator find(const key_type& key) const noexcept {
            m_Node* current = m_root;
            bool found = false;

            while(exists(current) && !found) {
                if(Compare()(key, current->data.first)) {
                    current = current->left;
                } else if(Compare()(current->data.first, key)) {
                    current = current->right;
                } else {
                    found = true;
                }
            }

            return exists(current) ? iterator(current, m_end) : end();
        }

        void swap(BinaryTree& other) noexcept {
            std::swap(this->m_root, other.m_root);
            std::swap(this->m_end, other.m_end);
            std::swap(this->m_size, other.m_size);
            if(m_end && m_end->parent) { m_end->parent->right = m_end; }
            if(other.m_end && other.m_end->parent) { other.m_end->parent->right = other.m_end; }
        }

        bool contains(const key_type& key) const noexcept { return find(key) != end(); }

        std::pair<iterator, iterator> equal_range(const key_type& key) const { return {lower_bound(key), upper_bound(key)}; }

        iterator lower_bound(const key_type& key) const {
            m_Node* current = m_root;
            m_Node* result = nullptr;

            while(exists(current)) {
                if(!Compare()(current->data.first, key)) {
                    result = current;
                    current = current->left;
                } else {
                    current = current->right;
                }
            }

            return exists(result) ? iterator(result, m_end) : end();
        }

        iterator upper_bound(const key_type& key) const {
            m_Node* current = m_root;
            m_Node* result = nullptr;

            while(exists(current)) {
                if(Compare()(key, current->data.first)) {
                    result = current;
                    current = current->left;
                } else {
                    current = current->right;
                }
            }

            return exists(result) ? iterator(result, m_end) : end();
        }

        // cppcheck-suppress functionStatic
        void generateDot(m_Node* node, std::ostream& out) const noexcept {
            if(!node) return;

            out << "  node" << node << " [label=\"" << node->data.first << "\\n"
                << node->data.second << "\", color=" << (node->color == red ? "red" : "black")
                << ", shape=circle, fontcolor=white, style=filled];\n";

            if(node->left) {
                out << "  node" << node << " -> node" << node->left << " [label=\"L\"];\n";
                generateDot(node->left, out);
            } else {
                out << "  nullLeft" << node << " [shape=point];\n";
                out << "  node" << node << " -> nullLeft" << node << " [color=gray];\n";
            }

            if(node->right) {
                out << "  node" << node << " -> node" << node->right << " [label=\"R\"];\n";
                generateDot(node->right, out);
            } else {
                out << "  nullRight" << node << " [shape=point];\n";
                out << "  node" << node << " -> nullRight" << node << " [color=gray];\n";
            }
        }

        // cppcheck-suppress unusedFunction
        void saveTreeToDot(m_Node* root, const std::string& filename) {
            std::ofstream out(filename);
            if(!out.is_open()) { throw std::runtime_error("Cannot open file: " + filename); }

            out << "digraph RedBlackTree {\n";
            out << "  node [fontname=\"Arial\"];\n";

            if(m_root) {
                generateDot(m_root, out);
            } else {
                out << "  empty [label=\"Empty tree\"];\n";
            }

            out << "}\n";
            out.close();
        }

        void clear() {
            clear_recursive(m_root);
            m_root = nullptr;
            if(m_end) { m_end->parent = nullptr; }
            m_size = 0;
        }

        static size_type max_size() noexcept { return std::numeric_limits<size_type>::max() / sizeof(m_Node); }

        static inline size_type get_node_size() noexcept { return sizeof(m_Node); }

    private:
        inline bool exists(const m_Node* const node) const noexcept { return node != nullptr && node != m_end; }

        void clear_recursive(m_Node* node) const noexcept {
            if(!exists(node)) return;
            clear_recursive(node->left);
            clear_recursive(node->right);
            delete node;
        }

        void replace_node(m_Node* a, m_Node* b) noexcept {
            if(!exists(a->parent)) {
                m_root = b;
            } else if(is_left_subtree(a)) {
                a->parent->left = b;
            } else {
                a->parent->right = b;
            }
            if(exists(b)) { b->parent = a->parent; }
        }

        void unlink_end() const noexcept {
            if(!exists(m_end)) return;

            if(m_Node* max = m_end->parent; exists(max) && max->right == m_end) { max->right = nullptr; }
            m_end->parent = nullptr;
        }

        void link_end() const {
            m_Node* max = maximum();
            if(max && max != m_end) {
                max->right = m_end;
                m_end->parent = max;
            }
        }

        bool is_left_subtree(m_Node* node) const noexcept {
            if(!exists(node)) return false;
            if(!exists(node->parent)) return false;
            return node->parent->left == node;
        }

        //clang-format off

        m_Node* get_uncle(m_Node* node) const noexcept {
            return exists(node->parent)
                           ? exists(node->parent->parent)
                                     ? (is_left_subtree(node->parent) ? node->parent->parent->right : node->parent->parent->left)
                                     : nullptr
                           : nullptr;
        }

        m_Node* get_brother(m_Node* node) const noexcept {
            return exists(node->parent) ? (is_left_subtree(node) ? node->parent->right : node->parent->left) : nullptr;
        }

        m_Node* get_grandfather(m_Node* node) const noexcept { return exists(node->parent) ? node->parent->parent : nullptr; }

        m_Node* maximum() const noexcept {
            if(!exists(m_root)) return nullptr;
            m_Node* current = m_root;
            while(exists(current) && exists(current->right)) { current = current->right; }
            return current;
        }

        //clang-format on

        void rotateLeft(m_Node* a) noexcept {
            if(!exists(a) || !exists(a->right)) return;

            m_Node* b = a->right;
            m_Node* c = b->left;
            m_Node* parentA = a->parent;

            if(!exists(parentA)) {
                m_root = b;
            } else {
                if(a == parentA->left) {
                    parentA->left = b;
                } else {
                    parentA->right = b;
                }
            }

            b->parent = parentA;

            b->left = a;
            a->parent = b;
            a->right = c;
            if(exists(c)) { c->parent = a; }
        }

        void rotateRight(m_Node* a) noexcept {
            if(!exists(a) || !exists(a->left)) return;

            m_Node* b = a->left;
            m_Node* c = b->right;
            m_Node* parentA = a->parent;

            if(!exists(parentA)) {
                m_root = b;
            } else {
                if(a == parentA->left) {
                    parentA->left = b;
                } else {
                    parentA->right = b;
                }
            }

            b->parent = parentA;
            b->right = a;

            a->parent = b;
            a->left = c;
            if(exists(c)) { c->parent = a; }
        }

        bool is_black(const m_Node* node) const noexcept { return !exists(node) || node->color == black; }
    };
} // namespace s21

#endif
