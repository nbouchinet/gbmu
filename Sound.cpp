#include <array>
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

  bool call() override {
    if (_current_period-- != 0 or _sweep_period == 0) return true;
    _current_period = _sweep_period;
    unsigned int new_freq = _frequency + (_frequency >> _shift) * -_negate;
    if (new_freq > 0x7f) return false;
    _frequency = new_freq;
    return true;
  }

  Byte get_register() const {
    return (_sweep_period << 5) | (_negate << 3) | _shift;
  }

  void set_register(Byte v) {
    _sweep_period = v & 0x70;
    _negate = v & 0x08;
    _shift = v & 0x07;
  }
};

class LengthUnit : public IModulationUnit {
 private:
  Word _length = 0;
  bool _enabled = false;

 public:
  Byte trigger_steps() const override { return 0x55; /* 01010101 */ }

  bool call() override {
    if (not _enabled) return true;
    if (_length == 0) return false;
    --_length;
    return true;
  }

  void set_length(Word l) { _length = l; }
  void enable(bool enable = true) { _enabled = enable; }
};

class EnvelopeUnit : public IModulationUnit {
 private:
  bool _negate : 1;
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

  void set_negate(bool v) { _negate = v; }
  void set_period(Byte v) {
    _period = v;
    _current_period = v;
  }
};
// -----------------------------------------------------------------------------

class SoundChannel {
 private:
  using ModUnitPtr = IModulationUnit*;
  std::vector<ModUnitPtr> _modulation_units;

 protected:
  int p_output_volume = 0;
  bool p_muted = true;
  bool p_enabled = true;

  void bind_module(ModUnitPtr module) { _modulation_units.push_back(module); }
  SoundChannel() = default;

 public:
  virtual ~SoundChannel() = default;

  void update(unsigned int modulation_unit_step) {
    if (not p_enabled) return;
    for (auto& modulation_unit : _modulation_units) {
      if (test_bit(modulation_unit_step, modulation_unit->trigger_steps()))
        if (not modulation_unit->call()) p_enabled = false;
    }
  }

  int get_output() const {
    return (p_muted or not p_enabled) ? 0 : p_output_volume;
  }
};

class SquareUnit : public IModulationUnit {
 private:
  static constexpr std::array<Byte, 4> s_waveforms{
      0x01, /* 00000001 */
      0x81, /* 10000001 */
      0x87, /* 10000111 */
      0x7E  /* 01111110 */
  };
  Byte _waveform_selected = 2;
  Byte _waveform_step = 0;
  Word _frequency = 0;

  int& _volume;
  int& _output_volume;
  Word& _timer;

 public:
  SquareUnit() = delete;
  SquareUnit(int& volume, int& out_volume, Word& timer)
      : _volume(volume), _output_volume(out_volume), _timer(timer) {}

  Byte trigger_steps() const override { return 0xff; }
  bool call() override {
    if (_timer == 0) {
      assert(_frequency);
      _timer = (2048 - _frequency) *
               4;  // ??? this fucking formula is different in every doc i read.
    }
    if (++_waveform_step >= 8) _waveform_step = 0;
    Byte waveform = s_waveforms[_waveform_selected];
    if (test_bit(_waveform_step, waveform))
      _output_volume = _volume;
    else
      _output_volume = 0;
    --_timer;
    return true;
  }

  void set_waveform_selected(Byte v) { _waveform_selected = v; }
  auto &frequency() { return _frequency; }
};

class SquareChannel : public SoundChannel {
 private:
  int _volume = 0;
  int _volume_load = 0;
  Word _timer = 0;

  SweepUnit _sweep;
  SquareUnit _square;
  LengthUnit _length;
  EnvelopeUnit _envelope;

  bool _sweep_enabled;

 public:
  SquareChannel(bool sweep_enabled = true)
      : _sweep(_timer),
        _square(_volume, p_output_volume, _timer),
        _envelope(_volume),
        _sweep_enabled(sweep_enabled) {
    if (sweep_enabled) bind_module(&_sweep);
    bind_module(&_square);
    bind_module(&_length);
    bind_module(&_envelope);
  }

  void write(Word addr, Byte v) {
    assert((addr & 0xfff0) == 0xff10);
    switch ((addr & 0xf) % 5) {
      case 0x0:
        assert(_sweep_enabled);
        _sweep.set_register(v);
        break;
      case 0x1:
        _square.set_waveform_selected(v & 0xC0);
        _length.set_length(v & 0x3f);
        break;
      case 0x2:
        _volume = _volume_load = v & 0xf0;
        _envelope.set_negate(~(v & 0x8));
        _envelope.set_period(v & 0x7);
        break;
      case 0x3:
        _square.frequency() = (static_cast<Word>(v) << 3) | (_square.frequency() & 0x7);
        break;
      case 0x4:
        if (v & 0x80)
          trigger_modules();
        _length.enable(v & 0x40);
        _square.frequency() &= v & 0x7;;
        break;
    }
  }
};

// -----------------------------------------------------------------------------
//
class APU {
 private:
  std::vector<std::unique_ptr<SoundChannel>> _channels;
  int _cpu_cycles = CPU_FREQ / 512;
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
