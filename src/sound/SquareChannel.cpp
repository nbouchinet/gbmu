#include "src/sound/SquareChannel.hpp"

#include "utils/Operations_utils.hpp"

#include <cassert>
#include <iostream>

static constexpr Word compute_timer(Word freq) noexcept {
  return (2048 - freq) * 4;
}

namespace sound {
const std::array<Byte, 4> SquareChannel::s_waveforms{
    {0b00000001, 0b10000001, 0b10000111, 0b01111110}};

void SquareChannel::do_update() {
  if (_timer == 0) {
    assert(_frequency);
    _timer = compute_timer(_frequency);
    if (++_waveform_step >= 8) _waveform_step = 0;
  }
  Byte waveform = s_waveforms[_waveform_selected];
  if (test_bit(_waveform_step, waveform)) {
    p_output_volume = _volume;
  } else
    p_output_volume = 0;
  --_timer;
}

void SquareChannel::do_trigger() { _timer = compute_timer(_frequency); }

void SquareChannel::write(Word addr, Byte v) {
  switch ((addr & 0xf) % 5) {
    case 0x0:
      assert(_sweep_enabled);
      _sweep.set_register(v);
      break;
    case 0x1:
      _waveform_selected = (v & 0xC0) >> 6;
      _length.set_length(v & 0x3f);
      break;
    case 0x2:
      _volume = (v & 0xf0) >> 4;
      _envelope.set_negate(-((v & 0x8) >> 3));
      _envelope.set_period(v & 0x7);
      break;
    case 0x3:
      _frequency = v | ((static_cast<Word>(_frequency) & 0x7) << 8);
      break;
    case 0x4:
      _length.enable((v & 0x40) >> 6);
      _frequency = (static_cast<Word>(v & 0x7) << 8) | (_frequency & 0xff);
      if (v & 0x80) trigger();
      break;
  }
}

Byte SquareChannel::read(Word addr) const {
  switch ((addr & 0xf) % 5) {
    case 0x0:
      assert(_sweep_enabled);
      return _sweep.get_register();
    case 0x1: {
      Word buf = _waveform_selected;
      return (buf << 6) | (_length.length() & 0x3f);
    }
    case 0x2:
      return (_volume << 4) | (_envelope.does_negate() << 3) |
             (_envelope.period() & 0x7);
    case 0x3:
      return _frequency & 0xff;
    case 0x4:
      return (_length.is_enabled() << 6) | ((_frequency & 0x700) >> 8);
  }
  assert(false);  // TODO throw some exception
}

}  // namespace sound
