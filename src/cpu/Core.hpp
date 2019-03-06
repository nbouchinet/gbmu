#pragma once
#ifndef CORE_HPP
#define CORE_HPP

#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"
#include "utils/Operations_utils.hpp"

#include <array>
#include <cstdint>
#include <functional>
#include <vector>

union Register {
  Word word = 0;
  struct {
    Byte low, high;
  };
};

class Accessor; // Friend interface class for unit testing

class Core : public IReadWrite {
public:
  enum class Flags { C = 0x10, H = 0x20, N = 0x40, Z = 0x80 };
  static constexpr std::size_t StackSize = 0x7F;

  Core(ComponentsContainer &components) : _components(components) {}
  Core(const Core &) = delete;

  friend class Accessor;

private:
  Register _pc = {.word = 0x0100};
  Register _sp = {.word = 0xfffe};
  Register _af = {.word = 0x01b0};
  Register _bc = {.word = 0x0013};
  Register _de = {.word = 0x00d8};
  Register _hl = {.word = 0x014d};
  Word _clock = 0x00;
  Word _cycles = 0x00;
  bool _in_jump_state = false;
  bool _has_jumped = false;
  std::array<Byte, StackSize> _stack;
  bool _halt = false;

  ComponentsContainer &_components;

public:
  void set_flag(Flags f, bool v) {
    int mask = static_cast<int>(f);
    if (v)
      _af.low |= mask;
    else if (!v && _af.low & mask)
      _af.low ^= mask;
  }

public:
  template <typename T> void instr_ld(T &a, T b) { a = b; }
  void instr_ldd(Byte &, Byte);
  void instr_ldi(Byte &, Byte);
  void instr_ldhl(Byte a);
  void instr_ldh(Byte &v, Byte b) { instr_ld(v, b); }
  void instr_push(Word v);
  void instr_pop(Word &dest);

  template <typename A, typename B> void instr_add(A &a, B b);
  void instr_adc(Byte &, Byte);
  void instr_sub(Byte &, Byte);
  void instr_sbc(Byte &, Byte);
  void instr_and(Byte &, Byte);
  void instr_or(Byte &, Byte);
  void instr_xor(Byte &, Byte);
  void instr_cp(Byte &, Byte);

  void instr_inc(Byte &);
  void instr_inc(Word &);
  void instr_dec(Byte &);
  void instr_dec(Word &);

  void instr_daa();
  void instr_cpl();
  void instr_ccf();
  void instr_scf();
  void instr_nop(Byte) {}
  void instr_halt();
  void instr_stop() {}
  void instr_di();
  void instr_ei();

  enum class JumpCondition { NonZero, Zero, NonCarry, Carry };
  bool can_jump(JumpCondition);
  void instr_jp(JumpCondition, Word);
  void instr_jp(Word);
  void instr_jr(JumpCondition, Byte);
  void instr_jr(Byte);
  void instr_call(JumpCondition, Word);
  void instr_call(Word);
  void instr_ret(JumpCondition);
  void instr_ret();
  void instr_reti();
  void instr_rst(Byte);

  void flag_handle(std::function<void(Byte &)> action, Byte &reg);
  void instr_rlc(Byte &);
  void instr_rl(Byte &);
  void instr_rrc(Byte &);
  void instr_rr(Byte &);
  void instr_sla(Byte &);
  void instr_sra(Byte &);
  void instr_srl(Byte &);

  void instr_rlca() { instr_rlc(_af.high); }
  void instr_rla() { instr_rl(_af.high); }
  void instr_rrca() { instr_rrc(_af.high); }
  void instr_rra() { instr_rr(_af.high); }

  void instr_swap(Byte &);
  void instr_bit(Byte, Byte &);
  void instr_set(Byte, Byte &);
  void instr_res(Byte, Byte &);

  bool get_flag(Flags f) const { return _af.low & static_cast<int>(f); }
  auto clock() const { return _clock; }
  auto cycles() const { return _cycles; }
  auto pc() const { return _pc.word; }
  auto sp() const { return _sp.word; }
  auto af() const { return _af; }
  auto bc() const { return _bc; }
  auto de() const { return _de; }
  auto hl() const { return _hl; }
  bool in_jump_state() const { return _in_jump_state; }

  void exec_instruction(std::function<void(void)> instr, Byte clock_cycles1,
                        Byte clock_cycles2);
  void exec_instruction(std::function<void(Byte &)> instr, Word addr,
                        Byte clock_cycles1, Byte clock_cycles2);
  void exec_instruction(std::function<void(void)> instr, Byte clock_cycles[2]);
  void exec_instruction(std::function<void(void)> instr, Byte clock_cycles);
  void exec_instruction(std::function<void(Byte &)> instr, Word addr,
                        Byte clock_cycles);
  void exec_instruction(std::function<void(Word &)> instr, Word addr,
                        Byte clock_cycles);

  using Iterator = std::vector<Byte>::const_iterator;
  void execute(Iterator it);

  void notify_interrupt() {
    if (_halt)
      _halt = false;
  }
  Byte read(Word addr) const override;
  void write(Word addr, Byte) override;
};

template <> inline void Core::instr_add<Byte, Byte>(Byte &a, Byte b) {
  _af.low = 0u;
  set_flag(Flags::H, check_add_overflow_from(a, b, 4));
  set_flag(Flags::C, check_add_overflow_from(a, b, 8));
  a += b;
  set_flag(Flags::Z, a == 0u);
}

template <> inline void Core::instr_add<Word, Word>(Word &a, Word b) {
  _af.low = 0u;
  set_flag(Flags::H, check_add_overflow_from(a, b, 12));
  set_flag(Flags::C, check_add_overflow_from(a, b, 16));
  a += b;
  set_flag(Flags::Z, a == 0u);
}

template <> inline void Core::instr_add<Word, Byte>(Word &a, Byte b) {
  instr_add<Word, Word>(a, static_cast<Word>(b));
}
#endif
