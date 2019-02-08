#include "Timer.hpp"

#include "src/Gameboy.hpp"
#include "src/cpu/InterruptController.hpp"

#include <iostream>

uint8_t Timer::read(Word addr) const {
  switch (addr) {
    case DIV:
      return _rDIV;
    case TIMA:
      return _rTIMA;
    case TMA:
      return _rTMA;
    case TAC:
      return _rTAC;
    default:
      return 0;
  }
}

void Timer::write(Word addr, uint8_t val) {
  uint8_t currentFrequence;
  uint8_t newFrequence;

  switch (addr) {
    case DIV:
      _rDIV = 0x0;
      break;
    case TIMA:
      _rTIMA = val;
      break;
    case TMA:
      _rTMA = val;
      break;
    case TAC:
      currentFrequence = GetFrequence();
      _rTAC = val & 0x7;
      newFrequence = GetFrequence();
      if (currentFrequence !=
          newFrequence) {  // Check if game try to change frequence
        SetFrequence();
      }
      break;
  }
}

void Timer::SetFrequence() {
  switch (GetFrequence() & 0x3) {
    case 0x0:
      _counter = 0x400;
      break;  // 4
    case 0x1:
      _counter = 0x10;
      break;  // 262
    case 0x2:
      _counter = 0x40;
      break;  // 65
    case 0x3:
      _counter = 0x100;
      break;  // 16
  }
}

void Timer::Update(Word cycles) {
  UpdateDivider(cycles);
  if (TimerEnabled()) {
    std::cout << "Timer Enabled" << std::endl;
    _counter -= cycles;
    if (_counter <= 0) SetFrequence();
    if (_rTIMA == 255) {  // Check if Timer Counter will overflow
      _rTIMA = _rTMA;     // Load Timer modulator value
      _components.interrupt_controller->RequestInterrupt(
          InterruptController::TOI);  // Request timer overflow interrupt
    } else {
      ++_rTIMA;  // Increment Timer counter
    }
  }
}

void Timer::UpdateDivider(Word cycles) {
  _rDIV += cycles;
  if (_rDIVCounter >= 255) {
    _rDIVCounter = 0;
    _rDIV++;
  }
}