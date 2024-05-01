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

  void push_back(const std::optional<T> &newElement) {
    std::lock_guard<std::mutex> lock(dynamicArrayMutex);
    if (m_size >= m_capacity)
      resize();
    if (newElement != std::nullopt)
      m_data[m_size++] = newElement.value();
  }
  std::optional<T> pop_back() {
    std::lock_guard<std::mutex> lock(dynamicArrayMutex);
    if (m_size > 0)
      return m_data[--m_size];
    else
      return std::nullopt;
  }
  void set(const std::optional<T> &newElement, index_t index) {
    while (index >= m_size) {
      this->push_back(std::nullopt);
      index += 1;
    }
    this->push_back(newElement);
  }
  std::optional<T> get(const index_t &index) {
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
    size_t newCapacity = m_capacity * GROWTH_FACTOR;
    auto newArray = std::make_unique<std::optional<T>[]>(newCapacity);

    for (index_t i = 0; i < m_size; ++i) {
      newArray[i] = std::move(m_data[i]);
    }

    m_data = std::move(newArray);

    m_capacity = newCapacity;
  }

  std::size_t m_size;
  std::size_t m_capacity;
  std::unique_ptr<std::optional<T>[]> m_data;
  std::mutex dynamicArrayMutex;
};
} // namespace arrays
} // namespace vics_data_structures