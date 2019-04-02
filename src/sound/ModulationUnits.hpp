#ifndef MODULATIONUNITS_HPP
#define MODULATIONUNITS_HPP

#include "src/Fwd.hpp"

#include <boost/serialization/access.hpp>

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
  Byte _sweep_period;
  Byte _negate;
  Byte _shift;

  Byte _current_period;
  bool _enabled;
  bool _trigger_overflowed;

  Word _shadow_freq;
  Word& _frequency;

  Word frequency_calculation();
  bool does_overflow(Word f) { return f > 0x7ff; }

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

  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int) {
    ar& _sweep_period;
    ar& _negate;
    ar& _shift;
    ar& _current_period;
    ar& _enabled;
    ar& _trigger_overflowed;
    ar& _shadow_freq;
  }
};

class LengthUnit : public IModulationUnit {
 private:
  Byte _max_length;
  Byte _length;
  bool _enabled;

 public:
  LengthUnit(Byte max_len) : _max_length(max_len) { clear(); }
  Byte trigger_steps() const override { return 0b01010101; }

  void set_length(Byte l) {
    _length = (static_cast<Word>(_max_length) + 1) - l;
  }
  void enable(bool enable = true) { _enabled = enable; }
  auto length() const { return _length; }
  bool is_enabled() const { return _enabled; }

  bool call() override;
  void trigger() override;
  void clear() override;

  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int) {
    ar& _max_length;
    ar& _length;
    ar& _enabled;
  }
};

class EnvelopeUnit : public IModulationUnit {
 private:
  bool _add;
  Byte _period;
  bool _enabled;
  Byte _current_period;
  Byte& _volume;

 public:
  EnvelopeUnit() = delete;
  EnvelopeUnit(Byte& volume) : _volume(volume) { clear(); }

  Byte trigger_steps() const override { return 0b10000000; }

  void set_add(bool v) { _add = v; }
  void set_period(Byte v) { _period = v; }
  bool does_add() const { return _add; }

  auto is_enabled() const { return _enabled; }
  auto period() const { return _period; }

  bool call() override;
  void trigger() override;
  void clear() override;

  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int) {
    ar& _add;
    ar& _period;
    ar& _enabled;
    ar& _current_period;
    ar& _volume;
  }
};
}  // namespace sound

#endif  // MODULATIONUNITS_HPP
