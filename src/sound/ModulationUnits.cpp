#include "src/sound/ModulationUnits.hpp"
#include "src/sound/SoundChannel.hpp"

namespace sound {

bool SweepUnit::call() {
  if (not _enabled or --_current_period != 0 or _sweep_period == 0) {
    return true;
  }
  _current_period = _sweep_period;
  unsigned int new_freq = _frequency + (_frequency >> _shift) * -_negate;
  if (new_freq > 0x7ff) return false;
  _frequency = new_freq;
  return true;
}

void SweepUnit::trigger() { 
  _current_period = _sweep_period; 
  _enabled = (_sweep_period or _shift);
}

void SweepUnit::clear() {
  _sweep_period = 0;
  _negate = 0;
  _shift = 0;
  _current_period = 0;
  _enabled = false;
}

bool LengthUnit::call() {
  if (not _enabled) return true;
  if (--_length == 0) return false;
  return true;
}

void LengthUnit::trigger() {
  if (not _length) _length = _max_length;
}

void LengthUnit::clear() {
  _length = 0;
  _enabled = false;
}

bool EnvelopeUnit::call() {
  if (not _enabled) return true;
  if (--_current_period != 0 or _period == 0) return true;
  _current_period = _period;
  Byte new_vol = _volume + ((_add) ? 1 : -1);
  if (new_vol > SoundChannel::MaxVolume)
    _enabled = false;
  else
    _volume = new_vol;
  return true;
}

void EnvelopeUnit::trigger()  {
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
