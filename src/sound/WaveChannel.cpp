#include "src/sound/WaveChannel.hpp"
#include "src/sound/VolumeTable.hpp"

#include <cassert>
#include <iostream>

static constexpr Word compute_timer(Word freq) noexcept {
  return (2048 - freq) * 2;
}

namespace sound {

const Byte WaveChannel::s_volume_shifts[VolumeShiftCount] = {4, 0, 1, 2};

void WaveChannel::do_update() {
  if (_timer == 0) {
    assert(_frequency);
    _timer = compute_timer(_frequency);
    if (++_table_index >= _table.size()) _table_index = 0;
  }
  assert(_volume_code < VolumeShiftCount);
  Byte shift = s_volume_shifts[_volume_code];
  p_output_volume = _table.get_nibble(_table_index) >> shift;
  --_timer;
}

void WaveChannel::do_trigger() {
  _timer = compute_timer(_frequency);
  _table_index = 0;
}

void WaveChannel::write(Word addr, Byte v) {
  switch ((addr & 0xf) % 5) {
    case 0x0:
      p_enabled = v & 0x80;
      break;
    case 0x1:
      _length.set_length(v);
      break;
    case 0x2:
      _volume_code = (v & 0x60) >> 5;
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

Byte WaveChannel::read(Word addr) const {
  switch ((addr & 0xf) % 5) {
    case 0x0:
      return p_enabled << 7;
    case 0x1:
      return _length.length();
    case 0x2:
      return _volume_code << 5;
    case 0x3:
      return _frequency & 0xff;
    case 0x4:
      return (_length.is_enabled() << 6) | ((_frequency & 0x700) >> 8);
  }

  assert(false);  // TODO throw some exception
}

}  // namespace sound
