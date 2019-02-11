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

public:
  MemoryBus(ComponentsContainer &components);

  template <typename T> T read(Word addr) {
    T ret = 0;
    auto i = sizeof(T);


    for (const auto &range : _ranged_components) {
      if (addr >= range.begin and addr <= range.end) {
        while (i-- > 0) {
          ret |= range.component->read(addr + i) >> (i * 8);
        }
      }
    }
    return ret;
  }

  template <typename T> void write(Word addr, T v) {

    auto i = sizeof(T);

    for (const auto &range : _ranged_components) {
      if (addr >= range.begin and addr <= range.end) {
        range.component->write(addr + i, v >> (i * 8));
      }
    }
  }
};

#endif /* MEMORYMAP_H */
