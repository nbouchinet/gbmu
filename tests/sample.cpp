#include "gtest/gtest.h"

TEST(Sample, work) { EXPECT_EQ(1, true); }

int main(int ac, char *av[]) {
  ::testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
