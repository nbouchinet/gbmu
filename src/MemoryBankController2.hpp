#ifndef MEMORYBANKCONTROLLER2_H
#define MEMORYBANKCONTROLLER2_H

#include "IMemoryBankController.hpp"
#include <cstdint>
#include <cstring>

class MemoryBankController2 : public IMemoryBankController {
private:
public:
  uint8_t *romData;
  uint8_t ramData[512];
  uint8_t romBank : 4;
  bool isRamEnabled;

private:
  void enableRAM() { isRamEnabled = true; };
  void disableRAM() { isRamEnabled = false; }

public:
  MemoryBankController2(uint8_t *romPtr)
      : romData(romPtr), romBank(0), isRamEnabled(false) {
    memset(ramData, 0, sizeof(ramData));
  }

  bool getRamEnabled() const { return isRamEnabled; }
  uint8_t getRomBank() const { return romBank; };

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
        romBank = value & 0xF;
      break;
    case 0xA000:
      if (!isRamEnabled)
        break;
      if (addr < 0xA200)
        ramData[addr - 0xA000] = value & 0xF;
      break;
    default:
      break;
    }
    if (romBank == 0x20 || romBank == 0x40 || romBank == 0x60 || romBank == 0x0)
      romBank += 0x1;
  };

  uint8_t read(uint16_t addr) const {
    switch (addr & 0xF000) {
    case 0x0000:
    case 0x3000:
      return romData[addr];
    case 0x4000:
    case 0x7000:
      return romData[(addr - 0x4000) + romBank * 0x4000];
    case 0xA000:
      if (addr < 0xA200)
        return ramData[(addr - 0xA000)] & 0xF;
    }
    return 0;
  }
};

#endif
