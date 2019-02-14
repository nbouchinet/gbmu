#include "src/cpu/Core.hpp"
#include "gtest/gtest.h"
#include "src/Gameboy.hpp"
#define test_flags(...) test_flags_base((TestCoreFixture::s_flags){__VA_ARGS__})

#include <tuple>

#define test_flags(...) test_flags_base((TestCoreFixture::s_flags){__VA_ARGS__})

class Accessor {
 public:
  ComponentsContainer container;
  Core core;
  Register& getPc(void) { return core._pc; }
  Register& getSp(void) { return core._sp; }
  Register& getAf(void) { return core._af; }
  Register& getBc(void) { return core._bc; }
  Register& getDe(void) { return core._de; }
  Register& getHl(void) { return core._hl; }

  Accessor() : container("tools/Tetris.gb"), core(container) {}
};

class TestCoreFixture : public ::testing::Test {
 public:
  struct s_flags {
    int c, z, n, h;
  };
  Accessor accessor;
  uint8_t reg = 0;

  void test_instr(std::function<void(Core&, Byte&)> instr, uint8_t base,
                  uint8_t expected) {
    instr(accessor.core, base);
    EXPECT_EQ(base, expected);
  }

  void test_flags_base(struct s_flags f) {
    if (f.c != -1) EXPECT_EQ(accessor.core.get_flag(Core::Flags::C), f.c);
    if (f.z != -1) EXPECT_EQ(accessor.core.get_flag(Core::Flags::Z), f.z);
    if (f.n != -1) EXPECT_EQ(accessor.core.get_flag(Core::Flags::N), f.n);
    if (f.h != -1) EXPECT_EQ(accessor.core.get_flag(Core::Flags::H), f.h);
  }

  void reset_flags() {
    accessor.core.set_flag(Core::Flags::C, false);
    accessor.core.set_flag(Core::Flags::Z, false);
    accessor.core.set_flag(Core::Flags::N, false);
    accessor.core.set_flag(Core::Flags::H, false);
  }

  void SetUp() override { reset_flags(); }
};

using Tuple = std::tuple<Core::Flags, bool>;
const Tuple& get_flag_tuple(Core::JumpCondition jc) {
  static Tuple refs[4] = {Tuple{Core::Flags::Z, false},
                          Tuple{Core::Flags::Z, true},
                          Tuple{Core::Flags::C, false},
                          Tuple{Core::Flags::C, true}};
  assert(jc != Core::JumpCondition::None);
  return refs[static_cast<int>(jc) - 1];
}

void test_jp(Accessor& access, Core::JumpCondition jc) {
  Word orig_pc = access.getPc().word;
  access.core.instr_jp(jc, 0x4242);
  if (jc != Core::JumpCondition::None) {
    const auto& flag_tuple = get_flag_tuple(jc);
    if (not std::get<1>(flag_tuple))
      EXPECT_EQ(access.getPc().word, 0x4242u);
    else
      EXPECT_EQ(access.getPc().word, orig_pc);
    access.core.set_flag(std::get<0>(flag_tuple), std::get<1>(flag_tuple));
  } else {
    EXPECT_EQ(access.getPc().word, 0x4242u);
    return;
  }
  access.core.instr_jp(jc, 0xaabb);
  EXPECT_EQ(access.getPc().word, 0xaabb);
}

TEST_F(TestCoreFixture, jp_none) {
  SCOPED_TRACE("Jump no conditions fail");
  test_jp(accessor, Core::JumpCondition::None);
}

TEST_F(TestCoreFixture, jp_nz) {
  SCOPED_TRACE("Jump non-zero fail");
  test_jp(accessor, Core::JumpCondition::NonZero);
}

TEST_F(TestCoreFixture, jp_z) {
  SCOPED_TRACE("Jump zero fail");
  test_jp(accessor, Core::JumpCondition::Zero);
}

TEST_F(TestCoreFixture, jp_nc) {
  SCOPED_TRACE("Jump no-carry fail");
  test_jp(accessor, Core::JumpCondition::NonCarry);
}

TEST_F(TestCoreFixture, jp_c) {
  SCOPED_TRACE("Jump carry fail");
  test_jp(accessor, Core::JumpCondition::Carry);
}

void test_jr(Accessor& access, Core::JumpCondition jc) {
  Word orig_pc = access.getPc().word;
  access.core.instr_jr(jc, 1);
  if (jc != Core::JumpCondition::None) {
    const auto& flag_tuple = get_flag_tuple(jc);
    if (not std::get<1>(flag_tuple))
      EXPECT_EQ(access.getPc().word, orig_pc + 1);
    else
      EXPECT_EQ(access.getPc().word, orig_pc);
    access.core.set_flag(std::get<0>(flag_tuple), std::get<1>(flag_tuple));
  } else {
    EXPECT_EQ(access.getPc().word, orig_pc + 1);
  }
  access.getPc().word = orig_pc;
  access.core.instr_jr(jc, 0x42);
  EXPECT_EQ(access.getPc().word, orig_pc + 0x42);
  access.getPc().word = orig_pc;
  access.core.instr_jr(jc, 0x85);
  EXPECT_EQ(access.getPc().word, orig_pc - 123);
}

TEST_F(TestCoreFixture, jr_none) {
  SCOPED_TRACE("Relative jump no conditions fail");
  test_jr(accessor, Core::JumpCondition::None);
}

TEST_F(TestCoreFixture, jr_nz) {
  SCOPED_TRACE("Relative jump non-zero fail");
  test_jr(accessor, Core::JumpCondition::NonZero);
}

TEST_F(TestCoreFixture, jr_zero) {
  SCOPED_TRACE("Relative jump zero fail");
  test_jr(accessor, Core::JumpCondition::Zero);
}

TEST_F(TestCoreFixture, jr_nc) {
  SCOPED_TRACE("Relative jump no-carry fail");
  test_jr(accessor, Core::JumpCondition::NonCarry);
}

TEST_F(TestCoreFixture, jr_c) {
  SCOPED_TRACE("Relative jump carry fail");
  test_jr(accessor, Core::JumpCondition::Carry);
}

TEST_F(TestCoreFixture, daa) {
  reset_flags();
  accessor.getAf().high = 0xC;
  accessor.core.instr_daa();
  EXPECT_EQ(accessor.getAf().high, 0x12);

  reset_flags();
  accessor.getAf().high = 0xF4;
  accessor.core.instr_daa();
  test_flags(.c = 1);
  EXPECT_EQ(accessor.getAf().high, 0x54);

  reset_flags();
  accessor.getAf().high = 0xE0;
  accessor.core.instr_daa();
  EXPECT_EQ(accessor.getAf().high, 0x40);
  test_flags(.c = 1);

  reset_flags();
  accessor.core.set_flag(Core::Flags::H, true);
  accessor.getAf().high = 0x98;
  accessor.core.instr_daa();
  EXPECT_EQ(accessor.getAf().high, 0x9E);

  reset_flags();
  accessor.core.set_flag(Core::Flags::N, true);
  accessor.getAf().high = 0xF4;
  accessor.core.instr_daa();
  EXPECT_EQ(accessor.getAf().high, 0x94);

  reset_flags();
  accessor.core.set_flag(Core::Flags::N, true);
  accessor.getAf().high = 0xF4;
  accessor.core.instr_daa();
  EXPECT_EQ(accessor.getAf().high, 0x94);
}

TEST_F(TestCoreFixture, push) {
  Register& spSaved = accessor.getSp();
  Word addrSaved = spSaved.word;
  Word value = 0x4242;

  accessor.core.instr_push(value);
  Byte b1 = accessor.core.read(addrSaved - 1);
  Byte b2 = accessor.core.read(addrSaved - 2);
  EXPECT_EQ(b1, ((value & 0xff00) >> 8));
  EXPECT_EQ(b2, (value & 0x00ff));
}

void test_call(Accessor& access, Core::JumpCondition jc) {
  Word orig_pc = access.getPc().word;
  Word orig_sp = access.getSp().word;

  access.core.instr_call(jc, 0x4242);
  if (jc != Core::JumpCondition::None) {
    const auto& flag_tuple = get_flag_tuple(jc);
    if (not std::get<1>(flag_tuple))
      EXPECT_EQ(access.getPc().word, 0x4242);
    else
      EXPECT_EQ(access.getPc().word, orig_pc);
    access.core.set_flag(std::get<0>(flag_tuple), std::get<1>(flag_tuple));
  } else {
    EXPECT_EQ(access.getPc().word, 0x4242);
    Byte b1 = access.core.read(orig_sp - 1);
    Byte b2 = access.core.read(orig_sp - 2);
    EXPECT_EQ(b1, (((orig_pc + 3) & 0xff00) >> 8));
    EXPECT_EQ(b2, ((orig_pc + 3) & 0x00ff));
    return;
  }
  access.core.instr_call(jc, 0xaabb);
  EXPECT_EQ(access.getPc().word, 0xaabb);
  Byte b1 = access.core.read(orig_sp - 1);
  Byte b2 = access.core.read(orig_sp - 2);
  EXPECT_EQ(b1, (((orig_pc + 3) & 0xff00) >> 8));
  EXPECT_EQ(b2, ((orig_pc + 3) & 0x00ff));
}

TEST_F(TestCoreFixture, call_none) {
  SCOPED_TRACE("Call jump no conditions fail");
  test_call(accessor, Core::JumpCondition::None);
}

TEST_F(TestCoreFixture, call_nz) {
  SCOPED_TRACE("Call jump non-zero fail");
  test_call(accessor, Core::JumpCondition::NonZero);
}

TEST_F(TestCoreFixture, call_z) {
  SCOPED_TRACE("Call jump zero fail");
  test_call(accessor, Core::JumpCondition::Zero);
}

TEST_F(TestCoreFixture, call_nc) {
  SCOPED_TRACE("Call jump non-carry fail");
  test_call(accessor, Core::JumpCondition::NonCarry);
}

TEST_F(TestCoreFixture, call_c) {
  SCOPED_TRACE("Call jump carry fail");
  test_call(accessor, Core::JumpCondition::Carry);
}

TEST_F(TestCoreFixture, pop) {
  Register& spSaved = accessor.getSp();
  Word addrSaved = spSaved.word;
  Word value = 0x4242;
  Word ret;

  accessor.core.instr_push(value);
  Byte b1 = accessor.core.read(addrSaved - 1);
  Byte b2 = accessor.core.read(addrSaved - 2);
  EXPECT_EQ(b1, ((value & 0xff00) >> 8));
  EXPECT_EQ(b2, (value & 0x00ff));
  accessor.core.instr_pop(ret);
  EXPECT_EQ(ret, value);
}

void test_ret(Accessor& access, Core::JumpCondition jc) {
  Word orig_pc = access.getPc().word;
  Word orig_sp = access.getSp().word;

  access.core.instr_push(0x4242);
  access.core.instr_ret(jc);
  if (jc != Core::JumpCondition::None) {
    const auto& flag_tuple = get_flag_tuple(jc);
    if (not std::get<1>(flag_tuple))
      EXPECT_EQ(access.getPc().word, 0x4242);
    else
      EXPECT_EQ(access.getPc().word, orig_pc);
    access.core.set_flag(std::get<0>(flag_tuple), std::get<1>(flag_tuple));
  } else {
    EXPECT_EQ(access.getPc().word, 0x4242);
    EXPECT_EQ(access.getSp().word, orig_sp);
    return;
  }
  access.core.instr_push(0xaabb);
  access.core.instr_ret(jc);
  EXPECT_EQ(access.getPc().word, 0xaabb);
}

TEST_F(TestCoreFixture, ret_none) {
  SCOPED_TRACE("ret no condition fail");
  test_call(accessor, Core::JumpCondition::None);
}

TEST_F(TestCoreFixture, ret_nz) {
  SCOPED_TRACE("ret non-zero fail");
  test_call(accessor, Core::JumpCondition::NonZero);
}

TEST_F(TestCoreFixture, ret_z) {
  SCOPED_TRACE("ret zero fail");
  test_call(accessor, Core::JumpCondition::Zero);
}

TEST_F(TestCoreFixture, ret_nc) {
  SCOPED_TRACE("ret non-carry fail");
  test_call(accessor, Core::JumpCondition::NonCarry);
}

TEST_F(TestCoreFixture, ret_c) {
  SCOPED_TRACE("ret carry fail");
  test_call(accessor, Core::JumpCondition::Carry);
}

template <typename T>
void test_add(Accessor& access, T loop_begin, T nibble_mask) {
  constexpr T max = std::numeric_limits<T>::max();
  for (T a = loop_begin; a < max; ++a) {
    for (T b = loop_begin; b < max; ++b) {
      T a_save = a;
      access.core.instr_add(a_save, b);
      unsigned int res = a + b;
      unsigned int half_res = (a & nibble_mask) + (b & nibble_mask);
      EXPECT_EQ(access.core.get_flag(Core::Flags::C), res > max);
      EXPECT_EQ(access.core.get_flag(Core::Flags::H),
                half_res > (max & nibble_mask));
      EXPECT_FALSE(access.core.get_flag(Core::Flags::N));
      EXPECT_EQ(access.core.get_flag(Core::Flags::Z), static_cast<T>(res) == 0);
      EXPECT_EQ(static_cast<T>(a_save), static_cast<T>(res));
    }
  }
}

TEST_F(TestCoreFixture, add) {
  SCOPED_TRACE("add tests");
  test_add(accessor, static_cast<Byte>(0x00u), static_cast<Byte>(0x0fu));
  test_add(accessor, static_cast<Word>(0xff00u), static_cast<Word>(0x0fffu));
}

TEST_F(TestCoreFixture, adc) {
  constexpr Byte max = std::numeric_limits<Byte>::max();
  for (Byte a = 0x00; a < max; ++a) {
    for (Byte b = 0x00; b < max; ++b) {
      Byte a_save = a;
      bool c = accessor.core.get_flag(Core::Flags::C);
      accessor.core.instr_adc(a_save, b);
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
      accessor.core.instr_sub(a_save, b);
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
      bool c = accessor.core.get_flag(Core::Flags::C);

      accessor.core.instr_sbc(a_save, b);
      int res = (a - b) - c;
      int half_res = (a & 0xf0) - (b & 0xf0);
      test_flags(.c = res < min, .h = half_res < (min & 0xf0), .n = true,
                 .z = static_cast<Byte>(res) == 0);
      EXPECT_EQ(static_cast<Byte>(a_save), static_cast<Byte>(res));
    }
  }
}

#define TEST_OPERAND(OPNAME, OP, _C, _H, _N)                 \
  constexpr Byte max = std::numeric_limits<Byte>::max();     \
  for (Byte a = 0u; a < max; ++a) {                          \
    for (Byte b = 0u; b < max; ++b) {                        \
      Byte a_save = a;                                       \
      accessor.core.OPNAME(a_save, b);                       \
      Byte res = a OP b;                                     \
      EXPECT_EQ(accessor.core.get_flag(Core::Flags::C), _C); \
      EXPECT_EQ(accessor.core.get_flag(Core::Flags::H), _H); \
      EXPECT_EQ(accessor.core.get_flag(Core::Flags::N), _N); \
      EXPECT_EQ(accessor.core.get_flag(Core::Flags::Z),      \
                static_cast<Byte>(res) == 0);                \
      EXPECT_EQ(static_cast<Byte>(a_save), res);             \
    }                                                        \
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
    accessor.core.instr_inc(a);
    EXPECT_FALSE(accessor.core.get_flag(Core::Flags::N));
    EXPECT_EQ(accessor.core.get_flag(Core::Flags::Z), a == 0);
    EXPECT_EQ(accessor.core.get_flag(Core::Flags::H), (tmp & 0xfu) == 0xfu);
    ASSERT_EQ(a, tmp + 1);
  }
}

TEST_F(TestCoreFixture, dec) {
  constexpr Byte max = std::numeric_limits<Byte>::max();
  for (Byte a = max; a > 0;) {
    Byte tmp = a;
    accessor.core.instr_dec(a);
    EXPECT_TRUE(accessor.core.get_flag(Core::Flags::N));
    EXPECT_EQ(accessor.core.get_flag(Core::Flags::Z), a == 0);
    EXPECT_EQ(accessor.core.get_flag(Core::Flags::H), (tmp & 0xf0u) == 0xfu);
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
  accessor.getBc().high = 0x00;
  accessor.getPc().word = 0x00;
  std::vector<Byte> opcodes{0x3E, 0x42, 0x06, 0xF0, 0xAF, 0x78, 0xAF};
  int i = 0;

  auto it = opcodes.begin();

  accessor.core.execute(it);  // ld a, 0x42
  accessor.core.execute(it);  // ld b, 0xF0

  while (it + accessor.getPc().word != opcodes.end()) {
    accessor.core.execute(it);
    switch (i) {
      case 0:
        EXPECT_EQ(accessor.getAf().high, 0);
        break;
      case 1:
        EXPECT_EQ(accessor.getAf().high, 0xF0);
        break;
      case 2:
        EXPECT_EQ(accessor.getAf().high, 0);
        break;
      default:
        break;
    }
    i++;
  }
}

TEST_F(TestCoreFixture, cpl) {
  for (int i = 0x0; i < 0xFF; i++) {
    accessor.getAf().high = i;
    accessor.core.instr_cpl();
    test_flags(.n = 1, .h = 1);
    EXPECT_EQ(accessor.getAf().high, static_cast<uint8_t>(~i));
    accessor.core.set_flag(Core::Flags::N, false);
    accessor.core.set_flag(Core::Flags::H, false);
  }
}

TEST_F(TestCoreFixture, ccf) {
  accessor.core.set_flag(Core::Flags::N, true);
  accessor.core.set_flag(Core::Flags::H, true);
  accessor.core.set_flag(Core::Flags::C, true);
  accessor.core.instr_ccf();
  test_flags(.z = -1);
  accessor.core.instr_ccf();
  test_flags(.c = 1, .z = -1);
}

TEST_F(TestCoreFixture, scf) {
  accessor.core.set_flag(Core::Flags::N, true);
  accessor.core.set_flag(Core::Flags::H, true);
  accessor.core.set_flag(Core::Flags::C, false);
  accessor.core.instr_ccf();
  test_flags(.c = 1, .z = -1);
}

TEST_F(TestCoreFixture, sla) {
  for (Byte i = 0x1; i < 0xFF; i++) {
    accessor.getBc().low = i;
    Byte swap = i;
    accessor.core.instr_sla(accessor.getBc().low);
    EXPECT_EQ(accessor.core.get_flag(Core::Flags::C), test_bit(7, swap));
    test_flags(.c = -1, .z = -1);
    EXPECT_EQ(accessor.getBc().low, static_cast<Byte>(i << 1));
    EXPECT_EQ(accessor.core.get_flag(Core::Flags::Z), (i == 0x80));
  }
}

TEST_F(TestCoreFixture, sra) {
  for (Byte i = 0x1; i < 0xFF; i++) {
    accessor.getBc().high = i;
    Byte swap = i;
    accessor.core.instr_sra(accessor.getBc().high);
    EXPECT_EQ(accessor.core.get_flag(Core::Flags::C), test_bit(0, swap));
    test_flags(.c = -1, .z = -1);
    EXPECT_EQ(accessor.getBc().high, static_cast<Byte>(i >> 1));
    EXPECT_EQ(accessor.core.get_flag(Core::Flags::Z), (i == 0x01));
  }
}

TEST_F(TestCoreFixture, srl) {
  for (Byte i = 0x1; i < 0xFF; i++) {
    accessor.getBc().high = i;
    Byte swap = i;
    accessor.core.instr_srl(accessor.getBc().high);
    EXPECT_EQ(accessor.core.get_flag(Core::Flags::C), test_bit(0, swap));
    test_flags(.c = -1, .z = -1);
    EXPECT_EQ(accessor.getBc().high, static_cast<Byte>(i >> 1));
    EXPECT_EQ(accessor.core.get_flag(Core::Flags::Z), (i == 0x01));
  }
}

int main(int ac, char* av[]) {
  ::testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
