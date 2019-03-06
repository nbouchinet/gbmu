#pragma once
#ifndef OPERATIONS_UTILS_HPP
#define OPERATIONS_UTILS_HPP

#include <type_traits>
#include <cstdint>
#include <limits>

template <typename T>
bool test_bit(uint8_t bit, T t) {
  return (t >> bit) & 1;
}

template <typename T>
void set_bit(uint8_t bit, T& t) {
  t = (t & ~(1 << bit)) | (1 << bit);
}

template <typename T>
void reset_bit(uint8_t bit, T& t) {
  t = (t & ~(1 << bit)) | (0 << bit);
}

template <typename T, typename = std::enable_if_t<std::is_unsigned<T>::value>>
bool check_add_overflow_from(T a, T b, uint8_t from) {
  T mask = (1 << from) - 1;
  return (a & mask) > mask - (b & mask);
}

#endif // OPERATIONS_UTILS_HPP
