#ifndef IMEMORYBANKCONTROLLER_H
#define IMEMORYBANKCONTROLLER_H

#include <cstdint>

class IMemoryBankController {
public:
  virtual void write(uint16_t addr, uint8_t value) = 0;
  virtual uint8_t read(uint16_t addr) const = 0;
};

#endif
