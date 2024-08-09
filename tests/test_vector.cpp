#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>

template <typename T>
class Vector {
private:
   T *m_data = nullptr;
   size_t m_size{};

public:
   explicit Vector(size_t m_size_) : m_data(new T[m_size_]), m_size(m_size_) {}

   Vector(Vector const& other) : m_data(new T[other.m_size]), m_size(other.m_size) {
      memcpy(m_data, other.m_data, m_size * sizeof(T));
   }

   Vector& operator=(Vector const& other) {
      if (this != &other) {
         delete[] m_data;
         m_data = new T[other.m_size];
         m_size = other.m_size;
         memcpy(m_data, other.m_data, m_size * sizeof(T));
      }
      return *this;
   }

   Vector(Vector&& other) noexcept {
      m_data = other.m_data;
      m_size = other.m_size;
      other.m_data = nullptr;
      other.m_size = 0;
   }

   Vector& operator=(Vector&& other) noexcept {
      if (this != &other) {
         delete[] m_data;
         m_data = other.m_data;
         m_size = other.m_size;
         other.m_data = nullptr;
         other.m_size = 0;
      }
      return *this;
   }

   // suporrt for std::vector constructor
   explicit Vector(std::vector<T> const& vec) : m_data(new T[vec.m_size()]), m_size(vec.m_size()) {
      memcpy(m_data, vec.m_data(), m_size * sizeof(T));
   }

   [[nodiscard]] size_t size() const noexcept {
      return m_size;
   }

   // read-only access
   T operator[](size_t index) const noexcept {
      return m_data[index];
   }

   // read-write access
   T& operator[](size_t index) noexcept {
      return m_data[index];
   }

   T at(size_t index) const {
      if (index >= m_size)
         [[unlikely]] throw std::out_of_range("Index out of range");
      return m_data[index];
   }

   T& at(size_t index) {
      if (index >= m_size)
         [[unlikely]] throw std::out_of_range("Index out of range");
      return m_data[index];
   }


   void print() {
      for (int i = 0; i < m_size; i++) {
         std::cout << m_data[i] << " ";
      }
      std::cout << "\n";
   }

   ~Vector() { delete[] m_data; }
};





int main() {
   auto v1 = Vector<int>(3);
   auto v2 = Vector<int>({1, 2, 3});
   v1 = v2;

   v1.print();
   v2.print();

   v1[1] = 10;

   std::cout << v1[1] << "\n";
   std::cout << v2.at(10) << "\n";
   // std::cout << v2[10] << "\n";
   std::sort()

   return 0;
}