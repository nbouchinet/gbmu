#ifndef IMEMORYBANKCONTROLLER_H
#define IMEMORYBANKCONTROLLER_H

#include "Fwd.hpp"
#include <array>
#include <boost/serialization/array.hpp>
#include <boost/serialization/vector.hpp>
#include <cstdint>
#include <vector>

class AMemoryBankController {
public:
  static constexpr unsigned int RAMSize = 0x20000;
  typedef std::array<Byte, RAMSize> RAMContainer;
  typedef std::vector<Byte> ROMContainer;

protected:
  ROMContainer &_rom;
  RAMContainer &_ram;

public:
  AMemoryBankController(ROMContainer &rom, RAMContainer &ram)
      : _rom(rom), _ram(ram) {}
  virtual ~AMemoryBankController(){};

  template <class Archive> void serialize(Archive &, const unsigned int) {}

  virtual void write(uint16_t addr, uint8_t value) = 0;
  virtual uint8_t read(uint16_t addr) const = 0;
};

#endif
