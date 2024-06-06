#pragma once

#include <cstddef>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <utility>

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
    m_data = std::make_unique<T[]>(m_capacity);
  }
  DynamicArray(const int initialCapacity) {

    m_size = 0;
    m_capacity = initialCapacity;
    m_data = std::make_unique<T[]>(m_capacity);
  }

  ~DynamicArray() = default;

  DynamicArray(const DynamicArray &other) = delete;
  DynamicArray &operator=(const DynamicArray &other) = delete;

  // clang-format off
  DynamicArray(DynamicArray &&other) noexcept
      : std::exchange(m_size,other.getLength()),
        std::exchange(m_capacity,other.getCapacity()),
        m_data(std::move(other.m_data)) {}

  DynamicArray &operator=(DynamicArray &&other) noexcept {
    if (this != &other) {
      std::exchange(m_size, other.getLength());
      std::exchange(m_capacity, other.getCapacity());
      m_data = std::move(other.m_data);
    }
    return *this;
  }
  // clang-format on
  std::size_t getLength() { return m_size; }
  std::size_t getCapacity() { return m_capacity; }

  void push_back(const T &newElement) {
    std::lock_guard<std::mutex> lock(dynamicArrayMutex);
    if (m_size >= m_capacity)
      resize();
    m_data[m_size++] = newElement;
  }
  T *pop_back() {
    if (m_size <= 0)
      return nullptr;
    std::lock_guard<std::mutex> lock(dynamicArrayMutex);
    return &m_data[--m_size];
  }
  bool is_empty() { return m_size == 0; }

  T &operator[](index_t index) {
    if (index >= m_capacity) {
      throw std::out_of_range("Index out of bounds");
    }
    return m_data[index];
  }

  const T &operator[](index_t index) const {
    if (index >= m_capacity) {
      throw std::out_of_range("Index out of bounds");
    }
    return m_data[index];
  }

  void insert(index_t index, const T &value) {
    if (index > m_size) {
      throw std::out_of_range("Index out of bounds");
    }

    if (m_size + 1 >= m_capacity) {
      resize(m_capacity * 2);
    }

    for (index_t i = m_size; i > index; --i) {
      m_data[i] = std::move(m_data[i - 1]);
    }

    m_data[index] = value;
    ++m_size;
  }

public:
  void public_resize(size_t newCapacity) { resize(newCapacity); }

private:
  void resize(size_t newCapacity = 0) {
    size_t effectiveCapacity =
        newCapacity != 0 ? newCapacity : m_capacity * GROWTH_FACTOR;
    if (effectiveCapacity <= m_capacity)
      return;
    auto newArray = std::make_unique<T[]>(effectiveCapacity);

    for (index_t i = 0; i < m_size; ++i) {
      newArray[i] = std::move(m_data[i]);
    }

    m_data = std::move(newArray);

    m_capacity = effectiveCapacity;
  }

  std::size_t m_size;
  std::size_t m_capacity;
  std::unique_ptr<T[]> m_data;
  std::mutex dynamicArrayMutex;

  template <typename T> struct Iterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;   // or also value_type*
    using reference = T &; // or also value_type&

    Iterator(T *ptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return &m_ptr; }

    Iterator &operator++() {
      m_ptr++;
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const Iterator &a, const Iterator &b) {
      return a.m_ptr == b.m_ptr;
    }

    friend bool operator!=(const Iterator &a, const Iterator &b) {
      return a.m_ptr != b.m_ptr;
    }

  private:
    T *m_ptr;
  };

public:
  Iterator<T> begin() { return Iterator(m_data.get()); }
  Iterator<T> end() { return Iterator(m_data.get() + m_size); }

}; // DynamicArray
} // namespace arrays
} // namespace vics_data_structures