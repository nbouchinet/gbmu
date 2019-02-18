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

void Cartridge::load_rom(const std::string &path) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);

  if (!file.is_open())
    throw std::invalid_argument("Could not read ROM file");

  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  std::streamsize size = file.tellg();

  file.seekg(0, std::ios::beg);
  rom.resize(size);
  file.read((char *)(rom.data()), size);
}

std::unique_ptr<AMemoryBankController> Cartridge::get_mbc(Byte cartridge_type) {
  switch (cartridge_type) {
  case 0x0:
  case 0x01:
  case 0x02:
  case 0x03:
    return std::make_unique<MemoryBankController1>(rom, ram);
  case 0x05:
  case 0x06:
    return std::make_unique<MemoryBankController2>(rom, ram);
  case 0x0F:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
    return std::make_unique<MemoryBankController3>(rom, ram);
  case 0x19:
  case 0x1A:
  case 0x1B:
  case 0x1C:
  case 0x1D:
  case 0x1E:
    return std::make_unique<MemoryBankController5>(rom, ram);
  default:
    throw UnsupportedCartridge();
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
