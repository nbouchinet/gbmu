#ifndef PORTAUDIOINTERFACE_HPP
#define PORTAUDIOINTERFACE_HPP

#include "src/sound/AudioInterface.hpp"

#include <memory>
#include <utility>
#include <portaudiocpp/PortAudioCpp.hxx>
#include <atomic>

namespace sound {
class PortAudioInterface : public AudioInterface {
 private:
  static constexpr std::size_t FramesPerBuffer = 64;
  using Stream = portaudio::MemFunCallbackStream<PortAudioInterface>; 
  using StereoSample = std::pair<float, float>; // TODO define a Sample type


  MonoSamples _right_output = {};
  MonoSamples _left_output = {};
  std::size_t _cursor = SamplesTableSize;
  volatile bool _callback_lock = false;
  volatile bool _fill_lock = false;
  StereoSample _last_sample_played = {0., 0.};
  std::unique_ptr<Stream> _stream = nullptr;

  std::atomic_bool _mute = ATOMIC_VAR_INIT(false);

  int callback(const void* input_buffer, void* output_uffer,
               unsigned long frames_per_buffer, const PaStreamCallbackTimeInfo*,
               PaStreamCallbackFlags);

  static portaudio::System& get_system();

 public:
  PortAudioInterface();
  ~PortAudioInterface();
  bool queue_stereo_samples(const MonoSamples&, const MonoSamples&) override;
  float mix(const std::vector<float>&, float volume) const override;
  void start() override;
  void terminate() override;
  void toggle_mute() override;
};
}  // namespace sound

#endif  // PORTAUDIOINTERFACE_HPP
