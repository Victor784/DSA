#pragma once

#include <cstddef>
#include <iostream>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <utility>

#include "../LinkedLists/DoublyLinkedList.hpp"

namespace vics_data_structures {
template <typename T> class Queue {
public:
  void enqueue(const T &element) { queue.push_back(element); }
  void dequeue() { queue.pop_front(); }
  const T &front() const { return queue.getHeadNode()->data; }
  bool isEmpty() { return queue.is_empty(); }

public:
  Queue() = default;
  ~Queue() = default;
  Queue(const Queue &other) = delete;
  Queue &operator=(const Queue &other) = delete;
  Queue(Queue &&other) { queue = std::move(other.queue); }
  Queue &operator=(Queue &&other) noexcept {
    if (this != &other) {
      queue = std::move(other.queue);
    }
    return *this;
  }

public:
private:
  linked_lists::doubly_linked_list::DoublyLinkedList<T> queue;
};
} // namespace vics_data_structures