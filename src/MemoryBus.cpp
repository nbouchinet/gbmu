#include "MemoryBus.hpp"

#include "src/Cartridge.hpp"
#include "src/cpu/Core.hpp"
#include "src/cpu/InterruptController.hpp"
#include "src/cpu/Timer.hpp"
#include "src/LCDRegisters.hpp"

#define push_component(begin, end, c)                                          \
  _ranged_components.push_back(RangedComponent{begin, end, c});

MemoryBus::MemoryBus(ComponentsContainer &components) {
  push_component(0x0000, 0xBFFF, components.cartridge.get());
  push_component(0xFF04, 0xFF08, components.timer.get());
  push_component(0xFF0F, 0xFF0F, components.interrupt_controller.get());
  push_component(0xFF40, 0xFF4B, components.lcd_registers.get());
  push_component(0xFF80, 0xFFFE, components.core.get());
  push_component(0xFFFF, 0xFFFF, components.interrupt_controller.get());
}
