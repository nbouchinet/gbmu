#ifndef MEMORYBANKCONTROLLER1_H
#define MEMORYBANKCONTROLLER1_H

#include "AMemoryBankController.hpp"
#include <array>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <cstdint>
#include <type_traits>
#include <vector>

class MemoryBankController1 : public AMemoryBankController {
private:
  uint8_t _rom_bank : 7;
  uint8_t _ram_bank;
  bool _is_rom_banking; // ROM or RAM banking
  bool _is_ram_enabled;

  void enableRAM() { _is_ram_enabled = true; };
  void disableRAM() { _is_ram_enabled = false; }

  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive &ar, const unsigned int) {
    ar &_rom_bank;
    ar &_ram_bank;
    ar &_is_rom_banking;
    ar &_is_ram_enabled;
  }

public:
  MemoryBankController1(ROMContainer &rom, RAMContainer &ram)
      : AMemoryBankController(rom, ram), _rom_bank(1), _ram_bank(0),
        _is_rom_banking(true), _is_ram_enabled(false) {}

  void write(uint16_t addr, uint8_t value) {
    switch (addr & 0xF000) {
    case 0x0000:
    case 0x1000: /* 0x0000 to 0x1FFF */
      value == 0xA ? enableRAM() : disableRAM();
      break;
    case 0x2000:
    case 0x3000: /* 0x2000 to 0x3FFF */
      _rom_bank = (_rom_bank & 0xE0) | (value & 0x1F);
      if (_rom_bank == 0)
        _rom_bank++;
      break;
    case 0x4000:
    case 0x5000: /* 0x4000 to 0x5FFF */
      if (_is_rom_banking)
        _rom_bank = (_rom_bank & 0x1F) | (value & 0xe0);
      else
        _ram_bank = value & 0x03;
      break;
    case 0x6000:
    case 0x7000: /* 0x6000 to 0x7FFF */
      _is_rom_banking = ((value & 0x1) == 0);
      if (_is_rom_banking)
        _ram_bank = 0;
      else
        _rom_bank &= 0x1F;
      break;
    case 0xA000:
    case 0xB000: /* 0xA000 to 0xBFFF */
      if (!_is_ram_enabled)
        break;
      _ram[(addr - 0xA000) + (_ram_bank * 0x2000)] = value;
      break;
    default:
      break;
    }
    if (_rom_bank == 0x20 || _rom_bank == 0x40 || _rom_bank == 0x60)
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
    case 0xB000:
      if (!_is_ram_enabled)
        break;
      return _ram[(addr - 0xA000) + (_ram_bank * 0x2000)];
    }
    return 0;
  }
};

#endif
