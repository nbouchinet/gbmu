#include "gtest/gtest.h"

#include "src/sound/ModulationUnits.hpp"
#include "src/sound/SquareChannel.hpp"
#include "src/sound/VolumeTable.hpp"
#include "src/sound/WaveChannel.hpp"
#include "utils/Operations_utils.hpp"

#include <initializer_list>
#include <iostream>

namespace sound {

// -----------------------------------------------------------------------------
// Utils
// -----------------------------------------------------------------------------

void test_channel_io(SoundChannel *c, Word base_addr,
                     std::initializer_list<Byte> to_test) {
  int i = 0;
  for (Byte b : to_test) {
    Word addr = base_addr + i++;
    c->write(addr, b);
    EXPECT_EQ(c->read(addr), b);
  }
}

// -----------------------------------------------------------------------------
// Sweep
// -----------------------------------------------------------------------------

TEST(SweepUnit, access) {
  Word frequency = 500u;
  SweepUnit sweep(frequency);
  EXPECT_EQ(sweep.trigger_steps(), 0b00100010u);
  ASSERT_EQ(sweep.get_register(), 0x0u);

  sweep.set_register(0b01011110u);

  EXPECT_EQ(sweep.negate(), 1u);
  EXPECT_EQ(sweep.shift(), 6u);
  EXPECT_EQ(sweep.get_register(), 0b01011110u);

  sweep.set_register(0b01111111u);
  EXPECT_EQ(sweep.sweep_period(), 7u);
  EXPECT_EQ(sweep.negate(), 1u);
  EXPECT_EQ(sweep.shift(), 7u);
  EXPECT_EQ(sweep.get_register(), 0b01111111u);

  sweep.set_register(0b00000000u);
  EXPECT_EQ(sweep.sweep_period(), 0u);
  EXPECT_EQ(sweep.negate(), 0u);
  EXPECT_EQ(sweep.shift(), 0u);
  EXPECT_EQ(sweep.get_register(), 0b00000000u);
}

TEST(SweepUnit, trigger) {
  Word frequency = 500u;
  SweepUnit sweep(frequency);
  sweep.set_register(0b01011110u);
  sweep.trigger();
  EXPECT_EQ(sweep.current_period(), sweep.sweep_period());
  EXPECT_EQ(sweep.is_enabled(), true);
}

void test_sweep(bool neg) {
  Word frequency = 500u;
  SweepUnit sweep(frequency);
  sweep.set_register(0b01010010u | (neg << 3));
  sweep.trigger();

  for (auto a = 50; a > 0; --a) {
    Word oldfreq = frequency;
    for (auto i = sweep.sweep_period(); i > 0; --i) ASSERT_TRUE(sweep.call());
    EXPECT_EQ(frequency, oldfreq + (oldfreq >> 2) * -neg);
  }
}

TEST(SweepUnit, step) {
  SCOPED_TRACE("sub sweep failed");
  test_sweep(true);
  SCOPED_TRACE("add sweep failed");
  test_sweep(false);
}

// -----------------------------------------------------------------------------
// LengthUnit
// -----------------------------------------------------------------------------

TEST(LengthUnit, access) {
  LengthUnit length(64);
  EXPECT_EQ(length.trigger_steps(), 0b01010101);
  EXPECT_FALSE(length.is_enabled());
  length.enable();
  EXPECT_TRUE(length.is_enabled());
}

TEST(LengthUnit, trigger) {
  LengthUnit length(64u);
  EXPECT_EQ(length.length(), 0u);
  length.trigger();
  EXPECT_EQ(length.length(), 64u);
}

TEST(LengthUnit, step) {
  LengthUnit length(64u);
  length.trigger();
  length.enable();
  for (auto i = 0; i < 64; ++i) {
    ASSERT_TRUE(length.is_enabled());
    ASSERT_EQ(length.call(), (i != 63));
  }
  EXPECT_EQ(length.length(), 0);
}

// -----------------------------------------------------------------------------
// EnvelopeUnit
// -----------------------------------------------------------------------------

TEST(EnvelopeUnit, access) {
  Byte vol = 0u;
  EnvelopeUnit env(vol);
  EXPECT_EQ(env.trigger_steps(), 0b10000000u);
}

TEST(EnvelopeUnit, trigger) {
  Byte vol = 0u;
  EnvelopeUnit env(vol);
  env.set_period(50);
  env.trigger();
  EXPECT_TRUE(env.is_enabled());
}

void test_envelope(bool neg) {
  const Byte period = 7u;
  Byte vol = 7u;
  EnvelopeUnit env(vol);
  env.set_negate(neg);
  env.set_period(period);
  env.trigger();

  for (auto stop_count = 16; stop_count > 0; --stop_count) {
    Byte oldvol = vol;
    for (auto i = 0; i < period; ++i) {
      ASSERT_TRUE(env.call());
    }
    if (not env.is_enabled()) break;
    EXPECT_EQ(vol, oldvol + ((neg) ? -1 : 1));
  }
  EXPECT_FALSE(env.is_enabled());
  EXPECT_EQ(vol, (neg) ? 0 : 15);
}

TEST(EnvelopeUnit, step) {
  SCOPED_TRACE("neg envelope failed");
  test_envelope(true);
  SCOPED_TRACE("positive envelope failed");
  test_envelope(false);
}

// -----------------------------------------------------------------------------
// SquareChannel
// -----------------------------------------------------------------------------

TEST(SquareChannel, io) {
  SquareChannel chan(true);

  SCOPED_TRACE("SquareChannel read/write null values");
  test_channel_io(
      &chan, 0xff10,
      {0b00000000, 0b00000000, 0b00000000, 0b000000000, 0b00000000});
  SCOPED_TRACE("SquareChannel read/write full values");
  test_channel_io(&chan, 0xff10,
                  {0b01111111, 0b11111111, 0b11111111, 0b11111111, 0b00000111});
  SCOPED_TRACE("SquareChannel read/write random values");
  test_channel_io(&chan, 0xff10,
                  {0b01010011, 0b11010110, 0b11100101, 0b11101100, 0b00000101});
}

void square_chan_test(SquareChannel &chan, Word freq, Byte duty_pattern) {
  chan.write(0xff13, (freq & 0xff));
  chan.write(0xff14, ((freq & 0x0700) >> 8) | 0x80);
  for (auto i = 0; i < 8; ++i) {
    Word timer = (2048 - freq) * 4;
    float ref = test_bit(i, duty_pattern) ? 1.f : -1.f;
    while (timer--) {
      chan.update();
      ASSERT_FLOAT_EQ(chan.get_output(), ref);
    }
  }
  chan.update();
}

TEST(SquareChannel, step) {
  SquareChannel chan(true);

  chan.enable(true);
  chan.write(0xff12, 0xf0);
  SCOPED_TRACE("SquareChannel duty 0");
  chan.write(0xff11, 0x00);
  square_chan_test(chan, 0x400, 0b00000001);
  SCOPED_TRACE("SquareChannel duty 1");
  chan.write(0xff11, 0x40);
  square_chan_test(chan, 0x410, 0b10000001);
  SCOPED_TRACE("SquareChannel duty 2");
  chan.write(0xff11, 0x80);
  square_chan_test(chan, 0x200, 0b10000111);
  SCOPED_TRACE("SquareChannel duty 3");
  chan.write(0xff11, 0xc0);
  square_chan_test(chan, 0x300, 0b01111110);
}

// -----------------------------------------------------------------------------
// WaveChannel
// -----------------------------------------------------------------------------

TEST(WaveChannel, io) {
  VolumeTable table;
  WaveChannel chan(table);

  SCOPED_TRACE("WaveChannel read/write null values");
  test_channel_io(
      &chan, 0xffa,
      {0b00000000, 0b00000000, 0b00000000, 0b000000000, 0b00000000});
  SCOPED_TRACE("WaveChannel read/write full values");
  test_channel_io(&chan, 0xffa,
                  {0b10000000, 0b11111111, 0b01100000, 0b11111111, 0b00000111});
  SCOPED_TRACE("WaveChannel read/write random values");
  test_channel_io(&chan, 0xffa,
                  {0b10000000, 0b11010110, 0b01000000, 0b11101100, 0b00000101});
}

void wave_chan_test(Word freq, VolumeTable &table) {
  constexpr std::pair<Byte, Byte> vcode_and_shift{2, 1};
  WaveChannel chan(table);

  chan.write(0xff1a, 0x80);
  chan.write(0xff1d, (freq & 0xff));
  chan.write(0xff1e, ((freq & 0x0700) >> 8) | 0x80);
  chan.write(0xff1c, (vcode_and_shift.first << 5));
  for (auto i = 0u; i < table.size(); ++i) {
    Word timer = (2048 - freq) * 2;
    float ref = table.get_nibble(i) >> vcode_and_shift.second;
    while (timer--) {
      chan.update();
      ASSERT_FLOAT_EQ(chan.get_raw_volume(), ref);
    }
  }
  chan.update();
}
TEST(WaveChannel, step) {
  {
    SCOPED_TRACE("WaveChannel null test");
    VolumeTable null(
        VolumeTable::Table{{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}});
    wave_chan_test(0x800, null);
  }
  {
    SCOPED_TRACE("WaveChannel full test");
    VolumeTable full(
        VolumeTable::Table{{0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}});
    wave_chan_test(0x800, full);
  }
  {
    SCOPED_TRACE("WaveChannel sine test");
    VolumeTable sine(
        VolumeTable::Table{{0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
                            0xed, 0xcb, 0xa9, 0x87, 0x65, 0x43, 0x21, 0x00}});
    wave_chan_test(0x450, sine);
  }
  {
    SCOPED_TRACE("WaveChannel sawtooth test");
    VolumeTable sawtooth(
        VolumeTable::Table{{0x01, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78,
                            0x89, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0x00}});
    wave_chan_test(0x600, sawtooth);
  }
}

int main(int ac, char *av[]) {
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}

}  // namespace sound

int main(int argc, char *argv[]) { return sound::main(argc, argv); }
