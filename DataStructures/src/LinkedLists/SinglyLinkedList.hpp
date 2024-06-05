#pragma once

#include <cstddef>
#include <iterator>
#include <mutex>
#include <optional>
#include <stdexcept>

namespace vics_data_structures {

using index_t = size_t;

namespace linked_lists {

namespace singly_linked_list {

template <typename T> class SinglyLinkedList {

private:
  template <typename T> struct Node {
  public:
    std::optional<T> data;
    Node<T> *next;
    Node(const T &data) : data(std::make_optional(data)), next(nullptr) {}

    friend bool operator==(const Node<T> &lhs, const Node<T> &rhs) {
      return lhs.data == rhs.data && lhs.next == rhs.next;
    }
  };

  // iterator class so that std::find and other algs from std lib work with this
  // DS, and for easier transversal
public:
  template <typename T> struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Node<T>;
    using pointer = Node<T> *;   // or also value_type*
    using reference = Node<T> &; // or also value_type&

    Iterator(pointer ptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }

    Iterator &operator++() {
      // safetycheck
      if (m_ptr == nullptr) {
        throw std::out_of_range("Null element referenced");
      }
      m_ptr = m_ptr->next;
      return *this;
    }

    Iterator operator++(int) {
      // safetycheck
      if (m_ptr == nullptr) {
        throw std::out_of_range("Null element referenced");
      }
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const Iterator &a, const Iterator &b) {
      return a.m_ptr == b.m_ptr;
    };
    friend bool operator!=(const Iterator &a, const Iterator &b) {
      return a.m_ptr != b.m_ptr;
    };

  private:
    pointer m_ptr;
  };

public:
  // Constructors + Destructor definitions
  SinglyLinkedList() = default;

  // SinglyLinkedList(const SinglyLinkedList &other) = delete;
  // SinglyLinkedList &operator=(const SinglyLinkedList &other) = delete;
  SinglyLinkedList(const SinglyLinkedList &other) {
    if (other.m_head) {
      m_head = new Node(other.m_head->data.value());
      Node<T> *current = m_head;
      Node<T> *otherCurrent = other.m_head->next;

      while (otherCurrent) {
        current->next = new Node<T>(otherCurrent->data.value());
        current = current->next;
        otherCurrent = otherCurrent->next;
      }

      m_tail = current;
    } else {
      m_head = m_tail = nullptr;
    }
  }

  SinglyLinkedList &operator=(const SinglyLinkedList &other) {
    if (this != &other) {
      clear();
      if (other.m_head) {
        m_head = new Node<T>(other.m_head->data);
        Node<T> *current = m_head;
        Node<T> *otherCurrent = other.m_head->next;

        while (otherCurrent) {
          current->next = new Node<T>(otherCurrent->data);
          current = current->next;
          otherCurrent = otherCurrent->next;
        }

        m_tail = current;
      } else {
        m_head = m_tail = nullptr;
      }
    }
    return *this;
  }

  SinglyLinkedList(SinglyLinkedList &&other)
      : m_head(other.getHeadNode()), m_tail(other.getTailNode()),
        m_size(other.getSize()) {
    other.shallowClear();
  }
  SinglyLinkedList &operator=(SinglyLinkedList &&other) {
    if (this != &other) {
      clear();
      m_head = other.getHeadNode();
      m_tail = other.getTailNode();
      m_size = other.getSize();
      other.shallowClear();
    }
    return *this;
  }
  ~SinglyLinkedList() { clear(); }

  // SingltLinkedList Interface
  void shallowClear() {
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
  }
  Node<T> *getHeadNode() const { return m_head; }
  Node<T> *getTailNode() const { return m_tail; }
  size_t getSize() const { return m_size; }

  void clear() {
    std::lock_guard<std::mutex> lock(m_mutex);

    Node<T> *current = m_head;
    while (current) {
      Node<T> *next = current->next;
      delete current;
      current = next;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
  }

  Iterator<T> begin() const { return Iterator<T>(m_head); }

  Iterator<T> end() const { return Iterator<T>(nullptr); }

  void push_front(const T &value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    Node<T> *newNode = new Node<T>(value);
    if (!m_head)
      m_head = m_tail = newNode;
    else {
      newNode->next = m_head;
      m_head = newNode;
    }
    m_size++;
  }
  void push_back(const T &value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    Node<T> *newNode = new Node<T>(value);
    if (!m_tail)
      m_head = m_tail = newNode;
    else {
      m_tail->next = newNode;
      m_tail = newNode;
    }
    m_size++;
  }
  void insert(const T &value, index_t pos) {
    if (pos == 0) {
      push_front(value);
    } else if (pos >= m_size) {
      push_back(value);
    } else {
      std::lock_guard<std::mutex> lock(m_mutex);
      Node<T> *newNode = new Node<T>(value);
      Node<T> *nodeBeforeInsertion = m_head;
      for (size_t i = 0; i < pos - 1; ++i) {
        nodeBeforeInsertion = nodeBeforeInsertion->next;
      }
      newNode->next = nodeBeforeInsertion->next;
      nodeBeforeInsertion->next = newNode;
      m_size++;
    }
  }
  std::optional<T> pop_front() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_head)
      return std::nullopt;
    Node<T> *temp = m_head;
    m_head = m_head->next;
    const auto data = temp->data;
    delete temp;
    if (!m_head)
      m_tail = nullptr;
    m_size--;
    return data;
  }
  std::optional<T> pop_back() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_head)
      return std::nullopt;
    if (m_head == m_tail) {
      const auto data = m_head->data;
      delete m_head;
      m_head = m_tail = nullptr;
      m_size = 0;
      return data;
    }
    Node<T> *current = m_head;
    while (current->next != m_tail) {
      current = current->next;
    }
    const auto data = m_tail->data;
    delete m_tail;
    m_tail = current;
    m_tail->next = nullptr;
    m_size--;
    return data;
  }
  void erase(index_t pos) {
    if (!m_head)
      throw std::out_of_range("Index out of bounds");
    if (pos == 0) {
      pop_front();
    } else if (pos >= m_size - 1) {
      pop_back();
    } else {
      std::lock_guard<std::mutex> lock(m_mutex);
      Node<T> *nodeHeforeDeletion = m_head;
      for (size_t i = 0; i < pos - 1; ++i) {
        nodeHeforeDeletion = nodeHeforeDeletion->next;
      }
      Node<T> *temp = nodeHeforeDeletion->next;
      nodeHeforeDeletion->next = temp->next;
      delete temp;
      m_size--;
    }
  }
  std::optional<T> front() {
    if (!m_head)
      return std::nullopt;
    return m_head->data;
  }
  std::optional<T> back() {
    if (!m_tail)
      return std::nullopt;
    return m_tail->data;
  }

  std::optional<T> operator[](index_t index) const {
    if (index > m_size) {
      throw std::out_of_range("Index out of bounds");
    }
    Node<T> *current = m_head;
    for (size_t i = 0; i < index; i++) {
      current = current->next;
    }
    return current->data;
  }
  bool is_empty() { return m_size == 0; }

private:
  Node<T> *m_head = nullptr;
  Node<T> *m_tail = nullptr;
  size_t m_size = 0;
  mutable std::mutex m_mutex;
};

} // namespace singly_linked_list
} // namespace linked_lists
} // namespace vics_data_structures