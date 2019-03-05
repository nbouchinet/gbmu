#ifndef MODULATIONUNITS_HPP
#define MODULATIONUNITS_HPP

#include "src/Fwd.hpp"

namespace sound {

class IModulationUnit {
 public:
  virtual ~IModulationUnit() = default;

  virtual Byte trigger_steps() const = 0;
  virtual bool call() = 0;
  virtual void trigger() = 0;
  virtual void clear() = 0;
};

class SweepUnit : public IModulationUnit {
 private:
  Byte _sweep_period : 3;
  Byte _negate : 1;
  Byte _shift : 3;

  Byte _current_period;
  bool _enabled;
  Word& _frequency;

 public:
  SweepUnit() = delete;
  SweepUnit(Word& frequency) : _frequency(frequency) { clear(); }

  Byte trigger_steps() const override { return 0b00100010; }

  Byte get_register() const {
    return (_sweep_period << 4) | (_negate << 3) | _shift;
  }

  void set_register(Byte v) {
    _sweep_period = (v & 0x70) >> 4;
    _negate = (v & 0x08) >> 3;
    _shift = v & 0x07;
  }

  auto sweep_period() const { return _sweep_period; }
  auto negate() const { return _negate; }
  auto shift() const { return _shift; }
  auto current_period() const { return _current_period; }
  auto is_enabled() const { return _enabled; }

  bool call() override;
  void trigger() override;
  void clear() override;
};

class LengthUnit : public IModulationUnit {
 private:
  Byte _max_length;
  Byte _length;
  bool _enabled;

 public:
  LengthUnit(Byte max_len) : _max_length(max_len) { clear(); }
  Byte trigger_steps() const override { return 0b01010101; }

  void set_length(Byte l) { _length = l; }
  void enable(bool enable = true) { _enabled = enable; }
  auto length() const { return _length; }
  bool is_enabled() const { return _enabled; }

  bool call() override;
  void trigger() override;
  void clear() override;
};

class EnvelopeUnit : public IModulationUnit {
 private:
  bool _negate : 1;
  Byte _period : 3;
  bool _enabled; 
  Byte _current_period;
  Byte& _volume;

 public:
  EnvelopeUnit() = delete;
  EnvelopeUnit(Byte& volume) : _volume(volume) { clear(); }

  Byte trigger_steps() const override { return 0b10000000; }

  void set_negate(bool v) { _negate = v; }
  void set_period(Byte v) { _period = v; }
  bool does_negate() const { return _negate; }

  auto is_enabled() const { return _enabled; }
  auto period() const { return _period; }

  bool call() override;
  void trigger() override;
  void clear() override;
};
}  // namespace sound

#endif  // MODULATIONUNITS_HPP
