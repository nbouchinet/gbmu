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
  virtual void call() = 0;
};

class SweepUnit : public IModulationUnit {
  public:
    Byte trigger_steps() const override { return 0x44; /* 00100010 */ }
};

// -----------------------------------------------------------------------------

class SoundChannel {
 private:
  using ModUnitPtr = IModulationUnit*;
  std::vector<ModUnitPtr> _modulation_units;

  virtual void do_update() = 0;

 protected:
  int p_output_volume;
  bool p_muted;
  SoundChannel(std::vector<ModUnitPtr>&& units)
      : _modulation_units(std::move(units)), p_volume(0), p_muted(true) {}

 public:
  virtual ~SoundChannel() = default;

  void update(unsigned int modulation_unit_step) {
    for (auto& modulation_unit : _modulation_units) {
      if (test_bit(modulation_unit_step, modulation_unit->trigger_steps()))
        modulation_unit->call();
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

  // SweepUnit _sweep;
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
  SquareChannel() : SoundChannel({}) {}
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
