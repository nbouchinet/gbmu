#include "InterruptController.hpp"

#include "src/Gameboy.hpp"
#include "src/cpu/Core.hpp"
#include <unistd.h>

#include <iostream>

InterruptController::InterruptController(ComponentsContainer &components)
    : _components(components) {
  reset();
}

void InterruptController::reset() {
  _rIF = 0x0;
  _rIE = 0x0;
  _IME = false;
}

void InterruptController::write(Word addr, Byte val) {
  switch (addr) {
  case 0xFF0F:
    _rIF = val;
    break;
  case 0xFFFF:
    _rIE = val;
    break;
  default:
    return;
  }
}

Byte InterruptController::read(Word addr) const {
  switch (addr) {
  case 0xFF0F:
    return (_rIF);
  case 0xFFFF:
    return (_rIE);
  default:
    return (0);
  }
}

void InterruptController::parse_interrupt() {
  if (_rIF) {
    for (Byte i = 0; i < 5; i++) {
      if (((_rIF >> i) & 0x01) == ((_rIE >> i) & 0x01) && ((_rIE >> i) & 0x1)) {
        _components.core->notify_interrupt();
        if (_IME) {
          execute_interrupt(i);
        }
      }
    }
  }
}

void InterruptController::execute_interrupt(Byte interrupt) {
  _IME = false;
  _rIF = (_rIF & ~(0x01 << interrupt));
  switch (interrupt) {
  case 0:
    _components.core->start_interrupt(VBI);
    break;
  case 1:
    _components.core->start_interrupt(LCDCSI);
    break;
  case 2:
    _components.core->start_interrupt(TOI);
    break;
  case 3:
    _components.core->start_interrupt(STCI);
    break;
  case 4:
    _components.core->start_interrupt(JOYI);
    break;
  }
  _IME = true;
}

void InterruptController::request_interrupt(Word interrupt) {
  switch (interrupt) {
  case VBI:
    _rIF |= 1;
    break;
  case LCDCSI:
    _rIF |= 2;
    break;
  case TOI:
    _rIF |= 4;
    break;
  case STCI:
    _rIF |= 8;
    break;
  case JOYI:
    _rIF |= 16;
    break;
  }
}
