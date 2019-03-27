#include "src/sound/APU.hpp"

#include "src/Gameboy.hpp"
#include "src/sound/NoiseChannel.hpp"
#include "src/sound/SquareChannel.hpp"
#include "src/sound/WaveChannel.hpp"
#include "utils/Operations_utils.hpp"

#include <unistd.h>
#include <cassert>
#include <iostream>

namespace sound {

APU::MemoryRangedChannel::~MemoryRangedChannel() {}

APU::APU(AudioInterface *interface, ComponentsContainer &c)
    : _audio_interface(interface),
      _comps(c),
      _channels{{
          {0xff10, 0xff14, std::make_unique<SquareChannel>(true)},
          {0xff15, 0xff19, std::make_unique<SquareChannel>(false)},
          {0xff1a, 0xff1e, std::make_unique<WaveChannel>(_wave_ram)},
          /*{0xff1f, 0xff23, std::make_unique<NoiseChannel>()},*/
      }} {
  _last_dump = std::chrono::system_clock::now();
}

void APU::update_clock() {
  if (--_update_countdown <= 0) {
    (void)_comps;
    _update_countdown = (CPU_FREQ * _speed / UPDATE_FREQ);
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
    _downsampling_countdown = (CPU_FREQ * _speed / SAMPLING_FREQ);
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
  return _audio_interface->mix(to_mix, 0);
}

void APU::update_clock(Word cycles) {
  if (not _APU_on) return;
  while (cycles--) {
    update_clock();
  }
}

void APU::clear() {
  _vin_and_volumes = 0;
  _modulation_units_steps = 0;
  _channel_to_terminal_output = 0;
}

void APU::dump() const { _channels[3].channel->dump(); }

Byte APU::read(Word addr) const {
  //  if (_dump)
  //    std::cerr << std::hex  << "APU read: " << addr << "\n";
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
  static std::map<Word, const char *> map{
      {0xFF10, "NR10_REG"}, {0xFF11, "NR11_REG"}, {0xFF12, "NR12_REG"},
      {0xFF13, "NR13_REG"}, {0xFF14, "NR14_REG"}, {0xFF16, "NR21_REG"},
      {0xFF17, "NR22_REG"}, {0xFF18, "NR23_REG"}, {0xFF19, "NR24_REG"},
      {0xFF1A, "NR30_REG"}, {0xFF1B, "NR31_REG"}, {0xFF1C, "NR32_REG"},
      {0xFF1D, "NR33_REG"}, {0xFF1E, "NR34_REG"}, {0xFF20, "NR41_REG"},
      {0xFF21, "NR42_REG"}, {0xFF22, "NR43_REG"}, {0xFF23, "NR44_REG"},
      {0xFF24, "NR50_REG"}, {0xFF25, "NR51_REG"}, {0xFF26, "NR52_REG"}};
  if (_dump) {
    auto now = std::chrono::system_clock::now();
    int ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - _last_dump)
            .count();
    if (ms) std::cerr << "delay(0x" << std::hex << ms << ");\n";
    if (map.find(addr) != map.end()) {
      std::cerr << std::hex << map[addr] << " = 0x" << +v << ";\n";
      if (addr == 0xff23 and v & 0x80) dump();
    }
    _last_dump = std::chrono::system_clock::now();
  }
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
}  // namespace sound

