#include "src/Core.hpp"
#include "gtest/gtest.h"
#define test_flags(...) test_flags_base((TestCoreFixture::s_flags){__VA_ARGS__})

#include <iostream>
#include <tuple>

#define test_flags(...) test_flags_base((TestCoreFixture::s_flags){__VA_ARGS__})

class Accesser {
 public:
  Core _core;
  Register& getPc(void) { return _core._pc; }
  Register& getSp(void) { return _core._sp; }
  Register& getAf(void) { return _core._af; }
  Register& getBc(void) { return _core._bc; }
  Register& getDe(void) { return _core._de; }
  Register& getHl(void) { return _core._hl; }
};

class TestCoreFixture : public ::testing::Test {
 public:
  struct s_flags {
    int c, z, n, h;
  };
  Accesser _accesser;
  uint8_t reg = 0;

  void test_instr(std::function<void(Core&, Byte&)> instr, uint8_t base,
                  uint8_t expected) {
    instr(_accesser._core, base);
    EXPECT_EQ(base, expected);
  }

  void test_flags_base(struct s_flags f) {
    if (f.c != -1) EXPECT_EQ(_accesser._core.get_flag(Core::Flags::C), f.c);
    if (f.z != -1) EXPECT_EQ(_accesser._core.get_flag(Core::Flags::Z), f.z);
    if (f.n != -1) EXPECT_EQ(_accesser._core.get_flag(Core::Flags::N), f.n);
    if (f.h != -1) EXPECT_EQ(_accesser._core.get_flag(Core::Flags::H), f.h);
  }

  void reset_flags() {
    _accesser._core.set_flag(Core::Flags::C, false);
    _accesser._core.set_flag(Core::Flags::Z, false);
    _accesser._core.set_flag(Core::Flags::N, false);
    _accesser._core.set_flag(Core::Flags::H, false);
  }
};

const std::tuple<Core::Flags, bool>& get_flag_tuple(Core::JumpCondition jc) {
  static std::tuple<Core::Flags, bool> refs[4] = {{Core::Flags::Z, false},
                                                  {Core::Flags::Z, true},
                                                  {Core::Flags::C, false},
                                                  {Core::Flags::C, true}};
  assert(jc != Core::JumpCondition::None);
  return refs[static_cast<int>(jc) - 1];
}

void test_jp(Accesser& access, Core::JumpCondition jc) {
  Word orig_pc = access.getPc().word;
  access._core.instr_jp(jc, 0x4242);
  if (jc != Core::JumpCondition::None) {
    const auto& flag_tuple = get_flag_tuple(jc);
    if (not std::get<1>(flag_tuple))
      EXPECT_EQ(access.getPc().word, 0x4242u);
    else
      EXPECT_EQ(access.getPc().word, orig_pc);
    access._core.set_flag(std::get<0>(flag_tuple), std::get<1>(flag_tuple));
  } else {
    EXPECT_EQ(access.getPc().word, 0x4242u);
    return;
  }
  access._core.instr_jp(jc, 0xaabb);
  EXPECT_EQ(access.getPc().word, 0xaabb);
}

TEST_F(TestCoreFixture, jp_none) {
  SCOPED_TRACE("Jump no conditions fail");
  test_jp(_accesser, Core::JumpCondition::None);
}

TEST_F(TestCoreFixture, jp_nz) {
  SCOPED_TRACE("Jump non-zero fail");
  test_jp(_accesser, Core::JumpCondition::NonZero);
}

TEST_F(TestCoreFixture, jp_z) {
  SCOPED_TRACE("Jump zero fail");
  test_jp(_accesser, Core::JumpCondition::Zero);
}

TEST_F(TestCoreFixture, jp_nc) {
  SCOPED_TRACE("Jump no-carry fail");
  test_jp(_accesser, Core::JumpCondition::NonCarry);
}

TEST_F(TestCoreFixture, jp_c) {
  SCOPED_TRACE("Jump carry fail");
  test_jp(_accesser, Core::JumpCondition::Carry);
}

void test_jr(Accesser& access, Core::JumpCondition jc) {
  Word orig_pc = access.getPc().word;
  access._core.instr_jr(jc, 1);
  if (jc != Core::JumpCondition::None) {
    const auto& flag_tuple = get_flag_tuple(jc);
    if (not std::get<1>(flag_tuple))
      EXPECT_EQ(access.getPc().word, orig_pc + 1);
    else
      EXPECT_EQ(access.getPc().word, orig_pc);
    access._core.set_flag(std::get<0>(flag_tuple), std::get<1>(flag_tuple));
  } else {
    EXPECT_EQ(access.getPc().word, orig_pc + 1);
  }
  access.getPc().word = orig_pc;
  access._core.instr_jr(jc, 0x42);
  EXPECT_EQ(access.getPc().word, orig_pc + 0x42);
  access.getPc().word = orig_pc;
  access._core.instr_jr(jc, 0x85);
  EXPECT_EQ(access.getPc().word, orig_pc - 123);
}

TEST_F(TestCoreFixture, jr_none) {
  SCOPED_TRACE("Relative jump no conditions fail");
  test_jr(_accesser, Core::JumpCondition::None);
}

TEST_F(TestCoreFixture, jr_nz) {
  SCOPED_TRACE("Relative jump non-zero fail");
  test_jr(_accesser, Core::JumpCondition::NonZero);
}

TEST_F(TestCoreFixture, jr_zero) {
  SCOPED_TRACE("Relative jump zero fail");
  test_jr(_accesser, Core::JumpCondition::Zero);
}

TEST_F(TestCoreFixture, jr_nc) {
  SCOPED_TRACE("Relative jump no-carry fail");
  test_jr(_accesser, Core::JumpCondition::NonCarry);
}

TEST_F(TestCoreFixture, jr_c) {
  SCOPED_TRACE("Relative jump carry fail");
  test_jr(_accesser, Core::JumpCondition::Carry);
}

TEST_F(TestCoreFixture, writeMemory) {
  Register& spSaved = _accesser.getSp();
  write<Byte>(spSaved.word, 55);
  EXPECT_EQ(tmp_memory[spSaved.word], 55);
}

TEST_F(TestCoreFixture, daa) {
  reset_flags();
  _accesser.getAf().high = 0xC;
  _accesser._core.instr_daa();
  EXPECT_EQ(_accesser.getAf().high, 0x12);

  reset_flags();
  _accesser.getAf().high = 0xF4;
  _accesser._core.instr_daa();
  test_flags(.c = 1);
  EXPECT_EQ(_accesser.getAf().high, 0x54);

  reset_flags();
  _accesser.getAf().high = 0xE0;
  _accesser._core.instr_daa();
  EXPECT_EQ(_accesser.getAf().high, 0x40);
  test_flags(.c = 1);

  reset_flags();
  _accesser._core.set_flag(Core::Flags::H, true);
  _accesser.getAf().high = 0x98;
  _accesser._core.instr_daa();
  EXPECT_EQ(_accesser.getAf().high, 0x9E);

  reset_flags();
  _accesser._core.set_flag(Core::Flags::N, true);
  _accesser.getAf().high = 0xF4;
  _accesser._core.instr_daa();
  EXPECT_EQ(_accesser.getAf().high, 0x94);

  reset_flags();
  _accesser._core.set_flag(Core::Flags::N, true);
  _accesser.getAf().high = 0xF4;
  _accesser._core.instr_daa();
  EXPECT_EQ(_accesser.getAf().high, 0x94);
}

TEST_F(TestCoreFixture, push) {
  Register& spSaved = _accesser.getSp();
  Word addrSaved = spSaved.word;
  Word value = 0x4242;

  _accesser._core.instr_push(value);
  EXPECT_EQ(tmp_memory[addrSaved - 1], ((value & 0xff00) >> 8));
  EXPECT_EQ(tmp_memory[addrSaved - 2], (value & 0x00ff));
}

void test_call(Accesser& access, Core::JumpCondition jc) {
  Word orig_pc = access.getPc().word;
  Word orig_sp = access.getSp().word;

  access._core.instr_call(jc, 0x4242);
  if (jc != Core::JumpCondition::None) {
    const auto& flag_tuple = get_flag_tuple(jc);
    if (not std::get<1>(flag_tuple))
      EXPECT_EQ(access.getPc().word, 0x4242);
    else
      EXPECT_EQ(access.getPc().word, orig_pc);
    access._core.set_flag(std::get<0>(flag_tuple), std::get<1>(flag_tuple));
  } else {
    EXPECT_EQ(access.getPc().word, 0x4242);
    EXPECT_EQ(read<Byte>(orig_sp - 1), (((orig_pc + 3) & 0xff00) >> 8));
    EXPECT_EQ(read<Byte>(orig_sp - 2), ((orig_pc + 3) & 0x00ff));
    return;
  }
  access._core.instr_call(jc, 0xaabb);
  EXPECT_EQ(access.getPc().word, 0xaabb);
  EXPECT_EQ(read<Byte>(orig_sp - 1), (((orig_pc + 3) & 0xff00) >> 8));
  EXPECT_EQ(read<Byte>(orig_sp - 2), ((orig_pc + 3) & 0x00ff));
}

TEST_F(TestCoreFixture, call_none) {
  SCOPED_TRACE("Call jump no conditions fail");
  test_call(_accesser, Core::JumpCondition::None);
}

TEST_F(TestCoreFixture, call_nz) {
  SCOPED_TRACE("Call jump non-zero fail");
  test_call(_accesser, Core::JumpCondition::NonZero);
}

TEST_F(TestCoreFixture, call_z) {
  SCOPED_TRACE("Call jump zero fail");
  test_call(_accesser, Core::JumpCondition::Zero);
}

TEST_F(TestCoreFixture, call_nc) {
  SCOPED_TRACE("Call jump non-carry fail");
  test_call(_accesser, Core::JumpCondition::NonCarry);
}

TEST_F(TestCoreFixture, call_c) {
  SCOPED_TRACE("Call jump carry fail");
  test_call(_accesser, Core::JumpCondition::Carry);
}

TEST_F(TestCoreFixture, readMemory) {
  Register& spSaved = _accesser.getSp();
  write<Byte>(spSaved.word, 55);
  EXPECT_EQ(tmp_memory[spSaved.word], 55);
  Byte ret = read<Byte>(spSaved.word);
  EXPECT_EQ(ret, 55);
}

TEST_F(TestCoreFixture, pop) {
  Register& spSaved = _accesser.getSp();
  Word addrSaved = spSaved.word;
  Word value = 0x4242;
  Word ret;

  _accesser._core.instr_push(value);
  EXPECT_EQ(tmp_memory[addrSaved - 1], ((value & 0xff00) >> 8));
  EXPECT_EQ(tmp_memory[addrSaved - 2], (value & 0x00ff));
  _accesser._core.instr_pop(ret);
  EXPECT_EQ(ret, value);
}

void test_ret(Accesser& access, Core::JumpCondition jc) {
  Word orig_pc = access.getPc().word;
  Word orig_sp = access.getSp().word;

  access._core.instr_push(0x4242);
  access._core.instr_ret(jc);
  if (jc != Core::JumpCondition::None) {
    const auto& flag_tuple = get_flag_tuple(jc);
    if (not std::get<1>(flag_tuple))
      EXPECT_EQ(access.getPc().word, 0x4242);
    else
      EXPECT_EQ(access.getPc().word, orig_pc);
    access._core.set_flag(std::get<0>(flag_tuple), std::get<1>(flag_tuple));
  } else {
    EXPECT_EQ(access.getPc().word, 0x4242);
    EXPECT_EQ(access.getSp().word, orig_sp);
    return;
  }
  access._core.instr_push(0xaabb);
  access._core.instr_ret(jc);
  EXPECT_EQ(access.getPc().word, 0xaabb);
}

TEST_F(TestCoreFixture, ret_none) {
  SCOPED_TRACE("ret no condition fail");
  test_call(_accesser, Core::JumpCondition::None);
}

TEST_F(TestCoreFixture, ret_nz) {
  SCOPED_TRACE("ret non-zero fail");
  test_call(_accesser, Core::JumpCondition::NonZero);
}

TEST_F(TestCoreFixture, ret_z) {
  SCOPED_TRACE("ret zero fail");
  test_call(_accesser, Core::JumpCondition::Zero);
}

TEST_F(TestCoreFixture, ret_nc) {
  SCOPED_TRACE("ret non-carry fail");
  test_call(_accesser, Core::JumpCondition::NonCarry);
}

TEST_F(TestCoreFixture, ret_c) {
  SCOPED_TRACE("ret carry fail");
  test_call(_accesser, Core::JumpCondition::Carry);
}

#define TEST_ADD(T, loop_begin, nibble_mask)                            \
  {                                                                     \
    constexpr T max = std::numeric_limits<T>::max();                    \
    for (T a = loop_begin; a < max; ++a) {                              \
      for (T b = loop_begin; b < max; ++b) {                            \
        T a_bis = a;                                                    \
        _accesser._core.instr_add(a_bis, b);                            \
        unsigned int res = a + b;                                       \
        unsigned int half_res = (a & nibble_mask) + (b & nibble_mask);  \
        EXPECT_EQ(_accesser._core.get_flag(Core::Flags::C), res > max); \
        EXPECT_EQ(_accesser._core.get_flag(Core::Flags::H),             \
                  half_res > (max & nibble_mask));                      \
        EXPECT_FALSE(_accesser._core.get_flag(Core::Flags::N));         \
        EXPECT_EQ(_accesser._core.get_flag(Core::Flags::Z),             \
                  static_cast<T>(res) == 0);                            \
        EXPECT_EQ(static_cast<T>(a_bis), static_cast<T>(res));          \
      }                                                                 \
    }

template <typename T>
void test_add(Accesser access, T loop_begin, T nibble_mask) {
  constexpr T max = std::numeric_limits<T>::max();
  for (T a = loop_begin; a < max; ++a) {
    for (T b = loop_begin; b < max; ++b) {
      T a_save = a;
      access._core.instr_add(a_save, b);
      unsigned int res = a + b;
      unsigned int half_res = (a & nibble_mask) + (b & nibble_mask);
      EXPECT_EQ(access._core.get_flag(Core::Flags::C), res > max);
      EXPECT_EQ(access._core.get_flag(Core::Flags::H),
                half_res > (max & nibble_mask));
      EXPECT_FALSE(access._core.get_flag(Core::Flags::N));
      EXPECT_EQ(access._core.get_flag(Core::Flags::Z),
                static_cast<T>(res) == 0);
      EXPECT_EQ(static_cast<T>(a_save), static_cast<T>(res));
    }
  }
}

TEST_F(TestCoreFixture, add) {
  SCOPED_TRACE("add tests");
  test_add(_accesser, static_cast<Byte>(0x00u), static_cast<Byte>(0x0fu));
  test_add(_accesser, static_cast<Word>(0xff00u), static_cast<Word>(0x0fffu));
}

TEST_F(TestCoreFixture, adc) {
  constexpr Byte max = std::numeric_limits<Byte>::max();
  for (Byte a = 0x00; a < max; ++a) {
    for (Byte b = 0x00; b < max; ++b) {
      Byte a_save = a;
      bool c = _accesser._core.get_flag(Core::Flags::C);
      _accesser._core.instr_adc(a_save, b);
      unsigned int res = a + b + c;
      unsigned int half_res = (a & 0xfu) + (b & 0xfu) + c;
      test_flags(.c = res > max, .h = half_res > (max & 0xfu), .n = false,
                 .z = static_cast<Byte>(res) == 0);
      EXPECT_EQ(static_cast<Byte>(a_save), static_cast<Byte>(res));
    }
  }
}

TEST_F(TestCoreFixture, sub) {
  constexpr Byte max = std::numeric_limits<Byte>::max();
  constexpr Byte min = std::numeric_limits<Byte>::min();
  for (Byte a = 0u; a < max; ++a) {
    for (Byte b = 0u; b < max; ++b) {
      Byte a_save = a;
      _accesser._core.instr_sub(a_save, b);
      int res = a - b;
      int half_res = (a & 0xf0) - (b & 0xf0);
      test_flags(.c = res < min, .h = half_res < (min & 0xf0), .n = true,
                 .z = static_cast<Byte>(res) == 0);
      EXPECT_EQ(static_cast<Byte>(a_save), static_cast<Byte>(res));
    }
  }
}

TEST_F(TestCoreFixture, sbc) {
  constexpr Byte max = std::numeric_limits<Byte>::max();
  constexpr Byte min = std::numeric_limits<Byte>::min();
  for (Byte a = 0u; a < max; ++a) {
    for (Byte b = 0u; b < max; ++b) {
      Byte a_save = a;
      bool c = _accesser._core.get_flag(Core::Flags::C);

      _accesser._core.instr_sbc(a_save, b);
      int res = (a - b) - c;
      int half_res = (a & 0xf0) - (b & 0xf0);
      test_flags(.c = res < min, .h = half_res < (min & 0xf0), .n = true,
                 .z = static_cast<Byte>(res) == 0);
      EXPECT_EQ(static_cast<Byte>(a_save), static_cast<Byte>(res));
    }
  }
}

#define TEST_OPERAND(OPNAME, OP, _C, _H, _N)                   \
  constexpr Byte max = std::numeric_limits<Byte>::max();       \
  for (Byte a = 0u; a < max; ++a) {                            \
    for (Byte b = 0u; b < max; ++b) {                          \
      Byte a_save = a;                                         \
      _accesser._core.OPNAME(a_save, b);                       \
      Byte res = a OP b;                                       \
      EXPECT_EQ(_accesser._core.get_flag(Core::Flags::C), _C); \
      EXPECT_EQ(_accesser._core.get_flag(Core::Flags::H), _H); \
      EXPECT_EQ(_accesser._core.get_flag(Core::Flags::N), _N); \
      EXPECT_EQ(_accesser._core.get_flag(Core::Flags::Z),      \
                static_cast<Byte>(res) == 0);                  \
      EXPECT_EQ(static_cast<Byte>(a_save), res);               \
    }                                                          \
  }

TEST_F(TestCoreFixture, and) {
  SCOPED_TRACE("and tests");
  TEST_OPERAND(instr_and, &, false, true, false);
}

TEST_F(TestCoreFixture, or) {
  SCOPED_TRACE("or tests");
  TEST_OPERAND(instr_or, |, false, false, false);
}

TEST_F(TestCoreFixture, xor) {
  SCOPED_TRACE("xor tests");
  TEST_OPERAND(instr_xor, ^, false, false, false);
}

TEST_F(TestCoreFixture, inc) {
  constexpr Byte max = std::numeric_limits<Byte>::max();
  for (Byte a = 0u; a < max;) {
    Byte tmp = a;
    _accesser._core.instr_inc(a);
    EXPECT_FALSE(_accesser._core.get_flag(Core::Flags::N));
    EXPECT_EQ(_accesser._core.get_flag(Core::Flags::Z), a == 0);
    EXPECT_EQ(_accesser._core.get_flag(Core::Flags::H), (tmp & 0xfu) == 0xfu);
    ASSERT_EQ(a, tmp + 1);
  }
}

TEST_F(TestCoreFixture, dec) {
  constexpr Byte max = std::numeric_limits<Byte>::max();
  for (Byte a = max; a > 0;) {
    Byte tmp = a;
    _accesser._core.instr_dec(a);
    EXPECT_TRUE(_accesser._core.get_flag(Core::Flags::N));
    EXPECT_EQ(_accesser._core.get_flag(Core::Flags::Z), a == 0);
    EXPECT_EQ(_accesser._core.get_flag(Core::Flags::H), (tmp & 0xf0u) == 0xfu);
    ASSERT_EQ(a, tmp - 1);
  }
}

TEST_F(TestCoreFixture, rlc) {
  SCOPED_TRACE("rlc instruction failure");

  test_instr(&Core::instr_rlc, 0xFF, 0xFF);
  test_flags(.c = 1);

  test_instr(&Core::instr_rlc, 0x85, 0xB);
  test_flags(.c = 1);

  test_instr(&Core::instr_rlc, 0x0, 0x0);
  test_flags(.z = 1);

  test_instr(&Core::instr_rlc, 0x7F, 0xFE);
  test_flags();
}

TEST_F(TestCoreFixture, rl) {
  SCOPED_TRACE("rl instruction failure");

  test_instr(&Core::instr_rl, 0xFF, 0xFE);
  test_flags(.c = 1);

  test_instr(&Core::instr_rl, 0x85, 0xB);
  test_flags(.c = 1);

  test_instr(&Core::instr_rl, 0x0, 0x1);
  test_flags();

  test_instr(&Core::instr_rl, 0x7F, 0xFE);
}

TEST_F(TestCoreFixture, rrc) {
  SCOPED_TRACE("rrc instruction failure");

  test_instr(&Core::instr_rrc, 0x41, 0xA0);
  test_flags(.c = 1);

  test_instr(&Core::instr_rrc, 0x85, 0xC2);
  test_flags(.c = 1);

  test_instr(&Core::instr_rrc, 0x0, 0x0);
  test_flags(.z = 1);

  test_instr(&Core::instr_rrc, 0x7F, 0xBF);
  test_flags(.c = 1);
}

TEST_F(TestCoreFixture, rr) {
  SCOPED_TRACE("rr instruction failure");

  test_instr(&Core::instr_rr, 0x41, 0x20);
  test_flags(.c = 1);

  test_instr(&Core::instr_rr, 0x85, 0xC2);
  test_flags(.c = 1);

  test_instr(&Core::instr_rr, 0x0, 0x80);
  test_flags();

  test_instr(&Core::instr_rr, 0x7F, 0x3F);
  test_flags(.c = 1);
}

TEST_F(TestCoreFixture, program_1) {
  reg = 0x00;
  _accesser.getBc().high = 0x00;
  std::vector<Byte> opcodes{0x3E, 0x42, 0x06, 0xF0, 0xAF, 0x78, 0xAF};
  int i = 0;

  auto it = opcodes.begin();

  _accesser._core.execute(it);  // ld a, 0x42
  _accesser._core.execute(it);  // ld b, 0xF0

  while (it != opcodes.end()) {
    _accesser._core.execute(it);
    switch (i) {
      case 0:
        EXPECT_EQ(_accesser.getAf().high, 0);
        break;
      case 1:
        EXPECT_EQ(_accesser.getAf().high, 0xF0);
        break;
      case 2:
        EXPECT_EQ(_accesser.getAf().high, 0);
        break;
      default:
        break;
    }
    i++;
  }
}

// TEST_F(TestCoreFixture, program_2)
// {
// 	reg = 0x42;
// 	_accesser.getBc().high = 0x00;
// 	std::vector<Byte> opcodes{ 0x06, 0x42, 0xCB, 0x00 };
//
// 	auto it = opcodes.begin();
//
// 	while (it != opcodes.end()) {
// 		_accesser._core.execute(it);
// 	}
// 	EXPECT_EQ(_accesser.getBc().high, 0x21);
// }

TEST_F(TestCoreFixture, cpl) {
  for (int i = 0x0; i < 0xFF; i++) {
    _accesser.getAf().high = i;
    _accesser._core.instr_cpl();
    test_flags(.n = 1, .h = 1);
    EXPECT_EQ(_accesser.getAf().high, static_cast<uint8_t>(~i));
    _accesser._core.set_flag(Core::Flags::N, false);
    _accesser._core.set_flag(Core::Flags::H, false);
  }
}

TEST_F(TestCoreFixture, ccf) {
  _accesser._core.set_flag(Core::Flags::N, true);
  _accesser._core.set_flag(Core::Flags::H, true);
  _accesser._core.set_flag(Core::Flags::C, true);
  _accesser._core.instr_ccf();
  test_flags(.z = -1);
  _accesser._core.instr_ccf();
  test_flags(.c = 1, .z = -1);
}

TEST_F(TestCoreFixture, scf) {
  _accesser._core.set_flag(Core::Flags::N, true);
  _accesser._core.set_flag(Core::Flags::H, true);
  _accesser._core.set_flag(Core::Flags::C, false);
  _accesser._core.instr_ccf();
  test_flags(.c = 1, .z = -1);
}

TEST_F(TestCoreFixture, sla) {
  for (Byte i = 0x1; i < 0xFF; i++) {
    _accesser.getBc().low = i;
    Byte swap = i;
    _accesser._core.instr_sla(_accesser.getBc().low);
    EXPECT_EQ(_accesser._core.get_flag(Core::Flags::C), test_bit(7, swap));
    test_flags(.c = -1, .z = -1);
    EXPECT_EQ(_accesser.getBc().low, static_cast<Byte>(i << 1));
    EXPECT_EQ(_accesser._core.get_flag(Core::Flags::Z), (i == 0x80));
  }
}

TEST_F(TestCoreFixture, sra) {
  for (Byte i = 0x1; i < 0xFF; i++) {
    _accesser.getBc().high = i;
    Byte swap = i;
    _accesser._core.instr_sra(_accesser.getBc().high);
    EXPECT_EQ(_accesser._core.get_flag(Core::Flags::C), test_bit(0, swap));
    test_flags(.c = -1, .z = -1);
    EXPECT_EQ(_accesser.getBc().high, static_cast<Byte>(i >> 1));
    EXPECT_EQ(_accesser._core.get_flag(Core::Flags::Z), (i == 0x01));
  }
}

TEST_F(TestCoreFixture, srl) {
  for (Byte i = 0x1; i < 0xFF; i++) {
    _accesser.getBc().high = i;
    Byte swap = i;
    _accesser._core.instr_srl(_accesser.getBc().high);
    EXPECT_EQ(_accesser._core.get_flag(Core::Flags::C), test_bit(0, swap));
    test_flags(.c = -1, .z = -1);
    EXPECT_EQ(_accesser.getBc().high, static_cast<Byte>(i >> 1));
    EXPECT_EQ(_accesser._core.get_flag(Core::Flags::Z), (i == 0x01));
  }
}

int main(int ac, char* av[]) {
  ::testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
