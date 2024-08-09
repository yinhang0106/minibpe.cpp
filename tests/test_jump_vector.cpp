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
        std::cout << n << "\n";
        m_data = new Block[n];
        m_size = n;
        for (size_t i = 0; i < n - 1; i++) {
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

    // read-write access
    [[nodiscard]] int& operator[](size_t index) const {
        auto ptr = m_data;
        while (index > 0) {
            ptr = ptr->m_next;
            index--;
        }
        return ptr->m_value;
    }

    // check if index is out of range!
    [[nodiscard]] int& at(size_t index) const {
        if (index >= m_size)
            [[unlikely]] throw std::out_of_range("Index out of range");
        auto ptr = m_data;
        while (index > 0) {
            ptr = ptr->m_next;
            index--;
        }
        return ptr->m_value;
    }


    void assign_and_shrink(size_t index, int val, size_t offset = 2) {
        if (index >= m_size)
            [[unlikely]] throw std::out_of_range("Index out of range");

        auto ptr = m_data;
        while (index > 0) {
            ptr = ptr->m_next;
            index--;
        }
        ptr->m_value = val;

        auto next = ptr->m_next;
        while (offset > 1) {
            next = next->m_next;
            offset--;
            m_size--;
        }
        ptr->m_next = next;
    }

    void find_assign_shrink(std::pair<int, int> val, int new_val) {
        auto key = val.first;
        auto next = val.second;
        auto size = m_size;
        auto ptr = m_data;

        while (size > 1) {
            if (ptr->m_value == key && ptr->m_next->m_value == next) {
                ptr->m_value = new_val;
                ptr->m_next = ptr->m_next->m_next;
                m_size--;
                size --;
            }
            ptr = ptr->m_next;
            size--;
        }
    }

    void print() const {
        auto ptr = m_data;
        while (ptr != nullptr) {
            std::cout << ptr->m_value << " ";
            ptr = ptr->m_next;
        }
        std::cout << "\n";
    }

};


int main() {
    JumpVector jv({1, 2, 3, 4, 5, 6, 3, 3, 3, 4});
    jv.print();
    // jv.assign_and_shrink(2, 100, 3);
    jv.find_assign_shrink({3, 3}, 100);
    jv.print();
    std::cout << jv.size() << "\n";

    return 0;
}