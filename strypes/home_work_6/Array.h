#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <iostream>
#include <optional>
#include <stdexcept>

template<typename T>
class Array
{
private:
  T* ptr;

public:
  size_t capacity;
  Array(size_t capacity)
    : ptr(new T[capacity]())
    , capacity(capacity)
  {
    if (!ptr) {
      throw std::runtime_error("ERROR: Heap allocation failed");
    }
  }

  void destroy()
  {
    if (ptr) {
      delete[] ptr;
      ptr = nullptr;
      capacity = 0;
    } else {
      std::cerr << "ERROR: Pointer to array is null\n";
    }
  }

  void set(size_t idx, T value)
  {
    if (idx < capacity) {
      ptr[idx] = value;
    } else {
      throw std::out_of_range("ERROR: Index out of bounds");
    }
  }

  T get(size_t idx) const
  {
    if (idx < capacity) {
      return ptr[idx];
    } else {
      throw std::out_of_range("ERROR: Index out of bounds");
    }
  }

  // Util functions

  void print() const
  {
    std::cout << "[ ";
    for (size_t i = 0; i < capacity; ++i) {
      std::cout << get(i) << " ";
    }
    std::cout << "]\n";
  }
};

template<typename T>
Array<T>
mergeSortedArrays(const Array<T>& arrLeft, const Array<T>& arrRight)
{
  size_t i = 0, j = 0, k = 0;
  Array<T> mergedArray(arrLeft.capacity + arrRight.capacity);

  while (i < arrLeft.capacity && j < arrRight.capacity) {
    if (arrLeft.get(i) < arrRight.get(j)) {
      mergedArray.set(k++, arrLeft.get(i++));
    } else {
      mergedArray.set(k++, arrRight.get(j++));
    }
  }

  while (i < arrLeft.capacity) {
    mergedArray.set(k++, arrLeft.get(i++));
  }

  while (j < arrRight.capacity) {
    mergedArray.set(k++, arrRight.get(j++));
  }

  return mergedArray;
}

template<typename T>
std::optional<T>
findMajorityElement(const Array<T>& arr)
{
  T candidate;
  int count = 0;

  // Phase 1: Find a candidate for the majority element
  for (size_t i = 0; i < arr.capacity; ++i) {
    if (count == 0) {
      candidate = arr.get(i);
      count = 1;
    } else if (arr.get(i) == candidate) {
      count++;
    } else {
      count--;
    }
  }

  // Phase 2: Verify if the candidate is indeed the majority element
  count = 0;
  for (size_t i = 0; i < arr.capacity; ++i) {
    if (arr.get(i) == candidate) {
      count++;
    }
  }

  if (count > arr.capacity / 2) {
    return candidate;
  } else {
    return std::nullopt;
  }
}

#endif // ARRAY_H
