#include <gtest/gtest.h>
#include "src/MemoryBankController2.hpp"
#include <iostream>

class mbc2_f : public ::testing::Test {
protected:
  AMemoryBankController::ROMContainer romData;
  AMemoryBankController::RAMContainer ramData;
  MemoryBankController2 mbc;

  static constexpr auto RAMSize = AMemoryBankController::RAMSize;

public:
  mbc2_f() : mbc(romData, ramData) {}
};

TEST_F(mbc2_f, ram_enabled) {

	EXPECT_EQ(mbc.getRamEnabled(), false);
	mbc.write(0x0000, 0xA);
	EXPECT_EQ(mbc.getRamEnabled(), true);
	mbc.write(0x0000, 0x9);
	EXPECT_EQ(mbc.getRamEnabled(), false);

	mbc.write(0x0000, 0x8);
	mbc.write(0x0100, 0xA);
	EXPECT_EQ(mbc.getRamEnabled(), false);
}

TEST_F(mbc2_f, rom_bank_switch) {

	// Enable RAM
	mbc.write(0x0000, 0xA);

	mbc.write(0x2100, 0x0);
	mbc.write(0x2100, 0xA);
	EXPECT_EQ(mbc.getRomBank(), 0xA);

	for (int j = 0x1; j < 0xF; j++) {
		for (uint16_t addr = 0x2000; addr < 0x4000; addr++) {
			// Reset ROM bank
			mbc.write(0x2100, 0x0);
			mbc.write(addr, j);
			if (((addr >> 8) & 0x1) == 1)
				EXPECT_EQ(mbc.getRomBank(), j);
			else
				EXPECT_EQ(mbc.getRomBank(), 1);
		}
	}
}

TEST_F(mbc2_f, rom_data_bank_switch) {

	char c;
	int i;

	mbc.write(0x6000, 0x0);
	mbc.write(0x2000, 0x0);
	mbc.write(0x4000, 0x0);

	romData.resize(0xFFFFF);

	for (i = 1, c = 'B'; i < 0xF; i++, c++) {
		if (c > 'Z')
			c = 'B';
		for (int j = 0; j < 0x3FFF; j++)
			romData[0x4000 * i + j] = c;

		mbc.write(0x2100, i);
		EXPECT_EQ(c, mbc.read(0x4000));
	}

	for (int j = 0; j <= 3; j++) {
		mbc.write(0x4000, j);
		for (i = 0x1, c = 'A'; i < 0xF; i++, c++) {
			if (c > 'Z')
				c = 'A';
			for (int j = 0; j < 0x3FFF; j++)
				romData[0x4000 * i + j] = c;

			mbc.write(0x2100, i);
			if (i == 0)
				EXPECT_EQ('B', mbc.read(0x4000));
			else
				EXPECT_EQ(c , mbc.read(0x4000));
		}
	}
}

TEST_F(mbc2_f, ram_io) {
	mbc.write(0x0, 0xA);

	for (int i = 0, j = 0xA000; i < 0x200; i++, j++) {
		mbc.write(j, 0xF);
		EXPECT_EQ(mbc.read(j), 0xF);
	}

	for (int i = 0, j = 0xA000; i < 0x200; i++, j++) {
		mbc.write(j, 0xFF);
		EXPECT_EQ(mbc.read(j), 0xF);
	}
}

int main(int ac, char* av[]) {
  ::testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
