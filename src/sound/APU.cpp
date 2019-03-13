#include "src/sound/APU.hpp"

#include "src/sound/NoiseChannel.hpp"
#include "src/sound/SquareChannel.hpp"
#include "src/sound/WaveChannel.hpp"
#include "utils/Operations_utils.hpp"

#include <cassert>
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
          {0xff1a, 0xff1e, std::make_unique<WaveChannel>(_wave_ram)},
          {0xff1f, 0xff23, std::make_unique<NoiseChannel>()},
      }} {}

void APU::update_clock() {
  if (--_update_countdown <= 0) {
    _update_countdown = (CPU_FREQ / UPDATE_FREQ);
    for (auto& ranged_channel : _channels) {
      ranged_channel.channel->update_modules(_modulation_units_steps);
      ranged_channel.channel->update();
    }
    if (++_modulation_units_steps >= 8) _modulation_units_steps = 0;
  } else {
    for (auto& ranged_channel : _channels) ranged_channel.channel->update();
  }

  if (--_sampling_countdown <= 0) {
    _sampling_countdown = (CPU_FREQ / SAMPLING_FREQ);
    float rvol = (static_cast<float>(_right_volume) + 1.f) / 8.f;
    float lvol = (static_cast<float>(_left_volume) + 1.f) / 8.f;

    _right_output[_output_index] =
        fetch_and_mix_samples(_channel_to_terminal_output, rvol);

    _left_output[_output_index++] =
        fetch_and_mix_samples((_channel_to_terminal_output & 0xf0) >> 4, lvol);

    if (_output_index >= AudioInterface::SamplesTableSize) {
      while (not _audio_interface->queue_stereo_samples(_right_output,
                                                        _left_output)) {}
      _output_index = 0;
    }
  }
}

float APU::fetch_and_mix_samples(Byte enabled_channels, float vol) const {
  std::vector<float> to_mix;
  Byte b = 0;
  for (const auto& chan : _channels) {
    if (chan.channel->is_enabled() and test_bit(b++, enabled_channels))
      to_mix.push_back(chan.channel->get_output());
  }
  return _audio_interface->mix(to_mix, vol);
}

void APU::update_clock(Word cycles) {
  if (not _APU_on) return;
  while (cycles--) {
    update_clock();
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
  if (addr >= 0xff30 and addr <= 0xff3f) return _wave_ram[addr & 0xf];
  else if (addr >= 0xff27 and addr <= 0xff2f)
    return 0;
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
      _left_volume = (v & 0x70) >> 4;
      _right_volume = v & 0x07;
      return;
    case 0xff25:
      _channel_to_terminal_output = v;
      return;
    case 0xff26: {
      _APU_on = (v & 0x80) >> 7;
      if (not _APU_on) _modulation_units_steps = 0;
      for (auto i = 0; i < 4; ++i) {
        _channels[i].channel->enable(v & (1 << i));
        if (not _APU_on) _channels[i].channel->clear();
      }
      return;
    }
  }
  if (addr >= 0xff30 and addr <= 0xff3f) {
    _wave_ram[addr & 0xf] = v;
    return;
  }
  else if (addr >= 0xff27 and addr <= 0xff2f)
    return;
  assert(false);
}
}  // namespace sound
