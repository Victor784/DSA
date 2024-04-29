#pragma once

#include <cstddef>
#include <iostream>
#include <optional>
#include <stdexcept>

using index_t = size_t;

#define MIN_CAPACITY 10
#define GROWTH_FACTOR 2

namespace vics_data_structures {

namespace arrays {

template <typename T> class DynamicArray {
public:
  DynamicArray() {

    m_size = 0;
    m_capacity = MIN_CAPACITY;
    m_data = new std::optional<T>[m_capacity];
    if (!m_data)
      throw std::bad_alloc();
  }
  ~DynamicArray() { delete[] m_data; }

  DynamicArray(const DynamicArray &other) = delete;
  DynamicArray &operator=(const DynamicArray &other) = delete;

  DynamicArray(DynamicArray &&other) noexcept = default;
  DynamicArray &operator=(DynamicArray &&other) noexcept = default;

  std::size_t getLength() { return m_size; }
  std::size_t getCapacity() { return m_capacity; }

  void push_back(std::optional<T> newElement) {
    if (m_size >= m_capacity)
      resize();
    m_data[m_size++] = newElement.value();
  }
  std::optional<T> pop_back() {
    if (m_size > 0)
      return m_data[m_size--];
    else
      return std::nullopt;
  }
  void set(std::optional<T> newElement, index_t index) {
    while (index >= m_size)
      this->push_back(std::nullopt);
    m_data[index] = newElement.value();
  }
  std::optional<T> get(index_t index) {
    if (index >= m_size) {
      throw std::out_of_range("Index out of bounds");
    }
    return m_data[index];
  }
  bool is_empty() { return m_size == 0; }

  std::optional<T> operator[](index_t index) const {
    if (index >= m_size) {
      throw std::out_of_range("Index out of bounds");
    }

    return m_data[index];
  }

private:
  void resize() {
    // get the neccessary space needed
    size_t newCapacity = m_capacity * GROWTH_FACTOR;

    // create new array with a bigger capacity
    std::optional<T> *newArray = new std::optional<T>[newCapacity];

    std::copy(m_data, m_data + m_size, newArray);

    // free the memory from the old heap location
    delete[] m_data;

    // reroute the pointer to point to the new array
    m_data = newArray;

    // save the new capacity
    m_capacity = newCapacity;
  }

  std::size_t m_size;
  std::size_t m_capacity;
  std::optional<T> *m_data;
};
} // namespace arrays
} // namespace vics_data_structures