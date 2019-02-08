#include "InterruptController.hpp"

#include "src/Gameboy.hpp"
#include "src/cpu/Core.hpp"

#include <iostream>

InterruptController::InterruptController(ComponentsContainer& components)
    : _components(components), _rIF(0), _rIE(0), _IME(false) {}

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

void InterruptController::ParseInterrupt() {
  Byte rIF;
  Byte rIE;

  rIF = _rIF;
  rIE = _rIE;
  if (rIF) {
    for (Byte i = 0; i < 5; i--) {
      if ((rIF & 0x01) == (rIE & 0x01)) {
        _components.core->notify_interrupt();
        if (_IME)
          ExecuteInterrupt(i);
      }
      rIF >>= rIF;
      rIE >>= rIE;
    }
  }
}

void InterruptController::ExecuteInterrupt(Byte interrupt) {
  _IME = false;
  _rIF = (_rIF & ~interrupt);
  switch (interrupt) {
    case 0:
      std::cout << "vertical blank interrupt" << std::endl;
      _components.core->instr_call(Core::JumpCondition::None, VBI);
      break;
    case 1:
      std::cout << "lcdc status interrupt" << std::endl;
      _components.core->instr_call(Core::JumpCondition::None, LCDCSI);
      break;
    case 2:
      std::cout << "timer overflow interrupt" << std::endl;
      _components.core->instr_call(Core::JumpCondition::None, TOI);
      break;
    case 3:
      break;
    case 4:
      std::cout << "joypad interrupt" << std::endl;
      _components.core->instr_call(Core::JumpCondition::None, JOYI);
      break;
  }
}

void InterruptController::RequestInterrupt(Word interrupt) {
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
