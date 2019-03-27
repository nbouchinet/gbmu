#ifndef TIMER_H
#define TIMER_H

#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"

class Timer : public IReadWrite {
public:
  static constexpr Word Frequencies[4] = {0x400, 0x10, 0x40, 0x100};

private:
  class Counter {
  private:
    bool _is_running;
    Byte _value;
    Byte _freq;
    int _cycles;

  public:
    Counter(Byte freq);
    bool step(Word freq);
    void set_value(Byte value) { _value = value; }
    void set_frequency(Byte freq) {
      _freq = freq;
      _cycles = Timer::Frequencies[freq];
    }
    Byte get_value() const { return _value; }
    void start() { _is_running = true; }
    void stop() { _is_running = false; }
  };

private:
  static constexpr Word DIV = 0xFF04;  // Divider register
  static constexpr Word TIMA = 0xFF05; // Timer counter
  static constexpr Word TMA = 0xFF06;  // Timer modulo
  static constexpr Word TAC = 0xFF07;  // Timer controller
  static constexpr Word KEY1 = 0xFF4D; // Speed controller

  Byte _rDIV;
  Byte _rTIMA;
  Byte _rTMA;
  Byte _rTAC : 3;
  Byte _rKEY1;
  int _counter;
  Word _rDIVCounter;

  ComponentsContainer &_components;

public:
  Timer(ComponentsContainer &components)
      : _components(components), _timer_counter(0x00),
        _divider_counter(0x03) {
    reset();
  };

  void reset();

  Byte read(Word addr) const override;
  void write(Word addr, Byte val) override;

  auto get_frequence() const { return read(TAC) & 0x3; }
  auto get_counter() const { return _counter; }
  void update_divider(Word cycles);
  bool timer_enabled() const { return (_rTAC & 0x4); }
  void enable_timer() { _rTAC |= 0x4; }
  void set_frequence();
  void update(Word cycles);

  Counter _timer_counter;
  Counter _divider_counter;
};

#endif /* TIMER_H */
