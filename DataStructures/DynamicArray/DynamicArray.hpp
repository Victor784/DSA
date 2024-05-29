#pragma once

#include <cstddef>
#include <iostream>
#include <mutex>
#include <optional>
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
    m_data = std::make_unique<std::optional<T>[]>(m_capacity);
  }
  DynamicArray(const int initialCapacity) {

    m_size = 0;
    m_capacity = initialCapacity;
    m_data = std::make_unique<std::optional<T>[]>(m_capacity);
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

  void push_back(const std::optional<T> &newElement = std::nullopt) {
    std::lock_guard<std::mutex> lock(dynamicArrayMutex);
    if (m_size >= m_capacity)
      resize();
    if (newElement.has_value())
      m_data[m_size++] = newElement.value();
  }
  std::optional<T> pop_back() {
    std::lock_guard<std::mutex> lock(dynamicArrayMutex);
    if (m_size > 0)
      return m_data[--m_size];
    else
      return std::nullopt;
  }
  bool is_empty() { return m_size == 0; }

  std::optional<T> operator[](index_t index) const {
    if (index >= m_size) {
      throw std::out_of_range("Index out of bounds");
    }

    return m_data[index];
  }

public:
  void public_resize(std::optional<size_t> newCapacity = std::nullopt) {
    resize(newCapacity);
  }

private:
  void resize(std::optional<size_t> newCapacity = std::nullopt) {
    size_t effectiveCapacity = newCapacity.value_or(m_capacity * GROWTH_FACTOR);
    if (effectiveCapacity <= m_capacity)
      return;
    auto newArray = std::make_unique<std::optional<T>[]>(effectiveCapacity);

    for (index_t i = 0; i < m_size; ++i) {
      newArray[i] = std::move(m_data[i]);
    }

    m_data = std::move(newArray);

    m_capacity = effectiveCapacity;
  }

  std::size_t m_size;
  std::size_t m_capacity;
  std::unique_ptr<std::optional<T>[]> m_data;
  std::mutex dynamicArrayMutex;

  template <typename T> struct Iterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;   // or also value_type*
    using reference = T &; // or also value_type&

    Iterator(std::optional<T> *ptr) : m_ptr(ptr) {}

    reference operator*() const { return m_ptr->value(); }
    pointer operator->() { return &(m_ptr->value()); }

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
    std::optional<T> *m_ptr;
  };

public:
  Iterator<T> begin() { return Iterator(m_data.get()); }
  Iterator<T> end() { return Iterator(m_data.get() + m_size); }

}; // DynamicArray
} // namespace arrays
} // namespace vics_data_structures