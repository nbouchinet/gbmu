#include "src/cpu/Timer.hpp"
#include "src/Gameboy.hpp"
#include "gtest/gtest.h"

namespace {
ComponentsContainer container("tools/Tetris.gb");
Timer t(container);

TEST(Timer, readwrite) {
  t.write(0xFF04, 0x42);
  t.write(0xFF05, 0x21);
  t.write(0xFF06, 0x42);
  EXPECT_EQ(t.read(0xFF04), 0x0);
  EXPECT_EQ(t.read(0xFF05), 0x21);
  EXPECT_EQ(t.read(0xFF06), 0x42);
}

TEST(Timer, enable_timer) {
  t.enable_timer();
  EXPECT_EQ(t.timer_enabled(), 1);
}

TEST(Timer, GetFrequence) {
  for (int i = 0; i <= 3; i++) {
    t.write(0xFF07, i);
    EXPECT_EQ(t.read(0xFF07), i);
    EXPECT_EQ(t.get_frequence() & 0x3, i);
  }
}

TEST(Timer, get_counter) {
  for (int i = 0; i <= 3; i++) {
    t.write(0xFF07, i);
    switch (i) {
    case 0x0:
      EXPECT_EQ(t.get_counter(), 0x400);
      break;
    case 0x1:
      EXPECT_EQ(t.get_counter(), 0x10);
      break;
    case 0x2:
      EXPECT_EQ(t.get_counter(), 0x40);
      break;
    case 0x3:
      EXPECT_EQ(t.get_counter(), 0x100);
      break;
    }
  }
}

TEST(Timer, update) {
  t.enable_timer();
  int cycles = 0;
  for (int i = 0; i <= 42000; i++) {
    t.update(cycles);
    cycles += 4;
  }
}
} // namespace

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
