#ifndef NOISECHANNEL_HPP
#define NOISECHANNEL_HPP

#include "src/Fwd.hpp"

#include "src/sound/SoundChannel.hpp"
#include "src/sound/ModulationUnits.hpp"

namespace sound {

class NoiseChannel : public SoundChannel {
 private:
  Word _timer;
  Word _lsfr;  // Linear feedback feed register
  Byte _shift;
  bool _width_mode;
  Byte _divisor_code;
  Byte _volume;

  LengthUnit _length;
  EnvelopeUnit _envelope;

  void do_update() override;
  void do_trigger() override;
  void do_clear() override;

 public:
  NoiseChannel() : _length(63), _envelope(_volume) {
    bind_module(&_length);
    bind_module(&_envelope);
    clear();
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
