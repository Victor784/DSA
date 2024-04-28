#include "DynamicArray.hpp"
#include <cstddef>

#define MIN_CAPACITY 10
#define GROWTH_FACTOR 2

using namespace vics_data_structures;

template <class T> DynamicArray<T>::DynamicArray() {

  m_size = 0;
  m_capacity = MIN_CAPACITY;
  m_data = new std::optional<T>[m_capacity];
  if (!m_data)
    throw std::bad_alloc();
}

template <class T> DynamicArray<T>::~DynamicArray() { delete[] m_data; }

template <class T> std::size_t DynamicArray<T>::getLength() { return m_size; }

template <class T> std::size_t DynamicArray<T>::getCapacity() {
  return m_capacity;
}

template <class T>
void DynamicArray<T>::push_back(std::optional<T> newElement) {
  if (m_size >= m_capacity)
    resize();
  m_data[++m_size] = newElement.data();
}

template <class T> std::optional<T> DynamicArray<T>::pop_back() {
  if (m_size > 0)
    return m_data[m_size--];
  else
    return std::nullopt;
}

// inserting an element at a non existand index, will increase the size of the
// array and populate each slot in the element with a nullopt.
template <class T>
void DynamicArray<T>::set(std::optional<T> newEleement, index_t index) {
  while (index >= m_size)
    this->push_back(std::nullopt);
  m_data[index] = newEleement;
}

template <class T> std::optional<T> DynamicArray<T>::get(index_t index) {
  if (index >= m_size) {
    throw std::out_of_range("Index out of bounds");
  }
  return m_data[index];
}

template <class T> bool DynamicArray<T>::is_empty() { return m_size == 0; }

template <class T> void DynamicArray<T>::resize() {
  // get the neccessary space needed
  size_t newCapacity = m_capacity * GROWTH_FACTOR;

  // create new array with a bigger capacity
  T *newArray = new T[newCapacity];

  std::copy(m_data, m_data + m_size, newArray);

  // free the memory from the old heap location
  delete[] m_data;

  // reroute the pointer to point to the new array
  m_data = newArray;

  // save the new capacity
  m_capacity = newCapacity;
}