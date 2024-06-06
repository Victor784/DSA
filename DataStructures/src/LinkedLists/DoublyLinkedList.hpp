#pragma once

#include <cstddef>
#include <iterator>
#include <mutex>
#include <stdexcept>

namespace vics_data_structures {

using index_t = size_t;

namespace linked_lists {

namespace doubly_linked_list {

template <typename T> class DoublyLinkedList {

private:
  template <typename T> struct Node {
  public:
    T data;
    Node<T> *next;
    Node<T> *prev;
    Node(const T &data) : data(data), prev(nullptr), next(nullptr) {}

    friend bool operator==(const Node<T> &lhs, const Node<T> &rhs) {
      return lhs.data == rhs.data && lhs.prev == rhs.prev &&
             lhs.next == rhs.next;
    }
  };

  // iterator class so that std::find and other algs from std lib work with
  // this
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
      if (m_ptr == nullptr) {
        throw std::out_of_range("Null element referenced");
      }
      m_ptr = m_ptr->next;
      return *this;
    }

    Iterator operator++(int) {
      if (m_ptr == nullptr) {
        throw std::out_of_range("Null element referenced");
      }
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    Iterator &operator--() {
      if (m_ptr == nullptr) {
        throw std::out_of_range("Null element referenced");
      }
      m_ptr = m_ptr->prev;
      return *this;
    }

    Iterator operator--(int) {
      if (m_ptr == nullptr) {
        throw std::out_of_range("Null element referenced");
      }
      Iterator tmp = *this;
      --(*this);
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
  DoublyLinkedList() = default;

  DoublyLinkedList(const DoublyLinkedList &other) = delete;
  DoublyLinkedList &operator=(const DoublyLinkedList &other) = delete;

  DoublyLinkedList(DoublyLinkedList &&other)
      : m_head(other.getHeadNode()), m_tail(other.getTailNode()),
        m_size(other.getSize()) {
    other.shallowClear();
  }
  DoublyLinkedList &operator=(DoublyLinkedList &&other) {
    if (this != &other) {
      clear();
      m_head = other.getHeadNode();
      m_tail = other.getTailNode();
      m_size = other.getSize();
      other.shallowClear();
    }
    return *this;
  }
  ~DoublyLinkedList() { clear(); }

  // DoublyLinkedList Interface
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

  Iterator<T> begin() { return Iterator<T>(m_head); }

  Iterator<T> end() { return Iterator<T>(m_tail); }

  void push_front(const T &value) {
    std::lock_guard<std::mutex> lock(m_mutex);
    Node<T> *newNode = new Node<T>(value);
    if (!m_head)
      m_head = m_tail = newNode;
    else {
      newNode->next = m_head;
      m_head->prev = newNode;
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
      newNode->prev = m_tail;
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
      nodeBeforeInsertion->next->prev = newNode;
      nodeBeforeInsertion->next = newNode;
      newNode->prev = nodeBeforeInsertion;
      m_size++;
    }
  }
  T pop_front() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_head)
      throw std::out_of_range("List is empty");
    Node<T> *temp = m_head;
    if (m_head == m_tail) {
      const auto data = m_head->data;
      delete m_head;
      m_head = m_tail = nullptr;
      m_size = 0;
      return data;
    }
    m_head->next->prev = nullptr;
    m_head = m_head->next;
    auto data = temp->data;
    delete temp;
    if (!m_head)
      m_tail = nullptr;
    m_size--;
    return data;
  }
  T pop_back() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_head)
      throw std::out_of_range("List is empty");
    if (m_head == m_tail) {
      auto data = m_head->data;
      delete m_head;
      m_head = m_tail = nullptr;
      m_size = 0;
      return data;
    }
    Node<T> *newTail = m_tail->prev;
    auto data = m_tail->data;
    delete m_tail;
    m_tail = newTail;
    m_tail->next = nullptr;
    m_size--;
    return data;
  }
  void erase(index_t pos) {
    Node<T> *current;
    if (!m_head)
      throw std::out_of_range("List is empty");
    if (pos == 0) {
      pop_front();
    } else if (pos >= m_size - 1) {
      pop_back();
    } else {
      std::lock_guard<std::mutex> lock(m_mutex);
      if (pos <= m_size / 2) // in case the index is closer to the head
      {
        current = m_head;
        for (size_t i = 0; i < pos; i++) {
          current = current->next;
        }
      } else //  else the index is closer to the tail
      {
        current = m_tail;
        for (size_t i = m_size - 1; i > pos; i--) {
          current = current->prev;
        }
      }
      current->next->prev = current->prev;
      current->prev->next = current->next;
      delete current;
      m_size--;
    }
  }
  T front() {
    if (!m_head)
      throw std::out_of_range("List is empty");
    return m_head->data;
  }
  T back() {
    if (!m_head)
      throw std::out_of_range("List is empty");
    return m_tail->data;
  }

  T operator[](index_t index) const {
    if (index >= m_size) {
      throw std::out_of_range("Index out of bounds");
    }
    Node<T> *current;
    if (index <= m_size / 2) // in case the index is closer to the head
    {
      current = m_head;
      for (size_t i = 0; i < index; i++) {
        current = current->next;
      }
    } else //  else the index is closer to the tail
    {
      current = m_tail;
      for (size_t i = m_size - 1; i > index; i--) {
        current = current->prev;
      }
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

} // namespace doubly_linked_list
} // namespace linked_lists
} // namespace vics_data_structures