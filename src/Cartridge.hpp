#ifndef CARTRIDGE_HPP
#define CARTRIDGE_HPP

#include "AMemoryBankController.hpp"
#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/array.hpp>
#include <memory>
#include <sstream>

class Accessor;

class Cartridge : public IReadWrite {
private:
  std::unique_ptr<AMemoryBankController> mbc;
  AMemoryBankController::RAMContainer ram;
  AMemoryBankController::ROMContainer rom;

  friend class Accessor;

  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive &ar, const unsigned int) {
    ar &rom;
    ar &ram;
    ar &*mbc;
  }

public:
  Cartridge(const std::string &);

  void reset(const std::string &rom_path);

  auto get_begin() const { return rom.cbegin(); }
  auto get_end() const { return rom.cend(); }

  void save_ram_to_buffer(AMemoryBankController::RAMContainer &buffer);
  void set_ram_content(const Byte *, std::size_t);

  Byte read(Word addr) const override {
    if (mbc.get())
      return mbc->read(addr);
	throw std::exception();
  }

  void write(Word addr, Byte v) override {
    if (mbc.get()) {
      mbc->write(addr, v);
    }
	else {
		throw std::exception();
	}
  }

  void load_rom(const std::string &path);
  std::unique_ptr<AMemoryBankController> get_mbc(Byte cartridge_type);

  class UnsupportedCartridge : public std::exception {
  public:
    const char *what() const noexcept { return "Unsupported cartridge type."; }
  };
};

#endif
