#ifndef GAMEBOY_HPP
#define GAMEBOY_HPP

#include "cpu/Core.hpp"
#include "src/AMemoryBankController.hpp"
#include "src/Debugger.hpp"
#include "src/Fwd.hpp"
#include "src/GbType.hpp"
#include "src/PPU.hpp"
#include "src/ScreenOutput.hpp"
#include "src/sound/APU.hpp"
#include "src/sound/portaudio/PortAudioInterface.hpp"

#include <atomic>
#include <iostream>
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
  std::unique_ptr<sound::APU> apu;
  std::unique_ptr<ScreenOutput> driver_screen;
  std::unique_ptr<Bios> bios;

  ComponentsContainer(const std::string &, sound::AudioInterface *);
  ~ComponentsContainer();
};

class Accessor;

class Gameboy {
 private:
  using GameSave = std::array<Byte, AMemoryBankController::RAMSize>;

  sound::PortAudioInterface _audio_interface;
  ComponentsContainer _components;
  Debugger _debugger;
  GbType _type;

  std::string _rom_path;
  bool _is_abort;
  std::atomic<bool> _pause;

  friend class Accessor;

  void do_checksum();
  void read_type();

 public:
  Gameboy(const std::string &rom_path);
  Gameboy() = delete;

  ComponentsContainer &components() { return _components; }
  int run();
  void step();
  void init();
  void load_existing_save();
  void reset();
  void save(std::string save_name);
  void load_save(std::string save_name);
  uint32_t get_pixel(uint8_t y, uint8_t x) {
    return (_components.driver_screen->get_rgba(y, x));
  }
  void key_pressed_wraper(int val);
  void key_released_wraper(int val);
  void notify_debugger(Debugger::e_dbg_state state, int duration = 0);
  bool is_screen_filled() { return _components.ppu->is_screen_filled(); }
  auto getType() const { return _type; }
  Debugger &get_debugger() { return _debugger; }
  bool get_is_abort() const { return _is_abort; }
  void set_is_abort(bool val) { _is_abort = val; }
  bool get_pause() const { return _pause.load(); }
  void set_pause(bool val) { _pause.store(val); }
  void mute_gameboy() { _audio_interface.toggle_mute(); }

  class BadChecksum : public std::exception {
    const char *what() const noexcept { return "Invalid ROM checksum."; }
  };
};

#endif
