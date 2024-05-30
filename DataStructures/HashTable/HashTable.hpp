#include <algorithm>
#include <functional>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <utility>

#include "../DynamicArray/DynamicArray.hpp"
#include "../LinkedLists/SinglyLinkedList.hpp"

namespace vics_data_structures {
template <typename K, typename V> class HashTable {
private:
  arrays::DynamicArray<
      linked_lists::singly_linked_list::SinglyLinkedList<std::pair<K, V>>>
      buckets;
  int numBuckets;
  int size;

  int hashFunction(K key) { return std::hash<K>{}(key) % numBuckets; }

  void rehash() {
    int newNumBuckets = numBuckets * 2;
    arrays::DynamicArray<
        linked_lists::singly_linked_list::SinglyLinkedList<std::pair<K, V>>>
        newBuckets(newNumBuckets);

    // Rehash all elements into the new buckets
    for (const linked_lists::singly_linked_list::SinglyLinkedList<
             std::pair<K, V>> &bucket : buckets) {
      for (const auto &element : bucket) {
        int newIndex =
            std::hash<K>{}(element.data.value().first) % newNumBuckets;
        newBuckets[newIndex].value().push_back(element.data.value());
      }
    }

    // Replace old buckets with new buckets
    buckets = std::move(newBuckets);
    numBuckets = newNumBuckets;
  }

public:
  HashTable(int initialCapacity = 16) : numBuckets(initialCapacity), size(0) {
    buckets.public_resize(numBuckets);
  }
  // Move constructor
  HashTable(HashTable &&other) noexcept
      : buckets(std::move(other.buckets)), numBuckets(other.numBuckets),
        size(other.size) {
    other.numBuckets = 0;
    other.size = 0;
  }

  // Move assignment operator
  HashTable &operator=(HashTable &&other) noexcept {
    if (this != &other) {
      buckets = std::move(other.buckets);
      numBuckets = other.numBuckets;
      size = other.size;
      other.numBuckets = 0;
      other.size = 0;
    }
    return *this;
  }

  // Delete copy constructor
  HashTable(const HashTable &) = delete;

  // Delete copy assignment operator
  HashTable &operator=(const HashTable &) = delete;

  void insert(K key, V value) {
    if ((float)size / numBuckets > 0.75) {
      rehash();
    }
    int index = hashFunction(key);
    buckets[index].value().push_back(std::make_pair(key, value));
    size++;
  }

  bool remove(K key) {
    int index = hashFunction(key);

    // Find the index of the element with the given key
    int elementIndex = 0;
    bool found = false;
    size_t pos = 0;

    for (auto it = buckets[index].value().begin();
         it != buckets[index].value().end(); ++it, ++elementIndex) {
      if (it->data->first == key) {
        found = true;
        break;
      }
    }

    if (found) {
      buckets[index].value().erase(
          elementIndex); // Remove the element by its index
      size--;
      return true;
    }

    return false; // Element with the given key was not found
  }

  V *search(K key) {
    int index = hashFunction(key);
    auto it =
        std::find_if(buckets[index].value().begin(),
                     buckets[index].value().end(), [&key](const auto &element) {
                       return element.data.value().first == key;
                     });
    if (it->data.has_value()) {
      return &it->data.value().second;
    }
    return nullptr;
  }

  int getSize() const { return size; }

  bool isEmpty() const { return size == 0; }

  int getNumBuckets() const { return numBuckets; }
};
} // namespace vics_data_structures