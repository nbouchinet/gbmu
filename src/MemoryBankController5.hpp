#ifndef MEMORYBANKCONTROLLER5_H
#define MEMORYBANKCONTROLLER5_H

#include "AMemoryBankController.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <cstdint>
#include <vector>

class MemoryBankController5 : public AMemoryBankController {
private:
  uint8_t _ram_bank : 4;
  uint16_t _rom_bank : 9;
  bool _is_ram_enabled;

private:
  void enableRAM() { _is_ram_enabled = true; };
  void disableRAM() { _is_ram_enabled = false; }

  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive &ar, unsigned const int) {
    ar &_ram_bank;
    ar &_rom_bank;
    ar &_is_ram_enabled;
  }

public:
  MemoryBankController5(ROMContainer &rom, RAMContainer &ram)
      : AMemoryBankController(rom, ram), _ram_bank(0), _rom_bank(0),
        _is_ram_enabled(false) {}

  void write(uint16_t addr, uint8_t value) {
    switch (addr & 0xF000) {
    case 0x0000:
    case 0x1000: /* 0x0000 to 0x1FFF */
      value == 0xA ? enableRAM() : disableRAM();
      break;
    case 0x2000: /* 0x2000 to 0x2FFF */
      _rom_bank = (_rom_bank & 0x100) | (value & 0xFF);
      break;
    case 0x3000: /* 0x3000 to 0x3FFF */
      _rom_bank = (_rom_bank & 0xFF) | ((value & 0x1) << 8);
      break;
    case 0x4000:
    case 0x5000: /* 0x4000 to 0x5FFF */
      _ram_bank = value & 0xF;
      break;
    case 0xA000:
    case 0xB000: /* 0xA000 to 0xBFFF */
      if (!_is_ram_enabled)
        break;
      _ram.at((addr - 0xA000) + _ram_bank * 0x2000) = value;
      break;
    default:
      break;
    }
  };

  uint8_t read(uint16_t addr) const {
    switch (addr & 0xF000) {
    case 0x0000:
    case 0x1000:
    case 0x2000:
    case 0x3000:
      return _rom.at(addr);
    case 0x4000:
    case 0x5000:
    case 0x6000:
    case 0x7000:
      return _rom.at((addr - 0x4000) + _rom_bank * 0x4000);
    case 0xA000:
    case 0xB000:
      return _ram.at((addr - 0xA000) + _ram_bank * 0x2000);
    }
    return 0;
  }
};

#endif
