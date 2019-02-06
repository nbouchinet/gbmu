#ifndef MEMORYBANKCONTROLLER1_H
#define MEMORYBANKCONTROLLER1_H

#include "IMemoryBankController.hpp"
#include <array>
#include <cstdint>
#include <vector>
#include <type_traits>

class MemoryBankController1 : public IMemoryBankController {
private:
  std::vector<uint8_t> *romData;
  std::array<uint8_t, 0x20000> *ramData;
  uint8_t ramBank : 2;
  uint8_t romBank : 7;
  bool isRomBanking; // ROM or RAM banking
  bool isRamEnabled;

private:
  void enableRAM() { isRamEnabled = true; };
  void disableRAM() { isRamEnabled = false; }

public:
  MemoryBankController1()
      : romData(0), ramData(0), ramBank(0), romBank(1), isRomBanking(true),
        isRamEnabled(false) {}

  MemoryBankController1(std::vector<uint8_t> *romPtr, std::array<uint8_t, 0x20000> *ramPtr)
      : romData(romPtr), ramData(ramPtr), ramBank(0), romBank(1),
        isRomBanking(true), isRamEnabled(false) {}

  bool getRamEnabled() const { return isRamEnabled; }
  uint8_t getRomBank() const { return romBank; };

  void write(uint16_t addr, uint8_t value) {
    switch (addr & 0xF000) {
    case 0x0000:
    case 0x1000: /* 0x0000 to 0x1FFF */
      value == 0xA ? enableRAM() : disableRAM();
      break;
    case 0x2000:
    case 0x3000: /* 0x2000 to 0x3FFF */
      if (value == 0)
        value = 1;
      romBank = (romBank & 0x60) | (value & 0x1F);
      break;
    case 0x4000:
    case 0x5000: /* 0x4000 to 0x5FFF */
      value &= 0x3;
      if (isRomBanking)
        romBank = (romBank & 0x1F) | (value << 5);
      else
        ramBank = value & 0x3;
      break;
    case 0x6000:
    case 0x7000: /* 0x6000 to 0x7FFF */
      isRomBanking = value & 0x1;
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
    if (romBank == 0x20 || romBank == 0x40 || romBank == 0x60)
      romBank += 0x1;
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
