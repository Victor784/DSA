#pragma once

#include <cstddef>
#include <iostream>
#include <optional>
#include <stdexcept>

using index_t = size_t;

namespace vics_data_structures {

template <typename T> class DynamicArray {
public:
  DynamicArray();
  ~DynamicArray();

  DynamicArray(const DynamicArray &other) = delete;
  DynamicArray &operator=(const DynamicArray &other) = delete;

  DynamicArray(DynamicArray &&other) noexcept = default;
  DynamicArray &operator=(DynamicArray &&other) noexcept = default;

  std::size_t getLength();
  std::size_t getCapacity();

  // clang-format off
  void             push_back(std::optional<T> newElement);
  std::optional<T> pop_back();
  void             set(std::optional<T> newElement, index_t index);
  std::optional<T> get(index_t index);
  bool             is_empty();
  // clang format on

  std::optional<T> operator[](index_t index) const {
    if (index >= m_size) {
      throw std::out_of_range("Index out of bounds");
    }

    return m_data[index];
  }

private:
  void resize();

  std::size_t m_size;
  std::size_t m_capacity;
  std::optional<T> *m_data;
};
} // namespace vics_data_structures