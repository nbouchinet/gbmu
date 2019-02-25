#ifndef TIMER_H
#define TIMER_H

#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"

class Timer : public IReadWrite {
 private:
  static constexpr Word DIV = 0xFF04;   // Divider register
  static constexpr Word TIMA = 0xFF05;  // Timer counter
  static constexpr Word TMA = 0xFF06;   // Timer modulo
  static constexpr Word TAC = 0xFF07;   // Timer controller

  Byte _rDIV = 0x00;
  Byte _rTIMA = 0x00;
  Byte _rTMA = 0x00;
  Byte _rTAC : 3;
  Word _counter = 0x00;
  Byte _rDIVCounter = 0x00;

  ComponentsContainer& _components;

 public:
  Timer(ComponentsContainer& components) : _rTAC(0), _components(components){};

  Byte read(Word addr) const override;
  void write(Word addr, Byte val) override;

  auto GetFrequence() const { return read(TAC) & 0x3; }
  auto GetCounter() const { return _counter; }
  void UpdateDivider(Word cycles);
  bool TimerEnabled() const { return (_rTAC & 0x4); }
  void EnableTimer() { _rTAC |= 0x4; }
  void SetFrequence();
  void Update(Word cycles);
};

#endif /* TIMER_H */
