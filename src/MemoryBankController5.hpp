#ifndef MEMORYBANKCONTROLLER5_H
#define MEMORYBANKCONTROLLER5_H

#include "AMemoryBankController.hpp"
#include <cstdint>
#include <vector>

class MemoryBankController5 : public AMemoryBankController {
private:
  uint8_t ramBank : 2;
  uint16_t romBank : 9;
  bool isRamEnabled;

private:
  void enableRAM() { isRamEnabled = true; };
  void disableRAM() { isRamEnabled = false; }

public:
  MemoryBankController5(std::vector<uint8_t> *romPtr,
                        std::array<uint8_t, 0x20000> *ramPtr)
      : ramBank(0), isRamEnabled(false) {
    romData = romPtr;
    ramData = ramPtr;
  }

  bool getRamEnabled() const { return isRamEnabled; }
  uint8_t getRomBank() const { return romBank; };

  void write(uint16_t addr, uint8_t value) {
    switch (addr & 0xF000) {
    case 0x0000:
    case 0x1000: /* 0x0000 to 0x1FFF */
      value == 0xA ? enableRAM() : disableRAM();
      break;
    case 0x2000: /* 0x2000 to 0x2FFF */
      romBank = (romBank & 0x100) | value;
      break;
    case 0x3000: /* 0x3000 to 0x3FFF */
      romBank = (romBank & 0xFF) | ((value & 0x1) << 8);
      break;
    case 0x4000:
    case 0x5000: /* 0x4000 to 0x5FFF */
      ramBank = value & 0xF;
      break;
    case 0xA000:
    case 0xB000: /* 0xA000 to 0xBFFF */
      if (!isRamEnabled)
        break;
      (*ramData)[(addr - 0xA000) + ramBank * 0x2000] = value;
      break;
    default:
      break;
    }
  };

  uint8_t read(uint16_t addr) const {
    switch (addr & 0xF000) {
    case 0x0000:
    case 0x3000:
      return (*romData)[addr];
    case 0x4000:
    case 0x7000:
      return (*romData)[(addr - 0x4000) + romBank * 0x4000];
    case 0xA000:
    case 0xB000:
      return (*ramData)[(addr - 0xA000) + ramBank * 0x2000];
    }
    return 0;
  }
};

#endif
