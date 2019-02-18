#include "src/sound/SoundChannel.hpp"

#include "utils/Operations_utils.hpp"
#include "src/sound/ModulationUnits.hpp"

namespace sound {

void SoundChannel::update(unsigned int modulation_unit_step) {
  if (not p_enabled) return;
  for (auto* modulation_unit : _modulation_units) {
    if (test_bit(modulation_unit_step, modulation_unit->trigger_steps()))
      if (not modulation_unit->call()) p_enabled = false;
  }
}

void SoundChannel::trigger() {
  p_enabled = true;
  do_trigger();
  for (auto* modulation_unit : _modulation_units) {
    modulation_unit->trigger();
  }
}

}  // namespace sound
