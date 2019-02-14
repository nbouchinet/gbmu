#include "src/AMemoryBankController.hpp"
#include "src/MemoryBankController1.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <stdint.h>
#include <unistd.h>

class Accessor {
public:
  AMemoryBankController::ROMContainer romData;
  AMemoryBankController::RAMContainer ramData;
  MemoryBankController1 mbc;

public:
  Accessor() : romData(), ramData(), mbc(&romData, &ramData) {}

  static constexpr auto RAMSize = AMemoryBankController::RAMSize;
};

class mbc1_f : public ::testing::Test {
public:
  Accessor accessor;
};

TEST_F(mbc1_f, ram_enabled) {

  EXPECT_EQ(accessor.mbc.getRamEnabled(), false);
  accessor.mbc.write(0x0000, 0xA);
  EXPECT_EQ(accessor.mbc.getRamEnabled(), true);
  accessor.mbc.write(0x0000, 0x9);
  EXPECT_EQ(accessor.mbc.getRamEnabled(), false);
}

TEST_F(mbc1_f, rom_bank_switch) {
  uint16_t upper_addr;
  uint16_t lower_addr;

  // Enable RAM
  accessor.mbc.write(0x0000, 0xA);

  for (upper_addr = 0x2000, lower_addr = 0x4000;
       upper_addr < 0x4000 && lower_addr < 0x6000; upper_addr++, lower_addr++) {
    accessor.mbc.write(upper_addr, 0x1F);
    accessor.mbc.write(lower_addr, 0x0);
    EXPECT_EQ(accessor.mbc.getRomBank(), 0x1F);

    accessor.mbc.write(upper_addr, 0x1F);
    accessor.mbc.write(lower_addr, 0x3);
    EXPECT_EQ(accessor.mbc.getRomBank(), 0x7F);

    // Bank 0x20 is not accessible, should redirect to 0x21
    accessor.mbc.write(upper_addr, 0x0);
    accessor.mbc.write(lower_addr, 0x1);
    EXPECT_EQ(accessor.mbc.getRomBank(), 0x21);

    // Bank 0x40 is not accessible, should redirect to 0x41
    accessor.mbc.write(upper_addr, 0x0);
    accessor.mbc.write(lower_addr, 0x2);
    EXPECT_EQ(accessor.mbc.getRomBank(), 0x41);

    // Bank 0x60 is not accessible, should redirect to 0x61
    accessor.mbc.write(upper_addr, 0x0);
    accessor.mbc.write(lower_addr, 0x3);
    EXPECT_EQ(accessor.mbc.getRomBank(), 0x61);

    // writes should not affect other bits in the rom bank number
    accessor.mbc.write(lower_addr, 0x3);
    accessor.mbc.write(upper_addr, 0xF);
    EXPECT_EQ(((accessor.mbc.getRomBank() >> 5) & 0x3), 0x3);
    EXPECT_EQ(((accessor.mbc.getRomBank() >> 5) & 0x3), 0x3);
  }
}

TEST_F(mbc1_f, external_ram_bank_switch) {
  char c;
  int i;

  for (i = 0, c = 'A'; i < 10; i++, c++)
    for (int j = 0; j < 0x2000; j++)
      accessor.ramData[0x1000 * i + j] = c;

  for (i = 0, c = 'A'; i < 4; i++, c++)
    for (int j = 0xA000; j < 0xC000; j++)
      ASSERT_EQ(accessor.mbc.read(j), accessor.ramData[j - 0xA000]);
}

TEST_F(mbc1_f, rom_data_bank_switch) {
  char c;
  int i;

  accessor.mbc.write(0x6000, 0x0);
  accessor.mbc.write(0x2000, 0x0);
  accessor.mbc.write(0x4000, 0x0);

  accessor.romData.reserve(0xFFFFF);
  for (i = 1, c = 'B'; i < 0x1F; i++, c++) {
    if (c > 'Z')
      c = 'B';
    for (int j = 0; j < 0x3FFF; j++)
      accessor.romData[0x4000 * i + j] = c;
    accessor.mbc.write(0x2000, i);
    EXPECT_EQ(c, accessor.mbc.read(0x4000));
  }

  for (int j = 0; j <= 3; j++) {
    accessor.mbc.write(0x4000, j);
    for (i = 0x0, c = 'A'; i < 0x1F; i++, c++) {
      if (c > 'Z')
        c = 'A';
      for (int x = 0; x < 0x3FFF; x++)
	      accessor.romData[0x4000 * i + j] = c;

      accessor.mbc.write(0x2000, i);
      if (i == 0)
        EXPECT_EQ('B', accessor.mbc.read(0x4000));
      else
        EXPECT_EQ(c, accessor.mbc.read(0x4000));
    }
  }
}

TEST_F(mbc1_f, rom_bank_00) {
  int i;
  char c;

  accessor.romData.reserve(0xFFFFF);
  for (i = 0, c = 'A'; i < 0x1F; i++, c++) {
    if (c > 'Z')
      c = 'A';
    for (int j = 0; j < 0x3FFF; j++)
	    accessor.romData[0x4000 * i + j] = c;
  }

  accessor.mbc.write(0x6000, 0x0);
  accessor.mbc.write(0x4000, 0x0);
  accessor.mbc.write(0x2000, 0x0);

  EXPECT_EQ(accessor.mbc.read(0x4000), 'B');
}

int main(int ac, char* av[]) {
  ::testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
