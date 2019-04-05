#include "Gameboy.hpp"
#include "src/Bios.hpp"
#include "src/Cartridge.hpp"
#include "src/MemoryBus.hpp"
#include "src/UnitWorkingRAM.hpp"
#include "src/cpu/Core.hpp"
#include "src/cpu/InputController.hpp"
#include "src/cpu/InterruptController.hpp"
#include "src/cpu/Timer.hpp"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <exception>
#include <fstream>
#include <iostream>
#include <ostream>

ComponentsContainer::ComponentsContainer(
    const std::string &rom_path, sound::AudioInterface *audio_interace) {
  cartridge = std::make_unique<Cartridge>(rom_path);
  bios = std::make_unique<Bios>();
  interrupt_controller = std::make_unique<InterruptController>(*this);
  input_controller = std::make_unique<InputController>(*this);
  core = std::make_unique<Core>(*this);
  timer = std::make_unique<Timer>(*this);
  unit_working_ram = std::make_unique<UnitWorkingRAM>();
  ppu = std::make_unique<PPU>(*this);
  apu = std::make_unique<sound::APU>(audio_interace, *this);
  driver_screen = std::make_unique<ScreenOutput>();
  mem_bus = std::make_unique<MemoryBus>(*this);
}

// Dtor Implementation MUST be here where the types are complete
ComponentsContainer::~ComponentsContainer() {}

Gameboy::Gameboy(const std::string &rom_path, GbType type)
    : _components(rom_path, &_audio_interface), _debugger(_components),
      _type(type), _rom_path(rom_path), _is_abort(false), _pause(false) {}

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

void Gameboy::reset() {
  _components.mem_bus->reset(_components);
  _components.core->reset();
  _components.cartridge->reset(_rom_path);
  _components.interrupt_controller->reset();
  _components.input_controller->reset();
  _components.timer->reset();
  _components.ppu->reset();
  _components.apu->reset();
  _components.driver_screen->reset_screen();
  init();
  _debugger.reset();
}

void Gameboy::key_pressed_wraper(int val) {
  _components.input_controller->key_pressed(val);
}

void Gameboy::key_released_wraper(int val) {
  _components.input_controller->key_released(val);
}

void Gameboy::step() {
  if (_debugger.is_enabled()) {
    _debugger.fetch(_components.core->pc());
  }

  _components.core->execute();
  int cycles = _components.core->cycles() / _components.core->speed();
  _components.timer->update(cycles);
  _components.ppu->update_graphics(cycles);
  _components.interrupt_controller->parse_interrupt();
  _components.apu->update_clock(cycles);
}

void Gameboy::load_existing_save() {
  std::string save_path = _rom_path + ".save";
  std::ifstream file(save_path.c_str());
  if (file.good()) {
    load_save(save_path);
  }
}

int Gameboy::run() {
  do_checksum();
  read_type();
  _components.bios->set_type(_type);
  load_existing_save();
  _audio_interface.start();
  while (!_is_abort) {
    if (!_pause)
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
    in.seekg(0, std::ios::beg);
    in.read(reinterpret_cast<char *>(gs.data()), gs.size());
    _components.cartridge->set_ram_content(gs.data(), gs.size());
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

void Gameboy::read_type() {
  Byte value = _components.mem_bus->read<Byte>(0x143);
  if (_type == GbType::DEFAULT) {
    if (value == 0xC0)
      _type = GbType::CGB;
    else if (value == 0x80)
      _type = GbType::CGB_DMG;
    else
      _type = GbType::DMG;
  } else if (_type == GbType::CGB && value == 0x80)
    _type = GbType::CGB_DMG;
  _components.ppu->set_gb_type(_type);
}

bool Gameboy::save_state(std::string save_name) {
  std::ofstream ofs(save_name);

  std::array<Byte, 0x10> title;

  for (int i = 0; i < 0x10; i++)
    title[i] = _components.mem_bus->read<Byte>(0x134 + i);

  {
    boost::archive::text_oarchive oa(ofs);
    oa << title;
    oa << *_components.mem_bus;
    oa << *_components.core;
    oa << *_components.cartridge;
    oa << *_components.ppu;
    oa << *_components.unit_working_ram;
    oa << *_components.interrupt_controller;
    oa << *_components.input_controller;
    oa << *_components.timer;
    oa << *_components.apu;
    oa << *_components.driver_screen;
    oa << *_components.bios;
  }
  ofs.close();
  return true;
}

bool Gameboy::load_state(std::string save_name) {
  std::ifstream ifs(save_name);

  std::array<Byte, 0x10> current_title;
  std::array<Byte, 0x10> title;

  for (int i = 0; i < 0x10; i++)
    current_title[i] = _components.mem_bus->read<Byte>(0x134 + i);

  {
    boost::archive::text_iarchive ia(ifs);
    ia >> title;

    if (current_title != title) {
      ifs.close();
      return false;
    }

    ia >> *_components.mem_bus;
    ia >> *_components.core;
    ia >> *_components.cartridge;
    ia >> *_components.ppu;
    ia >> *_components.unit_working_ram;
    ia >> *_components.interrupt_controller;
    ia >> *_components.input_controller;
    ia >> *_components.timer;
    ia >> *_components.apu;
    ia >> *_components.driver_screen;
    ia >> *_components.bios;
  }
  ifs.close();
  return true;
}
