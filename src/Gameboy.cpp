#include "Gameboy.hpp"

#include "src/Cartridge.hpp"
#include "src/MemoryBus.hpp"
#include "src/cpu/Core.hpp"
#include "src/cpu/InterruptController.hpp"
#include "src/cpu/Timer.hpp"

#include <iostream>

ComponentsContainer::ComponentsContainer(const std::string &rom_path) {
  cartridge = std::make_unique<Cartridge>(rom_path);
  interrupt_controller = std::make_unique<InterruptController>(*this);
  core = std::make_unique<Core>(*this);
  timer = std::make_unique<Timer>(*this);
  mem_bus = std::make_unique<MemoryBus>(*this);
}

// Dtor Implementation MUST be here where the types are complete
ComponentsContainer::~ComponentsContainer() {}

Gameboy::Gameboy(const std::string &rom_path) : _components(rom_path) {}

int Gameboy::run() {
  auto it = _components.cartridge->get_begin();
  auto end = _components.cartridge->get_end();

  while (it + _components.core->pc() != end) {
    std::cout << "pc: " << std::hex << _components.core->pc() << std::endl;
    _components.core->execute(it);
    _components.interrupt_controller->ParseInterrupt();
    _components.timer->Update(_components.core->clock());
  }
  return (0);
}

void Gameboy::init() {
  _components.mem_bus->write(0xFF05, 0x00);  // Timer Counter
  _components.mem_bus->write(0xFF06, 0x00);  // Timer Modulo
  _components.mem_bus->write(0xFF07, 0x00);  // Timer Controller
  _components.mem_bus->write(0xFF10, 0x80);  // Sound1
  _components.mem_bus->write(0xFF11, 0xBF);  // Sound1
  _components.mem_bus->write(0xFF12, 0xF3);  // Sound1
  _components.mem_bus->write(0xFF14, 0xBF);  // Sound1
  _components.mem_bus->write(0xFF16, 0x3F);  // Sound2
  _components.mem_bus->write(0xFF17, 0x00);  // Sound2
  _components.mem_bus->write(0xFF19, 0xBF);  // Sound2
  _components.mem_bus->write(0xFF1A, 0x7F);  // Sound3
  _components.mem_bus->write(0xFF1B, 0xFF);  // Sound3
  _components.mem_bus->write(0xFF1C, 0x9F);  // Sound3
  _components.mem_bus->write(0xFF1E, 0xBF);  // Sound3
  _components.mem_bus->write(0xFF20, 0xFF);  // Sound4
  _components.mem_bus->write(0xFF21, 0x00);  // Sound4
  _components.mem_bus->write(0xFF22, 0x00);  // Sound4
  _components.mem_bus->write(0xFF23, 0xBF);  // Sound4
  _components.mem_bus->write(0xFF24, 0x77);  // Sound4
  _components.mem_bus->write(0xFF25, 0xF3);  // Sound4
  _components.mem_bus->write(0xFF26, 0xF1);  // Sound4
  _components.mem_bus->write(0xFF40, 0x91);
  _components.mem_bus->write(0xFF42, 0x00);
  _components.mem_bus->write(0xFF43, 0x00);
  _components.mem_bus->write(0xFF45, 0x00);
  _components.mem_bus->write(0xFF47, 0xFC);
  _components.mem_bus->write(0xFF48, 0xFF);
  _components.mem_bus->write(0xFF49, 0xFF);
  _components.mem_bus->write(0xFF4A, 0x00);
  _components.mem_bus->write(0xFF4B, 0x00);
  _components.mem_bus->write(0xFFFF, 0x00);
}
