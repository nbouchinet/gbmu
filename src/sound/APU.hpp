#ifndef APU_HPP
#define APU_HPP

#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"
#include "src/sound/AudioInterface.hpp"

#include <memory>

#define CPU_FREQ (4194304)
#define UPDATE_FREQ (512)

namespace sound {

class SoundChannel;

class APU : public IReadWrite {
 private:
  struct MemoryRangedChannel {
    Word begin, end;
    std::unique_ptr<SoundChannel> channel;
    ~MemoryRangedChannel();
  };

  int _update_countdown = 0;
  int _sampling_countdown = 0;
  unsigned int _modulation_units_steps = 0;
  Byte _right_volume: 3;
  Byte _left_volume: 3;
  bool _APU_on : 1;
  Byte _channel_to_terminal_output = 0;

  std::size_t _output_index = 0;
  AudioInterface::MonoSamples _right_output;
  AudioInterface::MonoSamples _left_output;

  AudioInterface * const _audio_interface;

  std::array<MemoryRangedChannel, 4> _channels;

  void update_clock();
 public:
  APU(AudioInterface*);
  APU() = delete;

  void update_clock(Word);
  Byte read(Word addr) const override;
  void write(Word addr, Byte) override;
};
}  // namespace sound

#endif  // APU_HPP
