#ifndef WAVESOUND_HPP
#define WAVESOUND_HPP

#include "src/sound/ModulationUnits.hpp"
#include "src/sound/SoundChannel.hpp"

#include <array>

namespace sound {

class VolumeTable;

class WaveChannel : public SoundChannel {
 private:
  static constexpr std::size_t VolumeShiftCount = 4;
  static const Byte s_volume_shifts[VolumeShiftCount];

  Word _frequency = 0;
  Word _timer = 0;
  Byte _volume_code = 0;

  VolumeTable& _table;
  Byte _table_index = 0;

  LengthUnit _length;

  void do_update() override;
  void do_trigger() override;

 public:
  WaveChannel(VolumeTable& table) : _table(table), _length(255) {
    bind_module(&_length);
  }
  WaveChannel() = delete;

  void write(Word addr, Byte v) override;
  Byte read(Word addr) const override;
};

}  // namespace sound

#endif  // WAVESOUND_HPP
