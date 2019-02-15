#include <gtest/gtest.h>
#include "src/MemoryBankController3.hpp"

class mbc3_f : public ::testing::Test {
protected:
  AMemoryBankController::ROMContainer romData;
  AMemoryBankController::RAMContainer ramData;
  MemoryBankController3 mbc;
public:
  mbc3_f() : mbc(romData, ramData) {}

  static constexpr auto RAMSize = AMemoryBankController::RAMSize;
};

TEST_F(mbc3_f, enable_ram) {

	ASSERT_EQ(mbc.getRamEnabled(), 0);
	mbc.write(0x0000, 0xA);
	ASSERT_EQ(mbc.getRamEnabled(), 1);
}

TEST_F(mbc3_f, disable_ram) {

	mbc.write(0x0000, 0xA);
	ASSERT_EQ(mbc.getRamEnabled(), 1);
	mbc.write(0x0000, 0x42);
	ASSERT_EQ(mbc.getRamEnabled(), 0);
}

TEST_F(mbc3_f, disable_disabled_ram) {

	ASSERT_EQ(mbc.getRamEnabled(), 0);
	mbc.write(0x0000, 0x42);
	ASSERT_EQ(mbc.getRamEnabled(), 0);
}

TEST_F(mbc3_f, enable_enabled_ram) {

	ASSERT_EQ(mbc.getRamEnabled(), 0);
	mbc.write(0x0000, 0xA);
	ASSERT_EQ(mbc.getRamEnabled(), 1);
}

int main(int ac, char* av[]) {
  ::testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
