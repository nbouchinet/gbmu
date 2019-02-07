#ifndef INTERRUPTCONTROLLER_H
#define INTERRUPTCONTROLLER_H

#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"

class InterruptController : public IReadWrite {
 private:
  ComponentsContainer& _components;
  Byte _rIF : 5;  // 0xFF0F
  Byte _rIE : 5;  // 0xFFFF
  bool _IME;

 public:
  static constexpr Word VBI = 0x0040;     // Vertical Blank
  static constexpr Word LCDCSI = 0x0048;  // LCDC Status
  static constexpr Word TOI = 0x0050;     // Timer Overflow
  static constexpr Word STCI = 0x0058;    // Serial Transfert Completion
  static constexpr Word JOYI = 0x0060;    // Joypad

  void write(Word addr, Byte val) override;
  Byte read(Word addr) const override;
  void ParseInterrupt();
  void ExecuteInterrupt(Byte interrupt);
  void RequestInterrupt(Word interrupt);

  void SetIME(bool state) { _IME = state; }
  bool GetIME() const { return _IME; }

  InterruptController(ComponentsContainer& components);
};

#endif /* INTERRUPTCONTROLLER_H */
