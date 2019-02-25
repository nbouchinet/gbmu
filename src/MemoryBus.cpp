#include "MemoryBus.hpp"

#include "src/Gameboy.hpp"
#include "src/Cartridge.hpp"
#include "src/cpu/Core.hpp"
#include "src/cpu/InterruptController.hpp"
#include "src/cpu/Timer.hpp"
#include "src/LCDRegisters.hpp"
#include "src/UnitWorkingRAM.hpp"

#define push_component(begin, end, c)                                          \
  _ranged_components.push_back(RangedComponent{begin, end, c});

MemoryBus::MemoryBus(ComponentsContainer &components) {
  push_component(0x0000, 0x7FFF, components.cartridge.get());
  push_component(0xA000, 0xBFFF, components.cartridge.get());
  push_component(0xC000, 0xDFFF, components.unit_working_ram.get());
  push_component(0xFF04, 0xFF08, components.timer.get());
  push_component(0xFF0F, 0xFF0F, components.interrupt_controller.get());
  push_component(0xFF40, 0xFF4B, components.ppu.get());
  push_component(0xFF51, 0xFF55, components.ppu.get());
  push_component(0xFF68, 0xFF6B, components.ppu.get());
  push_component(0x8000, 0x9FFF, components.ppu.get());
  push_component(0xFF80, 0xFFFE, components.core.get());
  push_component(0xFFFF, 0xFFFF, components.interrupt_controller.get());
  push_component(0xFF70, 0xFF70, components.unit_working_ram.get());
}
