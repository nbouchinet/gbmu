#include "utils/Operations_utils.hpp"

#include "gtest/gtest.h"

#include <limits>

TEST(BitOperations, test_bit) {
  for (int i = 0; i < 16; ++i) {
    EXPECT_TRUE(test_bit(i, 0xffff));
    EXPECT_FALSE(test_bit(i, 0x0000));
  }
  constexpr int val = 0x20;
  for (auto i = 0u; i < sizeof(val) * 8; ++i) {
    if (i == 5)
      EXPECT_TRUE(test_bit(i, val));
    else
      EXPECT_FALSE(test_bit(i, val));
  }
}

TEST(BitOperations, set_bit) {
  {
    unsigned int a = 0u;
    for (auto i = 0u; i < sizeof(a) * 8; ++i) {
      set_bit(i, a);
    }
    EXPECT_EQ(a, std::numeric_limits<decltype(a)>::max());
  }
  {
    unsigned int a = 0u;
    set_bit(18, a);
    EXPECT_EQ(a, 0x40000u);
  }
}

TEST(BitOperations, reset_bit) {
  {
    auto a = std::numeric_limits<unsigned int>::max();
    for (auto i = 0u; i < sizeof(a) * 8; ++i) {
      reset_bit(i, a);
    }
    EXPECT_EQ(a, 0u);
  }
  {
    auto a = std::numeric_limits<unsigned int>::max();
    reset_bit(18, a);
    EXPECT_EQ(a, 0xfffbffffu);
  }
}

TEST(Overflows, add) {
  EXPECT_EQ(check_add_overflows(0x7u, 0x9u), 0x8u);
  EXPECT_EQ(check_add_overflows(0x6u, 0xau), 0x8u);
  EXPECT_EQ(check_add_overflows(0x80u, 0x80u), 0x80u);
  EXPECT_EQ(check_add_overflows(0x89u, 0x86u), 0x80u);
  EXPECT_EQ(check_add_overflows(0xffu, 0xffu), 0x88u);
  EXPECT_EQ(check_add_overflows(0xfu, 0x1u), 0x08u);
  EXPECT_EQ(check_add_overflows(0xffffu, 0xffffu), 0x8888u);

  EXPECT_EQ(check_add_overflows(0x6u, 0x9u), 0x0u);
  EXPECT_EQ(check_add_overflows(0x66u, 0x11u), 0x00u);
  EXPECT_EQ(check_add_overflows(0x66u, 0xa9u), 0x80u);
  EXPECT_EQ(check_add_overflows(0x0000u, 0x0000u), 0x0000u);
}

TEST(Overflows, sub) {
  EXPECT_EQ(check_sub_overflows(0x1u, 0x2u), 0x1u);
  EXPECT_EQ(check_sub_overflows(0x39u, 0x79u), 0x11u);
  EXPECT_EQ(check_sub_overflows(0x10u, 0x20u), 0x11u);
  EXPECT_EQ(check_sub_overflows(0x11u, 0x22u), 0x11u);
  EXPECT_EQ(check_sub_overflows(0x111111u, 0x222222u), 0x111111u);
  EXPECT_EQ(check_sub_overflows(0xfeu, 0xefu), 0x0u);

  EXPECT_EQ(check_sub_overflows(0x0u, 0x0u), 0x00u);
  EXPECT_EQ(check_sub_overflows(0x9u, 0x9u), 0x00u);
  EXPECT_EQ(check_sub_overflows(0x42u, 0x41u), 0x00u);
}

int main(int ac, char *av[]) {
  ::testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
