#ifndef GAMEBOY_HPP
#define GAMEBOY_HPP

#include "cpu/Core.hpp"
#include "src/AMemoryBankController.hpp"
#include "src/Debugger.hpp"
#include "src/Fwd.hpp"
#include "src/PPU.hpp"
#include "src/ScreenOutput.hpp"
#include <atomic>

#include <memory>

struct ComponentsContainer {
  std::unique_ptr<MemoryBus> mem_bus;
  std::unique_ptr<Core> core;
  std::unique_ptr<Cartridge> cartridge;
  std::unique_ptr<InterruptController> interrupt_controller;
  std::unique_ptr<InputController> input_controller;
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

  void set_cgb_flag();
  ComponentsContainer _components;
  Debugger _debugger;
  uint8_t _cgb_flag;

  std::atomic<bool> _wait;
  int _cycles = 0;
  std::string _rom_path;
  bool _is_abort;

  friend class Accessor;

  void do_checksum();

public:
  Gameboy(const std::string &rom_path);
  Gameboy() = delete;

  int run();
  void step();
  void init();
  void reset();
  void save(std::string save_name);
  void load_save(std::string save_name);
  uint32_t get_pixel(uint8_t y, uint8_t x) { return (_components.driver_screen->get_rgba(y, x)); }
  void handle_input_wraper(Byte val);
  void notify_debugger(Debugger::e_dbg_state state, int duration = 0);
  bool is_screen_filled() { return _components.ppu->is_screen_filled(); }
  const uint8_t &get_cgb_flag() const {return _cgb_flag;}
  Debugger &get_debugger() { return _debugger; }
  bool &get_is_abort() { return _is_abort; }
  void set_is_abort(bool val) { _is_abort = val; }

  void go() { _wait.store(false); }
  bool is_cycling() { return !_wait; }

  class BadChecksum : public std::exception {
    const char *what() const noexcept { return "Invalid ROM checksum."; }
  };
};

#endif
