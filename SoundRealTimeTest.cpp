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

void loop_at_41mhz(std::function<void(void)> action) {
  using namespace std::chrono;
  constexpr nanoseconds interval(1000000000LL / CPU_FREQ);
  //auto time = high_resolution_clock::now();
  while (true) {
    action();
    //auto now = high_resolution_clock::now();
    //.std::this_thread::sleep_for(interval - std::chrono::nanoseconds(now - time));
    //time = now;
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
        (static_cast<double>(i) / static_cast<double>(size/4)) * M_PI * 2.);
//    sine[i] = (sin >= 0.) ? .5 : -.5;
  //sine[i] = -0.08f;
    sine[i] = sin;
  }
  while (true) {
    while (not i->queue_stereo_samples(sine, sine)) {
    }
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  i->terminate();
}

void enable_wave(sound::APU &apu) {
  static const std::array<Byte, 16> triangular_wave = {
      {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xED, 0xCB, 0xA9,
       0x87, 0x65, 0x43, 0x21, 0x00}};
  //static const std::array<Byte, 16> saw_tooth_wave = {
  //    {0x01, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9a, 0xab,
  //     0xbc, 0xcd, 0xde, 0xef, 0x00}};
  Word addr = 0xff30;
  for (auto e : triangular_wave) apu.write(addr++, e);
  apu.write(0xff1b, 0x3f);
  apu.write(0xff1c, 0x20);
  apu.write(0xff1d, 0x83);
  apu.write(0xff1e, 0x87);
}

int main(int, char **) {
  using namespace sound;
  PortAudioInterface i;

  //test_audio_interface(&i);
  APU apu(&i);
  i.start();
  apu.write(0xff26, 0x80);
  apu.write(0xff25, 0x3f);
  apu.write(0xff24, 0x22);
  apu.write(0xff11, 0x0f);
  apu.write(0xff12, 0xf3);
  apu.write(0xff13, 0x83);
  apu.write(0xff14, 0x87);
  //enable_wave(apu);
  loop_at_41mhz([&]() { apu.update_clock(4); });
  i.terminate();
  return 1;
}
