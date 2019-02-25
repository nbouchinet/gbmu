#ifndef GAMEBOY_HPP
#define GAMEBOY_HPP

#include "cpu/Core.hpp"
#include "src/AMemoryBankController.hpp"
#include "src/Debugger.hpp"
#include "src/Fwd.hpp"
#include "PPU.class.h"
#include "ScreenOutput.class.h"

#include <memory>

struct ComponentsContainer {
  std::unique_ptr<MemoryBus> mem_bus;
  std::unique_ptr<Core> core;
  std::unique_ptr<Cartridge> cartridge;
  std::unique_ptr<InterruptController> interrupt_controller;
  std::unique_ptr<Timer> timer;
  std::unique_ptr<LCDRegisters> lcd_registers;
  std::unique_ptr<UnitWorkingRAM> unit_working_ram;
  std::unique_ptr<PPU> ppu;
  std::unique_ptr<ScreenOutput> driver_screen;
  std::unique_ptr<Bios> bios;

  ComponentsContainer(const std::string &);
  ~ComponentsContainer();
};

class Accessor;
class Debugger;

class Gameboy{
private:
  struct GameSave {
    Byte ram[AMemoryBankController::RAMSize];
  };

  Core::Iterator _begin;
  Core::Iterator _end;
  ComponentsContainer _components;
  Debugger _debugger;

  friend class Accessor;

  void do_checksum();

public:
  Gameboy(const std::string &rom_path);
  Gameboy() = delete;

  int run();
  void step();
  void init();
  void save(std::string save_name);
  void load_save(std::string save_name);
  uint32_t get_pixel(uint8_t y, uint8_t x) { return (_components.driver_screen->getRGBA(y, x)); }

  class BadChecksum : public std::exception {
    const char *what() const noexcept { return "Invalid ROM checksum."; }
  };
};

#endif
