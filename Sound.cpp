#include <bitset>
#include <cassert>
#include <cstdint>
#include <memory>
#include <vector>
#include "utils/Operations_utils.hpp"

using Byte = uint8_t;
using Word = uint16_t;
#define CPU_FREQ (4194304)

// -----------------------------------------------------------------------------

class IModulationUnit {
 public:
  virtual ~IModulationUnit() = default;

  virtual Byte trigger_steps() const = 0;
  virtual bool call() = 0;
};

class SweepUnit : public IModulationUnit {
 private:
  Byte _sweep_period : 3;
  Byte _negate : 1;
  Byte _shift : 3;

  Byte _current_period = 0;
  Word& _frequency;

 public:
  SweepUnit() = delete;
  SweepUnit(Word& frequency)
      : _sweep_period(0), _negate(0), _shift(0), _frequency(frequency) {}

  Byte trigger_steps() const override { return 0x44; /* 00100010 */ }

  Byte get_register() const {
    return (_sweep_period << 5) | (_negate << 3) | _shift;
  }

  bool call() override {
    if (_current_period-- != 0 or _sweep_period == 0) return true;
    _current_period = _sweep_period;
    unsigned int new_freq = _frequency + (_frequency >> _shift) * -_negate;
    if (new_freq > 0x7f) return false;
    _frequency = new_freq;
    return true;
  }
};

class LengthUnit : public IModulationUnit {
 private:
  Word _length = 0;
  bool _enabled = false;

 public:
  void set_length(Word l) { _length = l; }
  void enable(bool enable = true) { _enabled = enable; }

  Byte trigger_steps() const override { return 0x55; /* 01010101 */ }

  bool call() override {
    if (not _enabled) return true;
    if (_length == 0) return false;
    --_length;
    return true;
  }
};

class EnvelopeUnit : public IModulationUnit {
 private:
  Byte _negate : 1;
  Byte _period : 3;
  bool _enabled = false;
  Byte _current_period = 0;
  int& _volume;

 public:
  EnvelopeUnit() = delete;
  EnvelopeUnit(int& volume) : _negate(0), _period(0), _volume(volume) {}

  Byte trigger_steps() const override { return 0x80; /* 10000000 */ }

  bool call() override {
    if (not _enabled) return true;
    if (_current_period-- != 0 or _period == 0) return true;
    _current_period = _period;
    if (_volume < 0 or _volume > 15)
      _enabled = false;
    else
      _volume += (_negate) ? -1 : 1;
    return true;
  }
};
// -----------------------------------------------------------------------------

class SoundChannel {
 private:
  using ModUnitPtr = IModulationUnit*;
  std::vector<ModUnitPtr> _modulation_units;

  virtual void do_update() = 0;

 protected:
  int p_output_volume = 0;
  bool p_muted = true;
  bool p_enabled = true;

  void bind_module(ModUnitPtr module) { _modulation_units.push_back(module); }

 public:
  virtual ~SoundChannel() = default;

  void update(unsigned int modulation_unit_step) {
    if (not p_enabled) return;
    for (auto& modulation_unit : _modulation_units) {
      if (test_bit(modulation_unit_step, modulation_unit->trigger_steps()))
        if (not modulation_unit->call()) p_enabled = false;
    }
    do_update();
  }

  int get_output() const { return (p_muted) ? 0 : p_output_volume; }
};

class SquareChannel : public SoundChannel {
 private:
  static const std::array<Byte, 4> s_waveforms{
      0x1,  /* 00000001 */
      0x81, /* 10000001 */
      0x87, /* 10000111 */
      0x7E  /* 01111110 */
  };
  Byte _waveform_selected = 2;
  Byte _waveform_step = 0;
  Word _frequency = 0;
  Word _timer = 0;
  bool _init = false;
  int _volume = 0;

  SweepUnit _sweep;
  // LengthUnit _length;

  void do_update() override {
    if (_timer == 0) {
      assert(_frequency);
      _timer = (2048 - _frequency) *
               4;  // ??? this fucking formula is different in every doc i read.
    }
    if (++_waveform_step >= 8) _waveform_step = 0;
    Byte waveform = s_waveforms[_waveform_selected];
    if (test_bit(_waveform_step, waveform))
      p_output_volume = _volume;
    else
      p_output_volume = 0;
    --_timer;
  }

 public:
  SquareChannel() : _sweep(_frequency) { bind_module(&_sweep); }
};

// -----------------------------------------------------------------------------
//
class APU {
 private:
  std::vector<std::unique_ptr<SoundChannel>> _channels;
  unsigned int _cpu_cycles = CPU_FREQ / 512;
  unsigned int _modulation_units_steps = 0;

 public:
  void update_clock() {
    if (--_cpu_cycles <= 0) {
      _cpu_cycles = CPU_FREQ / 512;
      for (auto& channel : _channels) channel->update(_modulation_units_steps);
      if (++_modulation_units_steps >= 8) _modulation_units_steps = 0;
    }
  }
};
