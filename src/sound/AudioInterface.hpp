#ifndef AUDIOINTERFACE_HPP
#define AUDIOINTERFACE_HPP

#include <array>

#define SAMPLING_FREQ (44100)

namespace sound {

class AudioInterface {
 public:
  static constexpr std::size_t SamplesTableSize = 1024;
  using Sample = float;
  using MonoSamples = std::array<Sample, SamplesTableSize>;

  virtual ~AudioInterface() = default;
  virtual bool queue_stereo_samples(const MonoSamples&, const MonoSamples&) = 0;
  virtual void mix(Sample&, Sample, float volume) const = 0;
  virtual void start() = 0;
  virtual void terminate() = 0;
};

}  // namespace sound

#endif  // AUDIOINTERFACE_HPP
