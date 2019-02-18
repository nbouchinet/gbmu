#include "src/sound/APU.hpp"

#include "src/sound/SoundChannel.hpp"
#include "src/sound/SquareChannel.hpp"

#include <cassert>

namespace sound {

APU::APU()
    : _channels{{0xff10, 0xff14, std::make_unique<SquareChannel>(true)},
                {0xff15, 0xff19, std::make_unique<SquareChannel>(false)}} {}

void APU::update_clock() {
  if (--_cpu_cycles <= 0) {
    _cpu_cycles = CPU_FREQ / 512;
    for (auto& ranged_channel : _channels)
      ranged_channel.channel->update(_modulation_units_steps);
    if (++_modulation_units_steps >= 8) _modulation_units_steps = 0;
  }
}

Byte APU::read(Word addr) const {
  for (auto& ranged_channel : _channels) {
    if (addr >= ranged_channel.begin and addr <= ranged_channel.end)
      return ranged_channel.channel->read(addr);
  }
  assert(false);
}

void APU::write(Word addr, Byte v) {
  for (auto& ranged_channel : _channels) {
    if (addr >= ranged_channel.begin and addr <= ranged_channel.end) {
      ranged_channel.channel->write(addr, v);
      return;
    }
  }
  assert(false);
}
}  // namespace sound
