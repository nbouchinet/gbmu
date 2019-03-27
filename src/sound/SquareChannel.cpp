#include "src/sound/SquareChannel.hpp"

#include "utils/Operations_utils.hpp"

#include <cassert>
#include <iostream>

static constexpr Word compute_timer(Word freq, Byte speed) noexcept {
  return ((2048 - freq) * 4) * speed;
}

namespace sound {
const std::array<Byte, 4> SquareChannel::s_waveforms{
    {0b00000001, 0b10000001, 0b10000111, 0b01111110}};

void SquareChannel::do_update() {
  if (_timer == 0) {
    _timer = compute_timer(_frequency, p_speed);
    if (++_waveform_step >= 8) _waveform_step = 0;
  }
  Byte waveform = s_waveforms[_waveform_selected];
  if (test_bit(_waveform_step, waveform)) {
    p_output_volume = _volume;
  } else
    p_output_volume = 0;
  --_timer;
}

void SquareChannel::do_trigger() { _timer = compute_timer(_frequency, p_speed); }

void SquareChannel::do_clear() {
  _waveform_selected = 0;
  _waveform_step = 0;
  _frequency = 0;
  _volume = 0;
  _timer = 0;
}

void SquareChannel::write(Word addr, Byte v) {
  switch ((addr & 0xf) % 5) {
    case 0x0:
      _sweep.set_register(v);
      break;
    case 0x1:
      _waveform_selected = (v & 0xC0) >> 6;
      _length.set_length(v & 0x3f);
      break;
    case 0x2:
      _volume = (v & 0xf0) >> 4;
      _envelope.set_add((v & 0x8) >> 3);
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
  static const Byte or_table[10]{0x80, 0x3f, 0x00, 0xff, 0xbf,
                                 0xff, 0x3f, 0x00, 0xff, 0xbf};
  Byte ret;
  Byte low_addr_nibble = addr & 0xf;
  assert(low_addr_nibble < 10);
  switch (low_addr_nibble % 5) {
    case 0x0:
      ret = _sweep.get_register();
      break;
    case 0x1: {
      Word buf = _waveform_selected;
      ret = (buf << 6);
      break;
    }
    case 0x2:
      ret = (_volume << 4) | (_envelope.does_add() << 3) |
            (_envelope.period() & 0x7);
      break;
    case 0x3:
      ret = 0;
      break;
    case 0x4:
      ret = (_length.is_enabled() << 6);
      break;
  }
  ret |= or_table[low_addr_nibble];
  return ret;
}
}  // namespace sound
