#include "Core.hpp"

#include "src/Gameboy.hpp"
#include "src/MemoryBus.hpp"
#include "src/cpu/InterruptController.hpp"

#include <cassert>
#include <iostream>

// ----------------------------------------------------------------------------
// ld
// ----------------------------------------------------------------------------

void Core::instr_ldd(Byte &a, Byte b) {
  a = b;
  --_hl.word;
}

void Core::instr_ldi(Byte &a, Byte b) {
  a = b;
  ++_hl.word;
}

void Core::instr_ldhl(Byte n) {
  bool neg = test_bit(7, n);
  reset_bit(7, n);
  _hl.word = _sp.word;
  if (neg) {
    Word overflowing_nibbles =
        check_sub_overflows(_hl.word, static_cast<Word>(n));
    set_flag(Flags::H, test_bit(12, overflowing_nibbles));
    set_flag(Flags::C, test_bit(0, overflowing_nibbles));
    _hl.word -= n;
  } else {
    instr_add(_hl.word, static_cast<Word>(n));
  }
  set_flag(Flags::Z, false);
  set_flag(Flags::N, false);
}

// ldh A,(a8)
void Core::instr_ldh_a_v(Byte, Byte &v) { _af.high = v; }

// ldh (a8),A
void Core::instr_ldh_v_a(Byte &v, Byte) { v = _af.high; }

// ----------------------------------------------------------------------------
// Push/pop
// ----------------------------------------------------------------------------

void Core::instr_push(Word v) {
  _components.mem_bus->write(--_sp.word, static_cast<Byte>((v & 0xFF00) >> 8));
  _components.mem_bus->write(--_sp.word, static_cast<Byte>((v & 0x00FF)));
}

void Core::instr_pop(Word &dest) {
  dest = _components.mem_bus->read<Byte>(_sp.word++);
  dest |= static_cast<Word>(_components.mem_bus->read<Byte>(_sp.word++)) << 8;
}

// ----------------------------------------------------------------------------
// Add/sub
// ----------------------------------------------------------------------------

void Core::instr_adc(Byte &a, Byte b) {
  instr_add<Byte, Byte>(a, get_flag(Flags::C));
  Byte saved_flags = _af.low;
  instr_add(a, b);
  _af.low |= (saved_flags & 0x30);
}

void Core::instr_sub(Byte &a, Byte b) {
  _af.low = 0x40u;
  Byte overflowing_nibbles = check_sub_overflows(a, b);
  set_flag(Flags::H, test_bit(4, overflowing_nibbles));
  set_flag(Flags::C, test_bit(0, overflowing_nibbles));
  a -= b;
  set_flag(Flags::Z, a == 0u);
}

void Core::instr_sbc(Byte &a, Byte b) {
  bool c = get_flag(Flags::C);
  instr_sub(a, b);
  Byte saved_flags = _af.low;
  instr_sub(a, c);
  _af.low |= (saved_flags & 0x30);
}

// ----------------------------------------------------------------------------
// Logical operations
// ----------------------------------------------------------------------------

void Core::instr_and(Byte &a, Byte b) {
  a &= b;
  _af.low = 0x20u;
  set_flag(Flags::Z, a == 0u);
}

void Core::instr_or(Byte &a, Byte b) {
  a |= b;
  _af.low = 0x0u;
  set_flag(Flags::Z, a == 0u);
}

void Core::instr_xor(Byte &a, Byte b) {
  a ^= b;
  _af.low = 0x0u;
  set_flag(Flags::Z, a == 0u);
}

void Core::instr_cp(Byte &a, Byte b) {
  Byte tmp = a;
  instr_sub(tmp, b);
}

// ----------------------------------------------------------------------------
// Increment/decrement
// ----------------------------------------------------------------------------

void Core::instr_inc(Byte &b) {
  set_flag(Flags::N, false);
  Byte overflowing_nibbles = check_add_overflows(b, Byte(1u));
  set_flag(Flags::H, test_bit(3, overflowing_nibbles));
  ++b;
  set_flag(Flags::Z, b == 0u);
}

void Core::instr_inc(Word &b) { ++b; }

void Core::instr_dec(Byte &b) {

  Byte before = b;

  --b;

  set_flag(Flags::Z, b == 0u);
  set_flag(Flags::N, true);
  set_flag(Flags::H, (before & 0x0F) == 0);

}

// ----------------------------------------------------------------------------
// Miscellaneous
// ----------------------------------------------------------------------------

void Core::instr_dec(Word &b) { --b; }

/*
 * Turn the content of A that has been affected by an 'add' or a 'sub' between
 * two BCD values into a correct value.
 * ex: A = (0000 1000)bcd, B = (0100 0010)bcd
 *  ADD A, B -> A = (0100 1010)b # Incorrect BCD value
 *  DAA -> A = (0101 0000)b # correct BCD addition result
 */
void Core::instr_daa() {
  Byte correction_mask = 0u;

  if (get_flag(Flags::H) || ((_af.high & 0xf) > 0x9))
    correction_mask |= 0x6;
  if (get_flag(Flags::C) || _af.high > 0x99) {
    correction_mask |= 0x60;
    set_flag(Flags::C, true);
  }
  (get_flag(Flags::N)) ? _af.high -= correction_mask
                       : _af.high += correction_mask;
  set_flag(Flags::Z, _af.high == 0);
}

void Core::instr_halt() { _halt = true; }

// ----------------------------------------------------------------------------
// Flags manipulation
// ----------------------------------------------------------------------------

void Core::instr_cpl() {
  set_flag(Flags::N, true);
  set_flag(Flags::H, true);
  _af.high = ~_af.high;
}

void Core::instr_ccf() {
  set_flag(Flags::N, false);
  set_flag(Flags::H, false);
  set_flag(Flags::C, !get_flag(Flags::C));
}

void Core::instr_scf() {
  set_flag(Flags::N, false);
  set_flag(Flags::H, false);
  set_flag(Flags::C, true);
}

void Core::instr_di() { _components.interrupt_controller->SetIME(0); }

void Core::instr_ei() { _components.interrupt_controller->SetIME(1); }

bool Core::can_jump(JumpCondition jc) {
  switch (jc) {
  case JumpCondition::NonZero:
    return !get_flag(Flags::Z);
  case JumpCondition::Zero:
    return get_flag(Flags::Z);
  case JumpCondition::NonCarry:
    return !get_flag(Flags::C);
  case JumpCondition::Carry:
    return get_flag(Flags::C);
  }
  return false;
}

// ----------------------------------------------------------------------------
// Conditionnal jumps
// ----------------------------------------------------------------------------

void Core::instr_jp(JumpCondition jc, Word addr) {
  _in_jump_state = can_jump(jc);
  if (_in_jump_state) {
    _pc.word = addr;
    _has_jumped = true;
  }
}

void Core::instr_jp(Word addr) {
  _in_jump_state = true;
  _pc.word = addr;
  _has_jumped = true;
}

void Core::instr_jr(JumpCondition jc, Byte rel) {
  int8_t signed_rel = rel;
  if (can_jump(jc)) {
    _pc.word += signed_rel;
    _has_jumped = true;
  }
}

void Core::instr_jr(Byte rel) {
  int8_t signed_rel = rel;
  _pc.word += signed_rel;
  _has_jumped = true;
}

void Core::instr_call(JumpCondition jc, Word addr) {
  _in_jump_state = can_jump(jc);
  if (_in_jump_state) {
    instr_push(_pc.word + 3);
    _pc.word = addr;
    _has_jumped = true;
  }
}

void Core::instr_call(Word addr) {
  _in_jump_state = true;
  instr_push(_pc.word + 3);
  _pc.word = addr;
  _has_jumped = true;
}

void Core::instr_ret(JumpCondition jc) {
  _in_jump_state = can_jump(jc);
  if (_in_jump_state) {
    instr_pop(_pc.word);
    _has_jumped = true;
  }
}

void Core::instr_ret() {
  _in_jump_state = true;
  instr_pop(_pc.word);
  _has_jumped = true;
}

// ----------------------------------------------------------------------------
// Ret
// ----------------------------------------------------------------------------

void Core::instr_reti() {
  instr_ret();
  _components.interrupt_controller->SetIME(1);
}

void Core::instr_rst(Byte addr) {
  instr_push(_pc.word + 1);
  _pc.word = addr;
  _in_jump_state = true;
}

// ----------------------------------------------------------------------------
// Byte shift and rotations
// ----------------------------------------------------------------------------

void Core::flag_handle(std::function<void(Byte &)> action, Byte &reg) {
  set_flag(Flags::N, false);
  set_flag(Flags::H, false);
  action(reg);
  set_flag(Flags::Z, reg == 0);
}

void Core::instr_rlc(Byte &reg) {
  flag_handle(
      [this](Byte &reg) {
        bool bit7 = test_bit(7, reg);
        set_flag(Flags::C, bit7);
        reg <<= 1;
        reg |= bit7;
      },
      reg);
}

void Core::instr_rl(Byte &reg) {
  flag_handle(
      [this](Byte &reg) {
        bool bit7 = test_bit(7, reg);
        reg <<= 1;
        reg |= get_flag(Flags::C);
        set_flag(Flags::C, bit7);
      },
      reg);
}

void Core::instr_rrc(Byte &reg) {
  flag_handle(
      [this](Byte &reg) {
        bool bit0 = test_bit(0, reg);
        set_flag(Flags::C, bit0);
        reg >>= 1;
        reg |= bit0 << 7;
      },
      reg);
}

void Core::instr_rr(Byte &reg) {
  flag_handle(
      [this](Byte &reg) {
        bool bit0 = test_bit(0, reg);
        reg >>= 1;
        reg |= get_flag(Flags::C) << 7;
        set_flag(Flags::C, bit0);
      },
      reg);
}

void Core::instr_sla(Byte &reg) {
  flag_handle(
      [this](Byte &reg) {
        set_flag(Flags::C, test_bit(7, reg));
        reg <<= 1;
      },
      reg);
}

void Core::instr_sra(Byte &reg) {
  flag_handle(
      [this](Byte &reg) {
        set_flag(Flags::C, test_bit(0, reg));
        reg >>= 1;
      },
      reg);
}

void Core::instr_srl(Byte &reg) {
  flag_handle(
      [this](Byte &reg) {
        set_flag(Flags::C, test_bit(0, reg));
        reg >>= 1;
        reset_bit(7, reg);
      },
      reg);
}

void Core::instr_swap(Byte &reg) { reg = (reg >> 4) | (reg << 4); }

// ----------------------------------------------------------------------------
// Bitwise operations
// ----------------------------------------------------------------------------

void Core::instr_bit(Byte bit, Byte &reg) {
  set_flag(Flags::Z, test_bit(bit, reg));
  set_flag(Flags::N, false);
  set_flag(Flags::H, true);
}

void Core::instr_set(Byte bit, Byte &reg) { set_bit(bit, reg); }

void Core::instr_res(Byte bit, Byte &reg) { reset_bit(bit, reg); }

// ----------------------------------------------------------------------------
// Core exec utilities
// ----------------------------------------------------------------------------

void Core::exec_instruction(std::function<void(void)> instr, Byte clock_cycles1,
                            Byte clock_cycles2) {
  instr();
  if (_has_jumped) {
    _clock += clock_cycles1;
    _cycles = clock_cycles1;
  } else {
    _clock += clock_cycles2;
    _cycles = clock_cycles2;
  }
  _has_jumped = false;
}

void Core::exec_instruction(std::function<void(Byte &)> instr, Word addr,
                            Byte clock_cycles1, Byte clock_cycles2) {
  Byte b = _components.mem_bus->read<Byte>(addr);
  instr(b);
  if (_has_jumped) {
    _clock += clock_cycles1;
    _cycles = clock_cycles1;
  } else {
    _clock += clock_cycles2;
    _cycles = clock_cycles2;
  }
  _components.mem_bus->write<Byte>(addr, b);
  _has_jumped = false;
}

void Core::exec_instruction(std::function<void(void)> instr,
                            Byte clock_cycles) {
  instr();
  _clock += clock_cycles;
  _cycles = clock_cycles;
}

void Core::exec_instruction(std::function<void(Byte &)> instr, Word addr,
                            Byte clock_cycles) {
  Byte b = _components.mem_bus->read<Byte>(addr);
  instr(b);
  _components.mem_bus->write<Byte>(addr, b);
  _clock += clock_cycles;
  _cycles = clock_cycles;
}

void Core::exec_instruction(std::function<void(Word &)> instr, Word addr,
                            Byte clock_cycles) {
  Word b = _components.mem_bus->read<Word>(addr);
  instr(b);
  _components.mem_bus->write<Word>(addr, b);
  _clock += clock_cycles;
  _cycles = clock_cycles;
}

void Core::execute(Core::Iterator it) {
  if (_halt)
    return;
  it += _pc.word;
  Iterator original_it = it;
  auto fetch_word = [&]() -> Word {
    Word ret = *it++;
    ret |= *it++ << 8;
    return ret;
  };
  switch (*it++) {
#include "instructions.inc"
  default:
    break;
  }
  if (_in_jump_state)
    _in_jump_state = false;
  else
    _pc.word += it - original_it;
}

// ----------------------------------------------------------------------------
// Read and write
// ----------------------------------------------------------------------------

Byte Core::read(Word addr) const {
  assert(addr >= 0xFF80 and addr <= 0xFFFE);
  return _stack[addr - 0xFF80];
}

void Core::write(Word addr, Byte v) {
  assert(addr >= 0xFF80 and addr <= 0xFFFE);
  _stack[addr - 0xFF80] = v;
}
