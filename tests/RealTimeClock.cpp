#include "src/RealTimeClock.hpp"
#include <gtest/gtest.h>
#include <unistd.h>

/*
** Spin for `sec' seconds
*/
void spin(unsigned long sec) {
  clock_t clock_now = clock();
  clock_t clock_last = clock_now;
  clock_t elapsed_time = 0;

  while ((unsigned long)elapsed_time / CLOCKS_PER_SEC < sec) {
    clock_now = clock();
    elapsed_time += clock_now - clock_last;
    clock_last = clock_now;
  }
}

class rtc_f : public ::testing::Test {
public:
  RealTimeClock rtc;
};

TEST_F(rtc_f, switchReg) {
  rtc.switchReg(0x8);
  rtc.set(42);
  rtc.switchReg(0x9);
  rtc.set(35);
  rtc.switchReg(0xA);
  rtc.set(12);
  rtc.switchReg(0xB);
  rtc.set(0);
  rtc.switchReg(0xC);
  rtc.set(1);

  rtc.switchReg(0x8);
  EXPECT_EQ(rtc.get(), 42);
  rtc.switchReg(0x9);
  EXPECT_EQ(rtc.get(), 35);
  rtc.switchReg(0xa);
  EXPECT_EQ(rtc.get(), 12);
  rtc.switchReg(0xb);
  EXPECT_EQ(rtc.get(), 0);
  rtc.switchReg(0xc);
  EXPECT_EQ(rtc.get(), 1);
}

TEST_F(rtc_f, tick_sec) {
  rtc.switchReg(0x8);
  rtc.set(0);
  rtc.switchReg(0x9);
  rtc.set(0);
  rtc.switchReg(0xA);
  rtc.set(0);
  rtc.switchReg(0xB);
  rtc.set(0);
  rtc.switchReg(0xC);
  rtc.set(0);

  spin(1);
  rtc.refresh();

  rtc.switchReg(0x8);
  EXPECT_EQ(rtc.get(), 1);
}

TEST_F(rtc_f, tick_min) {
  rtc.switchReg(0x8);
  rtc.set(59);
  rtc.switchReg(0x9);
  rtc.set(0);
  rtc.switchReg(0xA);
  rtc.set(0);
  rtc.switchReg(0xB);
  rtc.set(0);
  rtc.switchReg(0xC);
  rtc.set(0);

  spin(1);
  rtc.refresh();

  // 0 sec
  rtc.switchReg(0x8);
  EXPECT_EQ(rtc.get(), 0);

  // 1 min
  rtc.switchReg(0x9);
  EXPECT_EQ(rtc.get(), 1);
}

TEST_F(rtc_f, tick_hour) {
  rtc.switchReg(0x8);
  rtc.set(59);
  rtc.switchReg(0x9);
  rtc.set(59);
  rtc.switchReg(0xA);
  rtc.set(0);
  rtc.switchReg(0xB);
  rtc.set(0);
  rtc.switchReg(0xC);
  rtc.set(0);

  spin(1);
  rtc.refresh();

  // 0 sec
  rtc.switchReg(0x8);
  EXPECT_EQ(rtc.get(), 0);

  // 0 min
  rtc.switchReg(0x9);
  EXPECT_EQ(rtc.get(), 0);

  // 1 hour
  rtc.switchReg(0xA);
  EXPECT_EQ(rtc.get(), 1);
}

TEST_F(rtc_f, tick_day) {
  rtc.switchReg(0x8);
  rtc.set(59);
  rtc.switchReg(0x9);
  rtc.set(59);
  rtc.switchReg(0xA);
  rtc.set(23);
  rtc.switchReg(0xB);
  rtc.set(0);
  rtc.switchReg(0xC);
  rtc.set(0);

  spin(1);
  rtc.refresh();

  // 0 sec
  rtc.switchReg(0x8);
  EXPECT_EQ(rtc.get(), 0);

  // 0 min
  rtc.switchReg(0x9);
  EXPECT_EQ(rtc.get(), 0);

  // 0 hour
  rtc.switchReg(0xA);
  EXPECT_EQ(rtc.get(), 0);

  // 1 day
  rtc.switchReg(0xB);
  EXPECT_EQ(rtc.get(), 1);
}

TEST_F(rtc_f, tick_day_upper) {
  rtc.switchReg(0x8);
  rtc.set(59);
  rtc.switchReg(0x9);
  rtc.set(59);
  rtc.switchReg(0xA);
  rtc.set(23);
  rtc.switchReg(0xB);
  rtc.set(255);
  rtc.switchReg(0xC);
  rtc.set(0);

  spin(1);
  rtc.refresh();

  // 0 sec
  rtc.switchReg(0x8);
  EXPECT_EQ(rtc.get(), 0);

  // 0 min
  rtc.switchReg(0x9);
  EXPECT_EQ(rtc.get(), 0);

  // 0 hour
  rtc.switchReg(0xA);
  EXPECT_EQ(rtc.get(), 0);

  // 256 day
  rtc.switchReg(0xB);
  EXPECT_EQ(rtc.get(), 0);
  rtc.switchReg(0xC);
  EXPECT_EQ(rtc.get(), 1);
}

TEST_F(rtc_f, tick_day_upper_overflow) {
  rtc.switchReg(0x8);
  rtc.set(59);
  rtc.switchReg(0x9);
  rtc.set(59);
  rtc.switchReg(0xA);
  rtc.set(23);
  rtc.switchReg(0xB);
  rtc.set(255);
  rtc.switchReg(0xC);
  rtc.set(1);

  spin(1);
  rtc.refresh();

  // 0 sec
  rtc.switchReg(0x8);
  EXPECT_EQ(rtc.get(), 0);

  // 0 min
  rtc.switchReg(0x9);
  EXPECT_EQ(rtc.get(), 0);

  // 0 hour
  rtc.switchReg(0xA);
  EXPECT_EQ(rtc.get(), 0);

  // 0 day
  rtc.switchReg(0xB);
  EXPECT_EQ(rtc.get(), 0);
  rtc.switchReg(0xC);
  EXPECT_EQ(rtc.getDayHigh(), 0);

  EXPECT_EQ(rtc.getCarry(), 1);
}

int main(int ac, char* av[]) {
  ::testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
