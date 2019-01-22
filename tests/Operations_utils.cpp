#include "src/Operations_utils.hpp"

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

int main(int ac, char *av[]) {
  ::testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
