#include "Gameboy.hpp"
#include "src/Bios.hpp"
#include "src/Cartridge.hpp"
#include "src/LCDRegisters.hpp"
#include "src/MemoryBus.hpp"
#include "src/UnitWorkingRAM.hpp"
#include "src/cpu/Core.hpp"
#include "src/cpu/InputController.hpp"
#include "src/cpu/InterruptController.hpp"
#include "src/cpu/Timer.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <ostream>

ComponentsContainer::ComponentsContainer(const std::string &rom_path) {
  cartridge = std::make_unique<Cartridge>(rom_path);
  interrupt_controller = std::make_unique<InterruptController>(*this);
  input_controller = std::make_unique<InputController>(*this);
  core = std::make_unique<Core>(*this);
  timer = std::make_unique<Timer>(*this);
  lcd_registers = std::make_unique<LCDRegisters>();
  unit_working_ram = std::make_unique<UnitWorkingRAM>();
  ppu = std::make_unique<PPU>(*this);
  driver_screen = std::make_unique<ScreenOutput>();
  bios = std::make_unique<Bios>();
  mem_bus = std::make_unique<MemoryBus>(*this);
}

// Dtor Implementation MUST be here where the types are complete
ComponentsContainer::~ComponentsContainer() {}

Gameboy::Gameboy(const std::string &rom_path)
    : _components(rom_path), _debugger(_components) {}

void Gameboy::notify_debugger(Debugger::e_dbg_state state, int duration) {
  switch (state) {
  case Debugger::RUN_DURATION:
    _debugger.run_duration(duration);
    break;
  case Debugger::RUN_ONE_FRAME:
    _debugger.run_one_frame();
    break;
  case Debugger::RUN_ONE_STEP:
    _debugger.run_one_step();
    break;
  case Debugger::RUN_CPU_SEC:
    _debugger.run_cpu_sec();
    break;
  }
}

void Gameboy::handle_input_wraper(Byte val) {
  _components.input_controller->handle_input(val);
}

void Gameboy::step() {
  if (_debugger.is_enabled()) {
    _debugger.fetch(_components.core->pc());
  }
  _components.core->execute();
  _components.interrupt_controller->parse_interrupt();
  _components.timer->update(_components.core->cycles());
  _components.ppu->update_graphics(_components.core->cycles());
}

int Gameboy::run() {
  //_components.mem_bus->write(0xFF50, 1);
  set_cgb_flag();
  _components.core->instr_jp(0x0000);
  do_checksum();
  while (true) {
    step();
  }
  return (0);
}

void Gameboy::init() {
  _components.mem_bus->write(0xFF05, 0x00); // Timer Counter Register
  _components.mem_bus->write(0xFF06, 0x00); // Timer Modulo Register
  _components.mem_bus->write(0xFF07, 0x00); // Timer Controller Registerr
  _components.mem_bus->write(0xFF10, 0x80); // Sound1 Register
  _components.mem_bus->write(0xFF11, 0xBF); // Sound1 Register
  _components.mem_bus->write(0xFF12, 0xF3); // Sound1 Register
  _components.mem_bus->write(0xFF14, 0xBF); // Sound1 Register
  _components.mem_bus->write(0xFF16, 0x3F); // Sound2 Register
  _components.mem_bus->write(0xFF17, 0x00); // Sound2 Register
  _components.mem_bus->write(0xFF19, 0xBF); // Sound2 Register
  _components.mem_bus->write(0xFF1A, 0x7F); // Sound3 Register
  _components.mem_bus->write(0xFF1B, 0xFF); // Sound3 Register
  _components.mem_bus->write(0xFF1C, 0x9F); // Sound3 Register
  _components.mem_bus->write(0xFF1E, 0xBF); // Sound3 Register
  _components.mem_bus->write(0xFF20, 0xFF); // Sound4 Register
  _components.mem_bus->write(0xFF21, 0x00); // Sound4 Register
  _components.mem_bus->write(0xFF22, 0x00); // Sound4 Register
  _components.mem_bus->write(0xFF23, 0xBF); // Sound4 Register
  _components.mem_bus->write(0xFF24, 0x77); // Sound4 Register
  _components.mem_bus->write(0xFF25, 0xF3); // Sound4 Register
  _components.mem_bus->write(0xFF26, 0xF1); // Sound4 Register
  _components.mem_bus->write(0xFF40, 0x91); // LCD Register
  _components.mem_bus->write(0xFF42, 0x00); // LCD Register
  _components.mem_bus->write(0xFF43, 0x00); // LCD Register
  _components.mem_bus->write(0xFF45, 0x00); // LCD Register
  _components.mem_bus->write(0xFF47, 0xFC); // LCD Register
  _components.mem_bus->write(0xFF48, 0xFF); // LCD Register
  _components.mem_bus->write(0xFF49, 0xFF); // LCD Register
  _components.mem_bus->write(0xFF4A, 0x00); // LCD Register
  _components.mem_bus->write(0xFF4B, 0x00); // LCD Register
  _components.mem_bus->write(0xFFFF, 0x00);
}

void Gameboy::save(std::string save_name) {
  std::filebuf fb;

  fb.open(save_name, std::ios::binary | std::ios::out | std::ios::trunc);
  if (fb.is_open()) {
    std::ostream os(&fb);
    AMemoryBankController::RAMContainer ram_content;

    _components.cartridge->save_ram_to_buffer(ram_content);
    for (unsigned int i = 0; i < AMemoryBankController::RAMSize; i++) {
      os << ram_content[i];
    }
    fb.close();
  }
}

void Gameboy::load_save(std::string save_name) {
  GameSave gs;

  std::ifstream in(save_name, std::ios::binary | std::ios::in | std::ios::ate);

  if (in.is_open()) {
    std::streamsize size = in.tellg();
    in.seekg(0, std::ios::beg);
    in.read(reinterpret_cast<char *>(&gs), size);
    _components.cartridge->set_ram_content(gs.ram);
  }
}

void Gameboy::do_checksum() {
  Byte sum = 0;

  for (Word i = 0x0134; i <= 0x14C; i++) {
    sum = sum - _components.mem_bus->read<Byte>(i) - 1;
  }

  Byte cartridge_sum = _components.mem_bus->read<Byte>(0x14D);

  if (cartridge_sum != sum)
    throw BadChecksum();
}

void Gameboy::set_cgb_flag() {
	_cgb_flag = _components.mem_bus->read<Byte>(0x143);
}
