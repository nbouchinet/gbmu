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

/*
 * Check if each nibble of an addition result overflow and set the highest bit of the nibble if so.
 * A nibble is a group of 4 bit.
 * example:
 *  Let's say T = Byte and a = b = 1111 1111b
 *  check_add_overflows(a, b) -> 1000 1000b
 *                               ^    ^ Those bits are set because they made their nibble overflow
 */
template <typename T, typename = std::enable_if_t<std::is_unsigned<T>::value>>
T check_add_overflows(T a, T b) {
  constexpr std::size_t nibbles = sizeof(T) * 2;
  T ret = 0u;
  T mask = 0xf;
  for (auto i = 0u; i < nibbles; ++i) {
    if ((a & mask) > mask - (b & mask)) ret |= (0x8 << i * 4);
    mask |= mask << 4;
  }
  return ret;
}

/*
 * Check if each nibble of an substraction result overflow and set the lowest bit of the nibble if so.
 * A nibble is a group of 4 bit.
 * example:
 *  Let's say T = Byte and a = b = 1111 1111b
 *  check_add_overflows(a, b) -> 0001 0001b
 *                                  ^    ^ Those bits are set because they made their nibble overflow
 */
template <typename T, typename = std::enable_if_t<std::is_unsigned<T>::value>>
T check_sub_overflows(T a, T b) {
  constexpr std::size_t nibbles = sizeof(T) * 2;
  T ret = 0u;
  T mask = std::numeric_limits<T>::max();
  for (auto i = 0u; i < nibbles; ++i) {
    if ((a & mask) < (b & mask)) ret |= (0x1 << i * 4);
    mask <<= 4;
  }
  return ret;
}
#endif // OPERATIONS_UTILS_HPP
