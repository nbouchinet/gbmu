#ifndef WAVESOUND_HPP
#define WAVESOUND_HPP

#include "src/Fwd.hpp"

#include "src/sound/ModulationUnits.hpp"
#include "src/sound/SoundChannel.hpp"

#include <array>

namespace sound {

class WaveChannel : public SoundChannel {
 private:
  static constexpr std::size_t VolumeShiftCount = 4;
  static const Byte s_volume_shifts[VolumeShiftCount];

  Word _frequency;
  Word _timer;
  Byte _volume_code;

  VolumeTable& _table;
  Byte _table_index;

  LengthUnit _length;

  void do_update() override;
  void do_trigger() override;
  void do_clear() override;

#define __serial_wave(OP) \
  ar OP _frequency;       \
  ar OP _timer;           \
  ar OP _volume_code;     \
  ar OP _table_index;     \
  ar OP _length;

  void do_serialize(boost::archive::text_iarchive& ar) override {
    __serial_wave(>>);
  }
  void do_serialize(boost::archive::text_oarchive& ar) override {
    __serial_wave(<<);
  }

 public:
  WaveChannel(VolumeTable& table) : _table(table), _length(255) {
    bind_module(&_length);
    clear();
  }
  WaveChannel() = delete;

  void write(Word addr, Byte v) override;
  Byte read(Word addr) const override;
};

}  // namespace sound

#endif  // WAVESOUND_HPP
