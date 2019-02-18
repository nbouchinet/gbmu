#include "src/sound/ModulationUnits.hpp"

namespace sound {

bool SweepUnit::call() {
  if (not _enabled or _current_period-- != 0 or _sweep_period == 0) return true;
  _current_period = _sweep_period;
  unsigned int new_freq = _frequency + (_frequency >> _shift) * -_negate;
  if (new_freq > 0x7f) return false;
  _frequency = new_freq;
  return true;
}

void SweepUnit::trigger() { 
  _current_period = _sweep_period; 
  _enabled = (_sweep_period or _shift);
}

bool LengthUnit::call() {
  if (not _enabled) return true;
  if (_length == 0) return false;
  --_length;
  return true;
}

void LengthUnit::trigger() {
  if (not _length) _length = _max_length;
}

bool EnvelopeUnit::call() {
  if (not _enabled) return true;
  if (_current_period-- != 0 or _period == 0) return true;
  _current_period = _period;
  if (_volume < 0 or _volume > 15)
    _enabled = false;
  else
    _volume += (_negate) ? -1 : 1;
  return true;
}

void EnvelopeUnit::trigger()  {
  _current_period = _period;
}

}  // namespace sound
