#include "src/sound/ModulationUnits.hpp"
#include "src/sound/SoundChannel.hpp"

namespace sound {

Word SweepUnit::frequency_calculation() {
  Word ret= _shadow_freq + (_shadow_freq >> _shift) * (_negate ? -1 : 1);
  return ret;
}

bool SweepUnit::call() {
  if (_trigger_overflowed) return false;
  if (not _enabled or --_current_period != 0) {
    return true;
  }
  if (_sweep_period == 0)
    _current_period = 8;
  else
    _current_period = _sweep_period;
  Word new_freq = frequency_calculation();
  if (does_overflow(new_freq)) return false;
  _frequency = _shadow_freq = new_freq;
  return not does_overflow(frequency_calculation());
}

void SweepUnit::trigger() {
  _shadow_freq = _frequency;
  _current_period = _sweep_period;
  _enabled = (_sweep_period or _shift);
  if (_shift)
    _trigger_overflowed = does_overflow(frequency_calculation());
  else
    _trigger_overflowed = false;
}

void SweepUnit::clear() {
  _sweep_period = 0;
  _negate = 0;
  _shift = 0;
  _current_period = 0;
  _enabled = false;
  _shadow_freq = 0;
  _trigger_overflowed = false;
}

bool LengthUnit::call() {
  if (not _enabled) return true;
  if (_length == 0) return false;
  --_length;
  return true;
}

void LengthUnit::trigger() {
  if (_length == 0) _length = _max_length;
}

void LengthUnit::clear() {
  _length = 0;
  _enabled = false;
}

bool EnvelopeUnit::call() {
  if (not _enabled) return true;
  if (--_current_period != 0) return true;
  if (_period == 0)
    _current_period = 8;
  else
    _current_period = _period;
  Byte new_vol = _volume + ((_add) ? 1 : -1);
  if (new_vol > SoundChannel::MaxVolume)
    _enabled = false;
  else
    _volume = new_vol;
  return true;
}

void EnvelopeUnit::trigger() {
  _current_period = _period;
  _enabled = _period != 0;
}

void EnvelopeUnit::clear() {
  _add = 0;
  _period = 0;
  _enabled = false;
  _current_period = 0;
}

}  // namespace sound
