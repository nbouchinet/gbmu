#include "src/sound/APU.hpp"

#include "src/sound/SoundChannel.hpp"
#include "src/sound/SquareChannel.hpp"
#include "utils/Operations_utils.hpp"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>

namespace sound {

APU::MemoryRangedChannel::~MemoryRangedChannel() {}

APU::APU(AudioInterface* interface)
    : _right_volume(0),
      _left_volume(0),
      _APU_on(false),
      _audio_interface(interface),
      _channels{{
          {0xff10, 0xff14, std::make_unique<SquareChannel>(true)},
          {0xff15, 0xff19, std::make_unique<SquareChannel>(false)},
          {0xff1a, 0xff1e, std::make_unique<SquareChannel>(false)},
          {0xff1f, 0xff23, std::make_unique<SquareChannel>(false)},
      }} {}

void APU::update_clock() {
  if (not _APU_on) return;
  if (--_update_countdown <= 0) {
    _update_countdown = CPU_FREQ / UPDATE_FREQ;
    for (auto& ranged_channel : _channels)
      ranged_channel.channel->update(_modulation_units_steps);
    if (++_modulation_units_steps >= 8) _modulation_units_steps = 0;
  }

  auto get_output = [&](Byte b) -> float {
    return (test_bit(b, _channel_to_terminal_output))
               ? _channels[0].channel->get_output()
               : 0;
  };
  _right_output[_output_index] = std::min(1.f, get_output(0));
  _left_output[_output_index++] = std::min(1.f, get_output(0));
  if (_output_index >= AudioInterface::SamplesTableSize) {
    while (
        not _audio_interface->queue_stereo_samples(_right_output, _left_output))
      ;
    _output_index = 0;
  }
}

Byte APU::read(Word addr) const {
  for (auto& ranged_channel : _channels) {
    if (addr >= ranged_channel.begin and addr <= ranged_channel.end)
      return ranged_channel.channel->read(addr);
  }
  switch (addr) {
    case 0xff24:
      return (_left_volume << 4) | _right_volume;
    case 0xff25:
      return _channel_to_terminal_output;
    case 0xff26: {
      Byte ret = _APU_on;
      ret = (ret << 7);
      for (auto i = 0; i < 4; ++i)
        ret |= _channels[i].channel->is_enabled() << i;
      return ret;
    }
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
  switch (addr) {
    case 0xff24:
      _left_volume = v & 0x70;
      _right_volume = v & 0x07;
      return;
    case 0xff25:
      _channel_to_terminal_output = v;
      return;
    case 0xff26: {
      _APU_on = v & 0x80;
      for (auto i = 0; i < 4; ++i) _channels[i].channel->enable(v & (1 << i));
      return;
    }
  }
  assert(false);
}
}  // namespace sound
