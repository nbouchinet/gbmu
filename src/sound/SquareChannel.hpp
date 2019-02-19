#ifndef SQUARECHANNEL_HPP
#define SQUARECHANNEL_HPP

#include "src/sound/ModulationUnits.hpp"
#include "src/sound/SoundChannel.hpp"

#include <array>

namespace sound {

class SquareUnit : public IModulationUnit {
 private:
  static const std::array<Byte, 4> s_waveforms;
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

  void set_waveform_selected(Byte v) { _waveform_selected = v; }
  auto waveform_selected() const { return _waveform_selected; }
  auto& frequency() { return _frequency; }
  auto frequency() const { return _frequency; }

  bool call() override;
  void trigger() override {}
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
        _length(64),
        _envelope(_volume),
        _sweep_enabled(sweep_enabled) {
    if (sweep_enabled) bind_module(&_sweep);
    bind_module(&_square);
    bind_module(&_length);
    bind_module(&_envelope);
  }

  void write(Word addr, Byte v) override;
  Byte read(Word addr) const override;

  void do_trigger() override;
};

}  // namespace sound

#endif  // SQUARECHANNEL_HPP
