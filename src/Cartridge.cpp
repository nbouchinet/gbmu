#include "Cartridge.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "MemoryBankController1.hpp"
#include "MemoryBankController2.hpp"
#include "MemoryBankController3.hpp"
#include "MemoryBankController5.hpp"

Cartridge::Cartridge(const std::string &rom_path) : rom(0) {
  load_rom(rom_path);
  mbc = get_mbc(rom[0x147]);
}

bool Cartridge::load_rom(const std::string &path) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);
  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  rom.resize(size);
  if (file.read((char *)(rom.data()), size)) {
    return (1);
  }
  return (0);
}

std::unique_ptr<AMemoryBankController> Cartridge::get_mbc(Byte cartridge_type) {
  switch (cartridge_type) {
  case 0x0:
  case 0x01:
  case 0x02:
  case 0x03:
    //std::cout << "Detected MBC1" << std::endl;
    return new MemoryBankController1(&rom, &ram);
  case 0x05:
  case 0x06:
    //std::cout << "Detected MBC2" << std::endl;
    return new MemoryBankController2(&rom, &ram);
  case 0x0F:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
    //std::cout << "Detected MBC3" << std::endl;
    return new MemoryBankController3(&rom, &ram);
  case 0x19:
  case 0x1A:
  case 0x1B:
  case 0x1C:
  case 0x1D:
  case 0x1E:
    //std::cout << "Detected MBC5" << std::endl;
    return new MemoryBankController5(&rom, &ram);
  default:
    //std::cout << static_cast<int>(rom[0x147]) << std::endl;
    return (0);
  }
}

void Cartridge::save_ram_to_buffer(
    AMemoryBankController::RAMContainer &buffer) {
  std::copy(ram.begin(), ram.end(), buffer.begin());
}

void Cartridge::set_ram_content(
    Byte (&buffer)[AMemoryBankController::RAMSize]) {
  for (unsigned int i = 0; i < ram.size(); i++) {
    ram[i] = buffer[i];
  }
}
