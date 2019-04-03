#ifndef MEMORYBANKCONTROLLER3_H
#define MEMORYBANKCONTROLLER3_H

#include "AMemoryBankController.hpp"
#include "RealTimeClock.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <cstdint>
#include <cstring>
#include <vector>

class MemoryBankController3 : public AMemoryBankController {
private:
  uint8_t _rom_bank : 7;
  uint8_t _ram_bank : 4;
  bool _is_ram_rtc_enabled;
  RealTimeClock rtc;
  struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t days;
    uint8_t days_high;
  } _latch_data;

  void enableRAM_RTC() { _is_ram_rtc_enabled = true; };
  void disableRAM_RTC() { _is_ram_rtc_enabled = false; };

  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive &ar, const unsigned int) {
    ar &_rom_bank;
    ar &_ram_bank;
    ar &_is_ram_rtc_enabled;
    ar &rtc;
    ar &_latch_data;
  }

public:
  MemoryBankController3(ROMContainer &rom, RAMContainer &ram)
      : AMemoryBankController(rom, ram), _rom_bank(1), _ram_bank(0),
        _is_ram_rtc_enabled(false), rtc() {
    memset(&_latch_data, 0, sizeof(_latch_data));
  }

  void write(uint16_t addr, uint8_t value) {

    /* Refresh the real time clock as often as possible */
    rtc.refresh();

    switch (addr & 0xF000) {
    case 0x0000:
    case 0x1000: /* 0x0000 to 0x1FFF */
      value == 0xA ? enableRAM_RTC() : disableRAM_RTC();
      break;
    case 0x2000:
    case 0x3000: /* 0x2000 to 0x3FFF */
      if (value == 0)
        value++;
      _rom_bank = value & 0x7F;
      break;
    case 0x4000:
    case 0x5000: /* 0x4000 to 0x5FFF */
      if (value <= 0x3) {
        _ram_bank = value;
      } else if (value >= 0x8 && value <= 0xC) {
        rtc.switch_reg(value);
      }
      break;
    case 0x6000:
    case 0x7000: /* 0x6000 to 0x7FFF */
      if (!_is_ram_rtc_enabled)
        break;
      if (value == 1)
        latch();
      break;
    case 0xA000:
    case 0xB000: /* 0xA000 to 0xBFFF */
      if (!_is_ram_rtc_enabled)
        break;
      if (_ram_bank <= 0x3)
        _ram[(addr - 0xA000) + _ram_bank * 0x2000] = value;
      else if (value >= 0x7 && value <= 0xC)
        rtc.set(value);
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
      return _rom[addr];
    case 0x4000:
    case 0x5000:
    case 0x6000:
    case 0x7000:
      return _rom[(addr - 0x4000) + _rom_bank * 0x4000];
    case 0xA000:
    case 0xB000:
      if (_ram_bank <= 0x3) {
        return _ram[(addr - 0xA000) + _ram_bank * 0x2000];
      } else if (_ram_bank >= 0x8 && _ram_bank <= 0xC) {
        return rtc.get();
      }
    }
    return 0;
  }

  void latch() {
    _latch_data.seconds = rtc.get_seconds();
    _latch_data.minutes = rtc.get_minutes();
    _latch_data.hours = rtc.get_hours();
    _latch_data.days = rtc.get_day_low();
    _latch_data.days_high = rtc.get_day_high();
  }
};

#endif /* MemoryBankController3_H */
