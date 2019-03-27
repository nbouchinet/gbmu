#include "src/sound/NoiseChannel.hpp"

#include <cassert>
#include <iostream>

namespace sound {

void NoiseChannel::do_update() {
  if (--_timer == 0) {
    if (_shift < 0xe) {
      Byte xored = (_lfsr & 1);
      _lfsr >>= 1;
      xored ^= (_lfsr & 1);
      _lfsr |= xored << 14;
      if (_width_mode) {
        _lfsr = (_lfsr & ~0x40u) | xored << 6;
      }
      p_output_volume = (~_lfsr & 1) * _volume;
    }
    _timer = (get_divider(_divisor_code) << _shift) * p_speed;//TODO
  }
}

void NoiseChannel::do_trigger() {
  _lfsr = 0x7fff;
  _timer = (get_divider(_divisor_code) << _shift) * p_speed;//TODO
}

void NoiseChannel::do_clear() {
  _timer = 0;
  _lfsr = 0;
  _shift = 0;
  _width_mode = false;
  _divisor_code = 0;
  _volume = 0;
}

void NoiseChannel::dump() const {
}

void NoiseChannel::write(Word addr, Byte v) {
  switch (addr) {
    case 0xff1f:
      break;
    case 0xff20:
      _length.set_length(v & 0x3f);
      break;
    case 0xff21:
      _volume = (v & 0xf0) >> 4;
      _envelope.set_add((v & 0x8) >> 3);
      _envelope.set_period(v & 0x7);
      break;
    case 0xff22:
      _shift = (v & 0xf0) >> 4;
      _width_mode = ((v & 0x8) >> 3);
      _divisor_code = (v & 0x7);
      break;
    case 0xff23:
      _length.enable((v & 0x40) >> 6);
      if (v & 0x80) trigger();
      break;
  }
}

Byte NoiseChannel::read(Word addr) const {
  switch (addr) {
    case 0xff1f:
    case 0xff20:
      return 0xff;
    case 0xff21:
      return (_volume << 4) | (_envelope.does_add() << 3) |
             (_envelope.period() & 0x7);
    case 0xff22:
      return (_shift << 4) | (_width_mode << 3) | (_divisor_code & 0x7);
    case 0xff23:
      return (_length.is_enabled() << 6) | 0xbf;
  }
  assert(false);
}

}  // namespace sound
