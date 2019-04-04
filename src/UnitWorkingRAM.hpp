#ifndef WORKINGRAM_H
#define WORKINGRAM_H

#include "Fwd.hpp"
#include "IReadWrite.hpp"

class UnitWorkingRAM : public IReadWrite {
private:
  static constexpr unsigned int UWRAMBankSize = 0x1000;
  static constexpr unsigned int UWRAMSize = 0x8000;
  static constexpr unsigned int Bank0Begin = 0xC000;
  static constexpr unsigned int Bank0End = 0xCFFF;
  static constexpr unsigned int BankNBegin = 0xD000;
  static constexpr unsigned int BankNEnd = 0xDFFF;
  static constexpr Word SVBKAddr = 0xFF70;

  Byte _ram[UWRAMSize];
  Byte _svbk;

  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive &ar, const unsigned int) {
    ar &_ram;
    ar &_svbk;
  }

public:
  UnitWorkingRAM() : _svbk(1) {}

  Byte read(Word addr) const override {
    if (addr == SVBKAddr) {
      return _svbk;
    } else if (addr >= Bank0Begin && addr <= Bank0End) {
      return _ram[addr - Bank0Begin];
    } else if (addr >= BankNBegin && addr <= BankNEnd) {
      return _ram[(addr - BankNBegin) + _svbk * UWRAMBankSize];
    }
    return 0;
  }

  void write(Word addr, Byte v) override {
    if (addr == SVBKAddr) {
      _svbk = v & 0x7;

      if (_svbk == 0)
        _svbk = 1;

    } else if (addr >= Bank0Begin && addr <= Bank0End) {
      _ram[addr - Bank0Begin] = v;
    } else if (addr >= BankNBegin && addr <= BankNEnd) {
      _ram[(addr - BankNBegin) + _svbk * UWRAMBankSize] = v;
    }
  }

  void dump(std::array<Byte, 0x8000> &buffer) {
    std::copy(std::begin(_ram), std::end(_ram), buffer.begin());
  }
};

#endif
