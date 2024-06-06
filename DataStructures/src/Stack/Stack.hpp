#pragma once

#include <cstddef>
#include <iostream>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <utility>

#include "../LinkedLists/SinglyLinkedList.hpp"

namespace vics_data_structures {
template <typename T> class Stack {
public:
  void push(const T &element) { stack.push_front(element); }
  T pop() { return stack.pop_front(); }
  const T peek() { return stack.getHeadNode()->data; }
  bool isEmpty() { return stack.is_empty(); }

public:
  Stack() = default;
  ~Stack() = default;
  Stack(const Stack &other) = delete;
  Stack &operator=(const Stack &other) = delete;
  Stack(Stack &&other) { stack = std::move(other.stack); }
  Stack &operator=(Stack &&other) noexcept {
    if (this != &other) {
      stack = std::move(other.stack);
    }
    return *this;
  }

private:
  linked_lists::singly_linked_list::SinglyLinkedList<T> stack;
}; // Stack
} // namespace vics_data_structures