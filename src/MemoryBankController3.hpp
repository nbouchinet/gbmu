#ifndef MEMORYBANKCONTROLLER3_H
#define MEMORYBANKCONTROLLER3_H

#include "IMemoryBankController.hpp"
#include "RealTimeClock.hpp"
#include <cstdint>
#include <cstring>

class MemoryBankController3 : public IMemoryBankController {
private:
  uint8_t *romData;
  uint8_t ramData[0xFFFF];
  uint8_t romBank : 7;
  uint8_t ramBank : 4;
  bool isRamRtcEnabled;
  bool isRamMode;
  RealTimeClock rtc;
  struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t days;
    uint8_t daysHigh;
  } latchData;

  void enableRAM_RTC() { isRamRtcEnabled = true; };
  void disableRAM_RTC() { isRamRtcEnabled = false; };

public:
  MemoryBankController3()
      : romData(NULL), romBank(1), isRamRtcEnabled(false), isRamMode(true),
        rtc() {}

  MemoryBankController3(uint8_t *romPtr)
      : romData(romPtr), romBank(1), ramBank(0), isRamRtcEnabled(false),
        isRamMode(true), rtc() {
    memset(ramData, 0, sizeof(ramData));
    memset(&latchData, 0, sizeof(latchData));
  }

  bool getRamEnabled() const { return isRamRtcEnabled; }
  uint8_t getRomBank() const { return romBank; }

  void reset() {
    romBank = 1;
    isRamRtcEnabled = false;
    isRamMode = true;
    rtc.reset();
    memset(ramData, 0, sizeof(ramData));
    memset(&latchData, 0, sizeof(latchData));
  }

  void write(uint16_t addr, uint8_t value) {
    switch (addr & 0xF000) {
    case 0x0000:
    case 0x1000: /* 0x0000 to 0x1FFF */
      value == 0xA ? enableRAM_RTC() : disableRAM_RTC();
      break;
    case 0x2000:
    case 0x3000: /* 0x2000 to 0x3FFF */
      romBank = value & 0x7F;
      break;
    case 0x4000:
    case 0x5000: /* 0x4000 to 0x5FFF */
      if (value <= 0x7) {
        if (value <= 0x3)
          ramBank = value;
        isRamMode = true;
      } else if (value >= 0x8 && value <= 0xC) {
        rtc.switchReg(value);
        isRamMode = false;
      }
      break;
    case 0x6000:
    case 0x7000: /* 0x6000 to 0x7FFF */
      if (!isRamRtcEnabled)
        break;
      if (value == 1)
        latch();
      break;
    case 0xA000:
    case 0xB000: /* 0xA000 to 0xBFFF */
      if (!isRamRtcEnabled)
        break;
      if (isRamMode)
        ramData[(addr - 0xA000) + ramBank * 0x2000] = value;
      else
        rtc.set(value);
      break;
    default:
      break;
    }
    if (romBank == 0)
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
    case 0xB000:
      if (isRamMode)
        return ramData[(addr - 0xA000) + ramBank * 0x2000];
      else
        return rtc.get();
    }
    return 0;
  }

  void latch() {
    latchData.seconds = rtc.getSeconds();
    latchData.minutes = rtc.getMinutes();
    latchData.hours = rtc.getHours();
    latchData.days = rtc.getDayLow();
    latchData.daysHigh = rtc.getDayHigh();
  }
};

#endif /* MemoryBankController3_H */
