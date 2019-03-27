#include "PortAudioInterface.hpp"

#include <cassert>
#include <vector>
#include <iostream>

namespace sound {

portaudio::System& PortAudioInterface::get_system() {
  static portaudio::AutoSystem a;
  return portaudio::System::instance();
}

int PortAudioInterface::callback(const void*, void* output_buffer,
                                 unsigned long frames_per_buffer,
                                 const PaStreamCallbackTimeInfo*,
                                 PaStreamCallbackFlags) {
  _callback_lock = true;
  assert(output_buffer != nullptr);
  float** out = static_cast<float**>(output_buffer);

  for (auto i = 0u; i < frames_per_buffer; ++i) {
    bool can_cpy = _cursor < SamplesTableSize and not _fill_lock;
    out[0][i] = (can_cpy) ? _left_output[_cursor] : _last_sample_played.second;
    out[1][i] = (can_cpy) ? _right_output[_cursor] : _last_sample_played.first;
    if (can_cpy) {
      _last_sample_played.first = _right_output[_cursor];
      _last_sample_played.second = _left_output[_cursor];
      ++_cursor;
    }
  }
  _callback_lock = false;
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
  if (_callback_lock or _cursor < SamplesTableSize) return false;
  _fill_lock = true;
  _right_output = right;
  _left_output = left;
  _cursor = 0;
  _fill_lock = false;
  return true;
}

float PortAudioInterface::mix(const std::vector<float>& samples, float) const {
  float ret = 0.f;
  for (const auto& sample : samples) {
    ret += sample / samples.size();
  }
  // arbitrary volume lowering cause otherwise it's too aggressive
  return ret / 4.;
}

void PortAudioInterface::start() { _stream->start(); }

void PortAudioInterface::terminate() { _stream->stop(); }

}  // namespace sound
