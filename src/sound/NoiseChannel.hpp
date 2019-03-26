#ifndef NOISECHANNEL_HPP
#define NOISECHANNEL_HPP

#include "src/Fwd.hpp"

#include "src/sound/SoundChannel.hpp"
#include "src/sound/ModulationUnits.hpp"

namespace sound {

class NoiseChannel : public SoundChannel {
 private:
  Word _timer;
  Word _lfsr;  // Linear feedback feed register
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

  void dump() const override;

  // Word get_divider(Byte code) {
  //   auto s = _shift + 3;
  //   if (!code) {
  //     code = 1;
  //     --s;
  //   }
  //   return (code << s);
  // }
  inline static Word get_divider(Byte code) {
    Word ret = 8u;
    if (code != 0) ret = 16 * code;
    return ret;
  }
};

}  // namespace sound

#endif  // NOISECHANNEL_HPP
