#ifndef IMEMORYBANKCONTROLLER_H
#define IMEMORYBANKCONTROLLER_H

#include "Fwd.hpp"
#include <array>
#include <cstdint>
#include <vector>

class AMemoryBankController {
public:
  static const unsigned int RAMSize = 0x20000;
  typedef std::array<Byte, RAMSize> RAMContainer;
  typedef std::vector<Byte> ROMContainer;

protected:
  ROMContainer &romData;
  RAMContainer &ramData;

public:
  AMemoryBankController(ROMContainer &rom, RAMContainer &ram)
	  : romData(rom), ramData(ram) {}
  virtual ~AMemoryBankController() {};

  virtual void write(uint16_t addr, uint8_t value) = 0;
  virtual uint8_t read(uint16_t addr) const = 0;
};

#endif
