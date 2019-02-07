#ifndef CARTRIDGE_HPP
#define CARTRIDGE_HPP

#include "MemoryBankController1.hpp"
#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"

class Cartridge : public IReadWrite {
 private:
  IMemoryBankController *mbc;
  std::array<Byte, 0x20000> ram;
  std::vector<Byte> rom;

 public:
  Cartridge(const std::string &);

  auto get_begin() const { return rom.cbegin(); }
  auto get_end() const { return rom.cend(); }

  Byte read(Word addr) const override {
    if (mbc) return mbc->read(addr);
    return (0);
  }

  void write(Word addr, Byte v) override {
    if (mbc) {
      mbc->write(addr, v);
    }
  }

  bool load_rom(const std::string &path);
  IMemoryBankController *get_mbc(Byte cartridge_type);
};

#endif
