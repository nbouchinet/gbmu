#include "src/Cartridge.hpp"
#include "src/Gameboy.hpp"
#include "gtest/gtest.h"
#include <fstream>

class Accessor {
public:
  Gameboy gb;

  Accessor() : gb("../tools/Tetris.gb") {}

  Cartridge &getCartridge() { return *gb._components.cartridge.get(); };
  AMemoryBankController::RAMContainer &getCartridgeRam() {
    return gb._components.cartridge.get()->ram;
  }
};

class TestGameboyFixture : public ::testing::Test {
public:
  Accessor _accessor;
  AMemoryBankController::RAMContainer ram;

  void SetUp() override { ram.fill(0); }
};

TEST_F(TestGameboyFixture, save) {
  std::string save_name = "test_rom.gb.save";
  std::ifstream in("/dev/urandom", std::ifstream::binary | std::ifstream::in);

  for (unsigned int i = 0; i < AMemoryBankController::RAMSize; i++) {
    in >> ram[i];
    _accessor.getCartridgeRam()[i] = ram[i];
  }
  _accessor.gb.save(save_name);

  Byte c;
  std::ifstream save_file(save_name);

  for (unsigned int i = 0; i < AMemoryBankController::RAMSize; i++) {
    save_file >> c;
    EXPECT_EQ(ram[i], c);
  }

  in.close();
}

int main(int ac, char *av[]) {
  ::testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
