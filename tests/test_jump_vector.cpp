#include <iostream>
#include <iterator>

struct Block {
    Block* m_next;
    int m_value;
};

struct JumpVector {

    Block *m_data;
    size_t m_size;

    JumpVector() noexcept {
        m_data = nullptr;
        m_size = 0;
    }

    JumpVector(std::initializer_list<int> ilist)
    : JumpVector(ilist.begin(), ilist.end()) {}

    explicit JumpVector(size_t n) {
        m_data = new Block[n];
        m_size = n;
        for (size_t i = 0; i < n - 1; i++) {
            m_data[i].m_next = &m_data[i + 1];
            m_data[i].m_value = 0;
        }
        m_data[n - 1].m_next = nullptr;
        m_data[n - 1].m_value = 0;
    }

    JumpVector(size_t n, int const &val) {
        m_data = new Block[n];
        m_size = n;
        for (size_t i = 0; i < n - 1; i++) {
            m_data[i].m_next = &m_data[i + 1];
            m_data[i].m_value = val;
        }
        m_data[n - 1].m_next = nullptr;
        m_data[n - 1].m_value = val;
    }

    template <std::random_access_iterator InputIt>
    JumpVector(InputIt first, InputIt last) {
        size_t n = last - first;
        m_data = new Block[n];
        m_size = n;
        for (size_t i = 0; i < n; i++) {
            m_data[i].m_next = &m_data[i + 1];
            m_data[i].m_value = *first;
            ++first;
        }
        m_data[n - 1].m_next = nullptr;
        m_data[n - 1].m_value = *first;

    }

    ~JumpVector() {
        delete[] m_data;
    }

    [[nodiscard]] size_t size() const noexcept {
        return m_size;
    }

    [[nodiscard]] Block* begin() const noexcept {
        return m_data;
    }

    Block* operator++(const Block* block) const noexcept {
        return block->m_next;
    }

    Block* operator+(Block* ptr, size_t n) const noexcept {
        while (n > 0) {
            ptr++;
            --n;
        }
        return ptr;
    }

    // read-write access
    int& operator[](size_t index) const noexcept {
        auto ptr = m_data + index;
        return ptr->m_value;
    }

    void assign_and_shrink(size_t index, int val, size_t offset = 2) {
        auto ptr = m_data + index;
        ptr->m_value = val;
        ptr->m_next = ptr + offset - 1;
        m_size -= offset - 1;
    }

};


int main() {
    JumpVector jv({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    jv.assign_and_shrink(3, 100, 2);
    for (size_t i = 0; i < jv.size(); i++) {
        std::cout << jv[i] << " ";
    }
    std::cout << "\n";
    return 0;
}