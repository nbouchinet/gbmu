#include "../src/PPU.class.h"
#include "gtest/gtest.h"

TEST(testBit, bit0) { EXPECT_EQ((ppu::testBit(0x01, 0)), true); }

int main(int ac, char *av[]) {
  ::testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
