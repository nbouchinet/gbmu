#include "src/sound/NoiseChannel.hpp"

#include <cassert>

namespace sound {

void NoiseChannel::do_update() {
  if (--_timer == 0) {
    _timer = get_divider(_divisor_code) << _shift;
  Byte xored = (_lsfr & 1);
  _lsfr >>= 1;
  xored ^= (_lsfr & 1);
  _lsfr |= xored << 15;
  if (_width_mode) _lsfr |= xored << 6;
  p_output_volume = (~_lsfr & 1) * _volume;
  }
}

void NoiseChannel::do_trigger() {
  _timer = get_divider(_divisor_code) << _shift;
  _lsfr = 0xffff;
}

void NoiseChannel::do_clear() {
  _timer = 0;
  _lsfr = 0;
  _shift = 0;
  _width_mode = false;
  _divisor_code = 0;
  _volume = 0;
}

void NoiseChannel::write(Word addr, Byte v) {
  switch (addr) {
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
    case 0xff20:
      return (_length.length() & 0x3f);
    case 0xff21:
      return (_volume << 4) | (_envelope.does_add() << 3) |
             (_envelope.period() & 0x7);
    case 0xff22:
      return (_shift << 4) | (_width_mode << 3) | (_divisor_code & 0x7);
    case 0xff23:
      return (_length.is_enabled() << 6);
  }
  assert(false);
}

}  // namespace sound
