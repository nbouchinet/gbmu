#ifndef CARTRIDGE_HPP
#define CARTRIDGE_HPP

#include "MemoryBankController1.hpp"
#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"

class Accessor;

class Cartridge : public IReadWrite {
private:
  AMemoryBankController *mbc;
  AMemoryBankController::RAMContainer ram;
  AMemoryBankController::ROMContainer rom;

  friend class Accessor;

public:
  Cartridge(const std::string &);

  auto get_begin() const { return rom.cbegin(); }
  auto get_end() const { return rom.cend(); }

  void save_ram_to_buffer(AMemoryBankController::RAMContainer &buffer);
  void set_ram_content(Byte (&buffer)[AMemoryBankController::RAMSize]);

  Byte read(Word addr) const override {
    if (mbc)
      return mbc->read(addr);
    return (0);
  }

  void write(Word addr, Byte v) override {
    if (mbc) {
      mbc->write(addr, v);
    }
  }

  bool load_rom(const std::string &path);
  AMemoryBankController *get_mbc(Byte cartridge_type);
};

#endif
