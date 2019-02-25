#include "gtest/gtest.h"

#include "src/sound/APU.hpp"
#include "src/sound/PortAudioInterface.hpp"

#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <thread>

void loop_at_41mhz(std::function<void(void)> action) {
  using namespace std::chrono;
  constexpr nanoseconds interval(1000000000LL / CPU_FREQ);
  auto time = high_resolution_clock::now();
  while (true) {
  //  while (duration_cast<nanoseconds>(high_resolution_clock::now() - time) <
  //         interval)
  //    ;
    action();
    time = high_resolution_clock::now();
  }
}

void test_audio_interface(sound::AudioInterface *i) {
  sound::AudioInterface::MonoSamples sine;
  auto size = sine.size();
  // std::srand(std::time(0));
  i->start();
  //  auto rand = std::rand() % 3 + 2;
  for (auto i = 0u; i < size; ++i) {
    auto sin = std::sin(
        (static_cast<double>(i) / static_cast<double>(size / 10)) * M_PI * 2.);
    sine[i] = (sin >= 0.) ? 1. : -1.;
  }
  while (true) {
    while (not i->queue_stereo_samples(sine, sine)) {
    }
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  i->terminate();
}

int main(int, char **) {
  using namespace sound;
  PortAudioInterface i;

  // test_audio_interface(&i);
  APU apu(&i);
  i.start();
  apu.write(0xff26, 0x80);
  apu.write(0xff25, 0xf3);
  apu.write(0xff24, 0x77);
  apu.write(0xff11, 0x80);
  apu.write(0xff12, 0xf3);
  apu.write(0xff13, 0x83);
  apu.write(0xff14, 0x87);
  loop_at_41mhz([&]() { apu.update_clock(4); });
  i.terminate();
  return 1;
}
