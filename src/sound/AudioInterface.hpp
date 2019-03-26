#ifndef AUDIOINTERFACE_HPP
#define AUDIOINTERFACE_HPP

#include <array>
#include <vector>

#define SAMPLING_FREQ (44100)

namespace sound {

class AudioInterface {
 public:
  static constexpr std::size_t SamplesTableSize = 512;
  using Sample = float;
  using MonoSamples = std::array<Sample, SamplesTableSize>;

  struct StereoSample {
    Sample left, right;
  };

  virtual ~AudioInterface() = default;
  virtual bool queue_stereo_samples(const MonoSamples&, const MonoSamples&) = 0;
  virtual float mix(const std::vector<float>&) const = 0;
  virtual void start() = 0;
  virtual void terminate() = 0;
  virtual void toggle_mute() = 0;
};

}  // namespace sound

#endif  // AUDIOINTERFACE_HPP
