#include "src/sound/APU.hpp"

#include "src/Gameboy.hpp"
#include "src/sound/NoiseChannel.hpp"
#include "src/sound/SquareChannel.hpp"
#include "src/sound/WaveChannel.hpp"
#include "utils/Operations_utils.hpp"

#include <unistd.h>
#include <cassert>

namespace sound {

APU::MemoryRangedChannel::~MemoryRangedChannel() {}

APU::APU(AudioInterface *interface, ComponentsContainer &c)
    : _audio_interface(interface),
      _comps(c),
      _channels{{
          {0xff10, 0xff14, std::make_unique<SquareChannel>(true)},
          {0xff15, 0xff19, std::make_unique<SquareChannel>(false)},
          {0xff1a, 0xff1e, std::make_unique<WaveChannel>(_wave_ram)},
          {0xff1f, 0xff23, std::make_unique<NoiseChannel>()},
      }} {}

#include <iostream>
void APU::update_clock() {
  if (--_update_countdown <= 0) {
    _update_countdown = (_comps.core->get_cpu_freq() * _speed / UPDATE_FREQ);
    for (auto &ranged_channel : _channels) {
      ranged_channel.channel->update_modules(_modulation_units_steps);
      ranged_channel.channel->update();
    }
    if (++_modulation_units_steps >= 8) _modulation_units_steps = 0;
  } else if (--_downsampling_countdown > 0) {
    for (auto &ranged_channel : _channels) {
      ranged_channel.channel->update();
    }
  } else {
    for (auto &ranged_channel : _channels) {
      ranged_channel.channel->update();
      ranged_channel.channel->downsample();
    }
    Byte rvol = right_volume() + 1;
    Byte lvol = left_volume() + 1;

    _right_output[_output_index] =
        fetch_and_mix_samples(_channel_to_terminal_output, rvol);

    _left_output[_output_index++] =
        fetch_and_mix_samples((_channel_to_terminal_output & 0xf0) >> 4, lvol);

    if (_output_index >= AudioInterface::SamplesTableSize) {
      while (not _audio_interface->queue_stereo_samples(_right_output,
                                                        _left_output)) {
        usleep(1);
      }
      _output_index = 0;
    }
    _downsampling_countdown = (_comps.core->get_cpu_freq() * _speed / SAMPLING_FREQ);
  }
}

void APU::set_speed(Byte value) {
  _speed = value;
  for (auto &chan : _channels) {
    chan.channel->set_speed(value);
  }
}

float APU::fetch_and_mix_samples(Byte enabled_channels, Byte vol) const {
  std::vector<AudioInterface::Sample> to_mix;
  to_mix.reserve(_channels.size());
  Byte b = 0;
  for (const auto &chan : _channels) {
    if (chan.channel->is_enabled() and test_bit(b++, enabled_channels))
      to_mix.push_back(chan.channel->get_output(vol));
  }
  return _audio_interface->mix(to_mix);
}

void APU::update_clock(Word cycles) {
  if (not _APU_on) return;
  while (cycles--) {
    update_clock();
  }
}

Byte APU::read(Word addr) const {
  for (auto &ranged_channel : _channels) {
    if (addr >= ranged_channel.begin and addr <= ranged_channel.end)
      return ranged_channel.channel->read(addr);
  }
  switch (addr) {
    case 0xff24:
      return _vin_and_volumes;
    case 0xff25:
      return _channel_to_terminal_output;
    case 0xff26: {
      Byte ret = _APU_on;
      ret = (ret << 7) | 0x70;
      for (auto i = 0u; i < _channels.size(); ++i)
        ret |= _channels[i].channel->is_enabled() << i;
      return ret;
    }
  }
  if (addr >= 0xff30 and addr <= 0xff3f)
    return _wave_ram[addr & 0xf];
  else if (addr >= 0xff27 and addr <= 0xff2f)
    return 0xff;
  return 0xff;
  assert(false);
}

void APU::write(Word addr, Byte v) {
  if (addr == 0xff26) {
    _APU_on = (v & 0x80) >> 7;
    if (not _APU_on) {
      for (auto &chan : _channels) {
        if (not _APU_on) chan.channel->clear();
      }
      clear();
    }
    return;
  }
  if (addr >= 0xff30 and addr <= 0xff3f) {
    _wave_ram[addr & 0xf] = v;
    return;
  } else if (addr >= 0xff27 and addr <= 0xff2f)
    return;
  if (not _APU_on) return;
  for (auto &ranged_channel : _channels) {
    if (addr >= ranged_channel.begin and addr <= ranged_channel.end) {
      ranged_channel.channel->write(addr, v);
      return;
    }
  }
  switch (addr) {
    case 0xff24:
      _vin_and_volumes = v;
      return;
    case 0xff25:
      _channel_to_terminal_output = v;
      return;
  }
  return;
  assert(false);
}

void APU::clear() {
  _vin_and_volumes = 0;
  _modulation_units_steps = 0;
  _channel_to_terminal_output = 0;
}

void APU::reset() {
  clear();
  _APU_on = false;
  _update_countdown = 0;
  _downsampling_countdown = 0;
  _modulation_units_steps = 0;
  _output_index = 0;
  _right_output.fill(0);
  _left_output.fill(0);
  _speed = 1;
  _wave_ram.clear();
  for (auto &c : _channels) c.channel->clear();
}

}  // namespace sound

