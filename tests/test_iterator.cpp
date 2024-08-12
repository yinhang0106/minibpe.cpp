#include <iostream>
#include <algorithm>


template <class T>
struct Node {
    Node* m_next;
    T m_value;
};

template <class T>
struct ForwardList {
    Node<T> *m_head;
    size_t m_size;

    ForwardList() noexcept {
        m_head = nullptr;
        m_size = 0;
    }

    ForwardList(std::initializer_list<T> ilist) {
        m_size = ilist.size();
        m_head = new Node<T>[m_size];
        for (size_t i = 0; i < m_size - 1; i++) {
            m_head[i].m_next = &m_head[i + 1];
            m_head[i].m_value = *(ilist.begin() + i);
        }
        m_head[m_size - 1].m_next = nullptr;
        m_head[m_size - 1].m_value = *(ilist.begin() + m_size - 1);
    }

    struct iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Node<T> *m_curr;

        reference operator*() const {
            return m_curr->m_value;
        }

        iterator &operator++() {
            m_curr = m_curr->m_next;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            m_curr = m_curr->m_next;
            return tmp;
        }

        bool operator!=(const iterator &other) const {
            return m_curr != other.m_curr;
        }

        bool operator==(const iterator &other) const {
            return !(*this != other);
        }
    };

    iterator begin() {
        return iterator{m_head};
    }

    iterator end() {
        return iterator{nullptr};
    }

};



int main() {
    auto jv = ForwardList<int>{1, 2, 3, 4, 5, 3, 4, 5, 6, 7, 8, 9, 10};
    for (auto const &it : jv)
        std::cout << it << " ";
    std::cout << "\n";
    if (auto const v = std::ranges::find(jv, 5); v != jv.end())
        std::cout << "Found: " << *v << "\n";
    else
        std::cout << "Not found\n";
    return 0;
}