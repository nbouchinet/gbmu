#include "gtest/gtest.h"

#include "src/sound/APU.hpp"
#include "src/sound/portaudio/PortAudioInterface.hpp"

#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <thread>

#define CPU_FREQ (4194304)

void filter(sound::AudioInterface::MonoSamples &samples) {
  constexpr float alpha = (1. / 44'100.) / (1. / 200.);
  static float yk = 0.;
  for (auto &e : samples) {
    yk += alpha * (e - yk);
    e = yk;
  }
}

void test_audio_interface(sound::AudioInterface *i) {
  sound::AudioInterface::MonoSamples sine;
  auto size = sine.size();
  std::srand(123456);
  i->start();
  while (true) {
    for (auto i = 0u; i < size; ++i) {
      sine[i] = (((float)std::rand() / RAND_MAX)* 2. - 1.) ;
    }
    filter(sine);
    while (not i->queue_stereo_samples(sine, sine)) {
    }
  }
  i->terminate();
}

int main(int, char **) {
  using namespace sound;
  PortAudioInterface i;

  test_audio_interface(&i);
  return 1;
}
