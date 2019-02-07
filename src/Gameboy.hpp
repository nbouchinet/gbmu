#ifndef GAMEBOY_HPP
#define GAMEBOY_HPP

#include "src/Fwd.hpp"

#include <memory>

struct ComponentsContainer {
  std::unique_ptr<MemoryBus> mem_bus;
  std::unique_ptr<Core> core;
  std::unique_ptr<Cartridge> cartridge;
  std::unique_ptr<InterruptController> interrupt_controller;
  std::unique_ptr<Timer> timer;

  ComponentsContainer(const std::string &);
  ~ComponentsContainer();
};

class Gameboy {
 private:
  ComponentsContainer _components;

 public:
  Gameboy(const std::string &rom_path);
  Gameboy() = delete;

  int run();
  void init();
};

#endif
