#ifndef MEMORYBANKCONTROLLER2_H
#define MEMORYBANKCONTROLLER2_H

#include "AMemoryBankController.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <cstdint>
#include <cstring>
#include <vector>

class MemoryBankController2 : public AMemoryBankController {
private:
  uint8_t _rom_bank : 4;
  bool _is_ram_enabled;

private:
  void enableRAM() { _is_ram_enabled = true; };
  void disableRAM() { _is_ram_enabled = false; }

  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive &ar, const unsigned int) {
    ar &_rom_bank;
    ar &_is_ram_enabled;
  }

public:
  MemoryBankController2(ROMContainer &rom, RAMContainer &ram)
      : AMemoryBankController(rom, ram), _rom_bank(0), _is_ram_enabled(false) {}

  void write(uint16_t addr, uint8_t value) {
    switch (addr & 0xF000) {
    case 0x0000:
    case 0x1000: /* 0x0000 to 0x1FFF */
      if (((addr >> 8) & 0x1) == 0)
        (value == 0xA) ? enableRAM() : disableRAM();
      break;
    case 0x2000:
    case 0x3000: /* 0x2000 to 0x3FFF */
      if (((addr >> 8) & 0x1) == 1)
        _rom_bank = value & 0xF;
      break;
    case 0xA000:
      if (!_is_ram_enabled)
        break;
      if (addr < 0xA200)
        _ram[addr - 0xA000] = value & 0xF;
      break;
    default:
      break;
    }
    if (_rom_bank == 0x20 || _rom_bank == 0x40 || _rom_bank == 0x60 ||
        _rom_bank == 0x0)
      _rom_bank += 0x1;
  };

  uint8_t read(uint16_t addr) const {
    switch (addr & 0xF000) {
    case 0x0000:
    case 0x1000:
    case 0x2000:
    case 0x3000:
      return _rom[addr];
    case 0x4000:
    case 0x5000:
    case 0x6000:
    case 0x7000:
      return _rom[(addr - 0x4000) + _rom_bank * 0x4000];
    case 0xA000:
      if (addr < 0xA200)
        return _ram[(addr - 0xA000)] & 0xF;
    }
    return 0;
  }
};

#endif
