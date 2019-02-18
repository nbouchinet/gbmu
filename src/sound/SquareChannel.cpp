#include "src/sound/SquareChannel.hpp"

#include "utils/Operations_utils.hpp"

#include <cassert>

namespace sound {

bool SquareUnit::call() {
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

void SquareChannel::write(Word addr, Byte v) {
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
      _square.frequency() =
          (static_cast<Word>(v) << 3) | (_square.frequency() & 0x7);
      break;
    case 0x4:
      if (v & 0x80) trigger();
      _length.enable(v & 0x40);
      _square.frequency() &= v & 0x7;
      break;
  }
}

Byte SquareChannel::read(Word addr) const {
  assert((addr & 0xfff0) == 0xff10);
  Word buf;
  switch ((addr & 0xf) % 5) {
    case 0x0:
      assert(_sweep_enabled);
      return _sweep.get_register();
    case 0x1:
      buf = _square.waveform_selected();
      return (buf << 6) | (_length.length() & 0x3f);
    case 0x2:
      return (_volume << 4) | (_envelope.does_negate() << 3) |
             (_envelope.period() & 0x7);
    case 0x3:
      return _square.frequency() & 0x7f8;
    case 0x4:
      return _length.is_enabled() << 6;
  }
  assert(false);  // TODO throw some exception
}

void SquareChannel::do_trigger() {
  _timer = _square.frequency();
  _volume = _volume_load;
}

}  // namespace sound
