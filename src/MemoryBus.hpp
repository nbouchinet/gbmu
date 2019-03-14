#pragma once
#ifndef MEMORYBUS_H
#define MEMORYBUS_H

#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"

#include <iostream>
#include <vector>

class MemoryBus {
private:
  struct RangedComponent {
    Word begin, end;
    IReadWrite *component;
  };
  std::vector<RangedComponent> _ranged_components;
  bool _bios_is_enabled = true;

public:
  MemoryBus(ComponentsContainer &components);

  void disable_bios();
  void enable_bios(Bios *bios);
  void reset(ComponentsContainer &components);

  template <typename T> T read(Word addr) const {
    T ret = 0;
    auto i = sizeof(T);

    for (const auto &range : _ranged_components) {
      if (addr >= range.begin and addr <= range.end) {
        while (i-- > 0) {
          ret |= range.component->read(addr + i) >> (i * 8);
        }
        break;
      }
    }
    return ret;
  }

  Byte _sb = 0;
  template <typename T> void write(Word addr, T v) {
    auto i = sizeof(T);

    if (addr == 0xff01) {
      _sb = v;
    }
    if (addr == 0xff02 && v == 0x81) {
      std::cerr << _sb;
    }

    if (addr == 0xFF50) {
      disable_bios();
    }

    for (const auto &range : _ranged_components) {
      if (addr >= range.begin and addr <= range.end) {
        while (i-- > 0) {
          range.component->write(addr + i, v >> (i * 8));
        }
        break;
      }
    }
  }
};

#endif /* MEMORYMAP_H */
