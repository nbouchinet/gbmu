#include "PortAudioInterface.hpp"

#include <cassert>
#include <chrono>
#include <exception>
#include <iostream>
#include <thread>
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
  _callback_lock = true;
  assert(output_buffer != nullptr);
  float** out = static_cast<float**>(output_buffer);

  for (auto i = 0u; i < frames_per_buffer; ++i) {
    bool can_cpy = _cursor < SamplesTableSize and not _fill_lock;
    out[0][i] = (can_cpy) ? _left_output[_cursor] : _last_sample_played.left;
    out[1][i] = (can_cpy) ? _right_output[_cursor] : _last_sample_played.right;
    if (can_cpy) {
      _last_sample_played.right = _right_output[_cursor];
      _last_sample_played.left = _left_output[_cursor];
      ++_cursor;
    }
    out[0][i] = _fade.apply(out[0][i]);
    out[1][i] = _fade.apply(out[1][i]);

    if (not _fill_lock) _fade.step();
  }
  _callback_lock = false;
  return paContinue;
}

PortAudioInterface::PortAudioInterface() {
  portaudio::System& sys = get_system();
  try {
    portaudio::Device& default_device = sys.defaultOutputDevice();
    portaudio::DirectionSpecificStreamParameters out_params(
        default_device, 2, portaudio::FLOAT32, false,
        default_device.defaultLowOutputLatency(), NULL);
    portaudio::StreamParameters params(
        portaudio::DirectionSpecificStreamParameters::null(), out_params,
        SAMPLING_FREQ, FramesPerBuffer, paClipOff);
    _stream =
        std::make_unique<Stream>(params, *this, &PortAudioInterface::callback);
  } catch (std::exception& e) {
    std::cerr << "[Warning] Unable to initialize audio output: " << e.what()
              << "\n";
    _stream = nullptr;
  }
}

PortAudioInterface::~PortAudioInterface() {
  if (_stream) _stream->close();
}

bool PortAudioInterface::queue_stereo_samples(const MonoSamples& right,
                                              const MonoSamples& left) {
  if (_stream == nullptr) {
    // Since gameboy is synchronized on the sound device sample retrieving, if
    // no sound device is available, we kinda do as if there is one by waiting
    // the good amount of time.
    std::chrono::milliseconds wait((SamplesTableSize * 1'000) / SAMPLING_FREQ -
                                   1);
    std::this_thread::sleep_for(wait);
    return true;
  }

  if (_callback_lock or _cursor < SamplesTableSize) return false;
  _fill_lock = true;
  if (_mute and _fade.done()) {
    _right_output.fill(0);
    _left_output.fill(0);
  } else {
    _right_output = right;
    _left_output = left;
  }
  _cursor = 0;
  _fill_lock = false;
  return true;
}

float PortAudioInterface::mix(const std::vector<float>& samples) const {
  float ret = 0.f;
  for (const auto& sample : samples) {
    ret += sample / samples.size();
  }
  // arbitrary volume lowering cause otherwise it's too aggressive
  return ret / 4.;
}

void PortAudioInterface::start() {
  if (_stream) _stream->start();
}

void PortAudioInterface::terminate() {
  if (_stream) _stream->stop();
}

void PortAudioInterface::toggle_mute() {
  constexpr float fade_time = .25;  // seconds
  _mute = !_mute;
  _fill_lock = true;
  if (_mute)
    _fade = FadeEffect(SAMPLING_FREQ * fade_time,
                               FadeEffect::Type::Descending);
  else
    _fade = FadeEffect(SAMPLING_FREQ * fade_time,
                               FadeEffect::Type::Ascending);
  _fill_lock = false;
}

}  // namespace sound
