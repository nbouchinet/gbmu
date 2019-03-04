#ifndef NOISECHANNEL_HPP
#define NOISECHANNEL_HPP

#include "src/sound/SoundChannel.hpp"

#include "src/sound/ModulationUnits.hpp"

namespace sound {

class NoiseChannel : public SoundChannel {
 private:
  Word _timer = 0;
  Word _lsfr = 0;  // Linear feedback feed register
  Byte _shift = 0;
  bool _width_mode = false;
  Byte _divisor_code = 0;
  Byte _volume = 0;

  LengthUnit _length;
  EnvelopeUnit _envelope;

  void do_update() override;
  void do_trigger() override;

 public:
  NoiseChannel() : _length(63), _envelope(_volume) {
    bind_module(&_length);
    bind_module(&_envelope);
  }

  void write(Word, Byte) override;
  Byte read(Word) const override;

  inline static Word get_divider(Byte code) {
    if (code == 0) return 8u;
    return 16 * code;
  }
};

}  // namespace sound

#endif  // NOISECHANNEL_HPP
