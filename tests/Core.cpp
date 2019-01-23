#include "src/Core.hpp"

#include "gtest/gtest.h"

class TestCoreFixture : public ::testing::Test {
 private:
  Core _core;
};

int main(int ac, char *av[]) {
  ::testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
