#include "PortAudioInterface.hpp"

#include <cassert>
#include <iostream>
#include <vector>

namespace sound {

portaudio::System& PortAudioInterface::get_system() {
  static portaudio::AutoSystem a;
  return portaudio::System::instance();
}

int PortAudioInterface::callback(const void*, void* output_buffer,
                                 unsigned long frames_per_buffer,
                                 const PaStreamCallbackTimeInfo*,
                                 PaStreamCallbackFlags) {
  // if (_lock) return paContinue;
  //std::cerr << "Read\n";
  bool locked = _lock;
  _lock = true;
  assert(output_buffer != nullptr);
  float** out = static_cast<float**>(output_buffer);

  for (auto i = 0u; i < frames_per_buffer; ++i) {
    bool can_cpy = _cursor < SamplesTableSize and not locked;
    out[0][i] = (can_cpy) ? _left_output[_cursor] : _last_sample_played.second;
    out[1][i] = (can_cpy) ? _right_output[_cursor] : _last_sample_played.first;
    if (can_cpy) {
      _last_sample_played.first = _right_output[_cursor];
      _last_sample_played.second = _left_output[_cursor];
      ++_cursor;
    }
  }
  if (not locked) _lock = false;
  return paContinue;
}

PortAudioInterface::PortAudioInterface() {
  portaudio::System& sys = get_system();
  portaudio::DirectionSpecificStreamParameters out_params(
      sys.defaultOutputDevice(), 2, portaudio::FLOAT32, false,
      sys.defaultOutputDevice().defaultLowOutputLatency(), NULL);
  portaudio::StreamParameters params(
      portaudio::DirectionSpecificStreamParameters::null(), out_params,
      SAMPLING_FREQ, FramesPerBuffer, paClipOff);
  _stream =
      std::make_unique<Stream>(params, *this, &PortAudioInterface::callback);
}

PortAudioInterface::~PortAudioInterface() { _stream->close(); }

bool PortAudioInterface::queue_stereo_samples(const MonoSamples& right,
                                              const MonoSamples& left) {
  if (_lock or _cursor < SamplesTableSize) return false;
  //std::cerr << "Write!\n";
  _lock = true;
  // for (auto & e : right)
  //   std::cerr << e << ", ";
  _right_output = right;
  _left_output = left;
  _cursor = 0;
  _lock = false;
  return true;
}

float PortAudioInterface::mix(const std::vector<float>& samples,
                              float volume) const {
  float ret = 0.f;
  for (const auto& sample : samples) {
    ret += sample / samples.size();
  }
  return ret * volume / 100.;
}

void PortAudioInterface::start() { _stream->start(); }

void PortAudioInterface::terminate() { _stream->stop(); }

}  // namespace sound
