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
  Byte enabled = (_rIE & _rIF) & 0x0F;

  if (enabled) {
    for (Byte i = 0; i < 5; i++) {
      if ((enabled >> i) & 0x01) {
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
  _rIF = (_rIF & ~(0x01 << interrupt));
}

void InterruptController::request_interrupt(Word interrupt) {
  switch (interrupt) {
  case VBI:
    _rIF |= 0x01;
    break;
  case LCDCSI:
    _rIF |= 0x02;
    break;
  case TOI:
    _rIF |= 0x04;
    break;
  case STCI:
    _rIF |= 0x08;
    break;
  case JOYI:
    _rIF |= 0x0F;
    break;
  }
}
