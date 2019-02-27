#ifndef BIOS_H
#define BIOS_H

#include "Fwd.hpp"

#include "Gameboy.hpp"
#include "MemoryBus.hpp"

#include <exception>
#include <vector>

class Bios {
 public:
  class BadLogo : public std::exception {
   public:
    const char *what() const noexcept { return "Bad Nintendo Logo"; }
  };

 private:
  ComponentsContainer &_components;

 public:
  Bios(ComponentsContainer &components) : _components(components) {}
  Bios() = delete;

  void start();
};

// class Bios {
//  class BadLogo : public std::exception {
//   public:
//    const char *what() const noexcept { return "Bad Nintendo Logo"; }
//  };
//
// private:
//  ComponentsContainer &_components;
//
//  static const std::vector<Byte> _nintendo_logo; = {
//      0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83,
//      0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
//      0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63,
//      0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E,
//  };
//
// public:
//  Bios(ComponentsContainer &components) : _components(components) {}
//  void compare_logo();
//  std::vector<Byte> dump_logo();
//};

#endif /* BIOS_H */
