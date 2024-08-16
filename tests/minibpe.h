#pragma once

#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <vector>
#include <format>

template<typename T>
struct Node {
    Node *m_prev;
    Node *m_next;
    T m_value;
};

template<typename T>
struct Tokenizer {

    Node<T> *m_data;
    size_t m_size{};

    inline static std::map<std::pair<int, int>, int> g_stats_map{};

    Tokenizer() noexcept {
        m_data = nullptr;
        m_size = 0;
    }

    [[maybe_unused]]
    Tokenizer(std::initializer_list<int> ilist)
            : Tokenizer(ilist.begin(), ilist.end()) {}

    [[maybe_unused]] explicit
    Tokenizer(size_t n, T const &val = 0) {
        m_data = new Node<T>[n];
        m_size = n;

        auto ptr = m_data;
        ptr->m_prev = nullptr;
        for (size_t i = 0; i < n - 1; i++) {
            ptr->m_next = ptr + 1;
            (ptr + 1)->m_prev = ptr;
            ptr->m_value = val;
            ptr = ptr->m_next;
        }
        ptr->m_next = nullptr;
        ptr->m_value = val;
    }

    template<std::random_access_iterator InputIt>
    Tokenizer(InputIt first, InputIt last) {
        size_t n = last - first;
        std::cout << n << "\n";
        m_data = new Node<T>[n];
        m_size = n;

        auto ptr = m_data;
        ptr->m_prev = nullptr;
        for (size_t i = 0; i < n - 1; i++) {
            ptr->m_next = ptr + 1;
            (ptr + 1)->m_prev = ptr;
            ptr->m_value = *first;
            ++first;
            ptr = ptr->m_next;
        }
        ptr->m_next = nullptr;
        ptr->m_value = *first;

        init_stats();
    }

    ~Tokenizer() {
        delete[] m_data;
    }

    void init_stats() {
        auto ptr = m_data;
        for (size_t i = 0; i < m_size - 1; ++i) {
            g_stats_map.insert_or_assign({ptr->m_value, ptr->m_next->m_value},
                                         g_stats_map[{ptr->m_value, ptr->m_next->m_value}] + 1);
            ptr = ptr->m_next;
        }
    }

    void stats_clear() {
        g_stats_map.clear();
    }

    struct iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        Node<T> *m_curr;

        iterator &operator++() { // ++iterator
            m_curr = m_curr->m_next;
            return *this;
        }

        iterator operator++(int) { // iterator++
            iterator tmp = *this;
            m_curr = m_curr->m_next;
            return tmp;
        }

        reference operator*() {
            return m_curr->m_value;
        }

        bool operator!=(iterator const &other) const {
            return m_curr != other.m_curr;
        }

        bool operator==(iterator const &other) const {
            return !(*this != other);
        }
    };

    iterator begin() {
        return iterator{m_data};
    }

    iterator end() {
        return iterator{nullptr};
    }

    [[nodiscard]] size_t size() const noexcept {
        return m_size;
    }

    // read-write access
    [[nodiscard]] typename
    iterator::reference operator[](size_t index) const {
        auto ptr = m_data;
        while (index > 0) {
            ptr = ptr->m_next;
            index--;
        }
        return ptr->m_value;
    }

    // check if index is out of range!
    [[nodiscard]] typename
    iterator::reference at(size_t index) const {
        if (index >= m_size)
            [[unlikely]] throw std::out_of_range("Index out of range");
        auto ptr = m_data;
        while (index > 0) {
            ptr = ptr->m_next;
            index--;
        }
        return ptr->m_value;
    }

    void find_assign_shrink(std::pair<int, int> val, int new_val) {
        auto key = val.first;
        auto next = val.second;
        auto size = m_size;
        auto ptr = m_data;

        while (ptr->m_next != nullptr) {
            if (ptr->m_value == key && ptr->m_next->m_value == next) {
                // update stats
                // first fix the old stats
                g_stats_map.erase({key, next});
                if (ptr->m_prev != nullptr)
                    g_stats_map[{ptr->m_prev->m_value, key}]--;
                if (ptr->m_next->m_next != nullptr) {
                    if (g_stats_map[{next, ptr->m_next->m_next->m_value}] > 1)
                        g_stats_map[{next, ptr->m_next->m_next->m_value}]--;
                    else
                        g_stats_map.erase({next, ptr->m_next->m_next->m_value});
                }

                // update values
                ptr->m_value = new_val;
                ptr->m_next = ptr->m_next->m_next;
                if (ptr->m_next != nullptr)
                    ptr->m_next->m_prev = ptr;
                m_size--;

                // update stats
                if (ptr->m_next != nullptr)
                    g_stats_map.insert_or_assign({ptr->m_value, ptr->m_next->m_value},
                                                 g_stats_map[{ptr->m_value, ptr->m_next->m_value}] + 1);

                if (ptr->m_prev != nullptr)
                    g_stats_map.insert_or_assign({ptr->m_prev->m_value, ptr->m_value},
                                                 g_stats_map[{ptr->m_prev->m_value, ptr->m_value}] + 1);
            }
            ptr = ptr->m_next;
        }
    }

    void print_stats() {
        for (auto const &it: g_stats_map)
            std::cout << it.first.first << " " << it.first.second << " " << it.second << "\n";
    }

};

auto tokens_generate(int min_val, int max_val, int length) {
    auto rng = std::mt19937(std::random_device{}());
    std::uniform_int_distribution<int> dist(min_val, max_val);
    std::vector<int> data(length);
    std::ranges::generate(data, [&]() { return dist(rng); });
    Tokenizer<int> tokenizer(data.begin(), data.end());
    return tokenizer;
}

template<class T>
void bytes_pair_encode(Tokenizer<T> &tokens, int round, int new_token) {
    for (int k = 0; k < round; ++k) {
        // find the most frequent pair in this round
        auto max_it = std::max_element(Tokenizer<T>::g_stats_map.begin(), Tokenizer<T>::g_stats_map.end(),
                                       [](auto const &a, auto const &b) {
                                           return a.second < b.second;
                                       });

        if (max_it->second == 1) break;

        std::cout << "Most frequent pair of round #" << (k + 1) << ": " << max_it->first.first << " "
                  << max_it->first.second << " " << max_it->second << "\n";

        // merge the most frequent pair
        tokens.find_assign_shrink({max_it->first.first, max_it->first.second}, new_token);

        ++new_token;
    }
}