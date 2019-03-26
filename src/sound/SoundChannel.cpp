#include "src/sound/SoundChannel.hpp"

#include "src/sound/ModulationUnits.hpp"
#include "utils/Operations_utils.hpp"

namespace sound {

void SoundChannel::update_modules(unsigned int modulation_unit_step) {
  if (not p_enabled) return;
  for (auto* modulation_unit : _modulation_units) {
    if (test_bit(modulation_unit_step, modulation_unit->trigger_steps())) {
      if (not modulation_unit->call()) {
        p_enabled = false;
      }
    }
  }
}

void SoundChannel::update() {
  if (p_enabled) {
    do_update();
    _summed_volumes += p_output_volume;
    ++_summed_volumes_nb;
  }
}

void SoundChannel::trigger() {
  p_enabled = true;
  do_trigger();
  for (auto* modulation_unit : _modulation_units) {
    modulation_unit->trigger();
  }
}

void SoundChannel::clear() {
  _summed_volumes = 0;
  _summed_volumes_nb = 0;
  p_enabled = false;
  p_output_volume = 0;
  for (auto& unit : _modulation_units) unit->clear();
  do_clear();
}

}  // namespace sound
