#include "Core.hpp"
#include <cassert>
#include <iostream>

// ----------------------------------------------------------------------------
// ld
// ----------------------------------------------------------------------------

void Core::instr_ldd(Byte& a, Byte b) {
	a = b;
	--_hl.word;
}

void Core::instr_ldi(Byte& a, Byte b) {
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

// ----------------------------------------------------------------------------
// Push/pop
// ----------------------------------------------------------------------------

void Core::instr_push(Word v) {
  write<Byte>(--_sp.word, static_cast<Byte>((v  & 0xFF00) >> 8));
  write<Byte>(--_sp.word, static_cast<Byte>((v & 0x00FF)));
}

void Core::instr_pop(Word& dest) {
  dest = read<Byte>(_sp.word++);
  dest |= static_cast<Word>(read<Byte>(_sp.word++)) << 8;
}

// ----------------------------------------------------------------------------
// Add/sub
// ----------------------------------------------------------------------------

void Core::instr_adc(Byte& a, Byte b) {
  instr_add<Byte, Byte>(a, get_flag(Flags::C));
  Byte saved_flags = _af.low;
  instr_add(a, b);
  _af.low |= (saved_flags & 0x30);
}

void Core::instr_sub(Byte& a, Byte b) {
	_af.low = 0x40u;
	Byte overflowing_nibbles = check_sub_overflows(a, b);
	set_flag(Flags::H, test_bit(4, overflowing_nibbles));
	set_flag(Flags::C, test_bit(0, overflowing_nibbles));
	a -= b;
	set_flag(Flags::Z, a == 0u);
}

void Core::instr_sbc(Byte& a, Byte b) {
  bool c = get_flag(Flags::C);
  instr_sub(a, b);
  Byte saved_flags = _af.low;
  instr_sub(a, c);
  _af.low |= (saved_flags & 0x30);
}

// ----------------------------------------------------------------------------
// Logical operations
// ----------------------------------------------------------------------------

void Core::instr_and(Byte& a, Byte b) {
	a &= b;
	_af.low = 0x20u;
	set_flag(Flags::Z, a == 0u);
}

void Core::instr_or(Byte& a, Byte b) {
	a |= b;
	_af.low = 0x0u;
	set_flag(Flags::Z, a == 0u);
}

void Core::instr_xor(Byte& a, Byte b) {
	a ^= b;
	_af.low = 0x0u;
	set_flag(Flags::Z, a == 0u);
}

void Core::instr_cp(Byte& a, Byte b) {
	Byte tmp = a;
	instr_sub(tmp, b);
}

// ----------------------------------------------------------------------------
// Increment/decrement
// ----------------------------------------------------------------------------

void Core::instr_inc(Byte& b) {
  set_flag(Flags::N, false);
  Byte overflowing_nibbles = check_add_overflows(b, Byte(1u));
  set_flag(Flags::H, test_bit(3, overflowing_nibbles));
  ++b;
  set_flag(Flags::Z, b == 0u);
}

void Core::instr_inc(Word& b) { ++b; }

void Core::instr_dec(Byte& b) {
  set_flag(Flags::N, true);
  Byte overflowing_nibbles = check_sub_overflows(b, Byte(1u));
  set_flag(Flags::H, test_bit(4, overflowing_nibbles));
  --b;
  set_flag(Flags::Z, b == 0u);
}

void Core::instr_dec(Word& b) { --b; }

/*
 * Turn the content of A that has been affected by an 'add' or a 'sub' between
 * two BCD values into a correct value.
 * ex: A = (0000 1000)bcd, B = (0100 0010)bcd
 *  ADD A, B -> A = (0100 1010)b # Incorrect BCD value
 *  DAA -> A = (0101 0000)b # correct BCD addition result
 */
void Core::instr_daa() {
	Byte correction_mask = 0u;

	if (get_flag(Flags::H) || ((_af.high & 0xf) > 0x9)) correction_mask |= 0x6;
	if (get_flag(Flags::C) || _af.high > 0x99) {
		correction_mask |= 0x60;
		set_flag(Flags::C, true);
	}
	(get_flag(Flags::N)) ? _af.high -= correction_mask : _af.high += correction_mask;
	set_flag(Flags::Z, _af.high == 0);
}

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


bool Core::is_condition_fulfilled(JumpCondition jc) {
	switch (jc) {
		case JumpCondition::None:
			return true;
			break;
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
	_in_jump_state = is_condition_fulfilled(jc);
	if (_in_jump_state) _pc.word = addr;
}

void Core::instr_jr(JumpCondition jc, Byte rel) {
	int8_t signed_rel = rel;
	_in_jump_state = is_condition_fulfilled(jc);
	if (_in_jump_state) _pc.word += signed_rel;
}

void Core::instr_call(JumpCondition jc, Word addr) {
	_in_jump_state = is_condition_fulfilled(jc);
	if (_in_jump_state) {
		instr_push(_pc.word + 3);
		_pc.word = addr;
	}
}

void Core::instr_ret(JumpCondition jc) {
	_in_jump_state = is_condition_fulfilled(jc);
	if (_in_jump_state) {
		instr_pop(_pc.word);
	}
}

void Core::instr_rst(Byte addr) {
	instr_push(_pc.word + 2);
	_pc.word = addr;
}

// ----------------------------------------------------------------------------
// Ret
// ----------------------------------------------------------------------------

void Core::instr_reti() {
	instr_ret(JumpCondition::None);
	// TODO Enable interrupts
}

// ----------------------------------------------------------------------------
// Byte shift and rotations
// ----------------------------------------------------------------------------

void Core::flag_handle(std::function<void(Byte&)> action, Byte& reg) {
	set_flag(Flags::N, false);
	set_flag(Flags::H, false);
	action(reg);
	set_flag(Flags::Z, reg == 0);
}

void Core::instr_rlc(Byte& reg) {
	flag_handle(
			[this](Byte& reg) {
			bool bit7 = test_bit(7, reg);
			set_flag(Flags::C, bit7);
			reg <<= 1;
			reg |= bit7;
			},
			reg);
}

void Core::instr_rl(Byte& reg) {
	flag_handle(
			[this](Byte& reg) {
			bool bit7 = test_bit(7, reg);
			reg <<= 1;
			reg |= get_flag(Flags::C);
			set_flag(Flags::C, bit7);
			},
			reg);
}

void Core::instr_rrc(Byte& reg) {
  flag_handle(
      [this](Byte& reg) {
        bool bit0 = test_bit(0, reg);
        set_flag(Flags::C, bit0);
        reg >>= 1;
        reg |= bit0 << 7;
      },
      reg);
}

void Core::instr_rr(Byte& reg) {
  flag_handle(
      [this](Byte& reg) {
        bool bit0 = test_bit(0, reg);
        reg >>= 1;
        reg |= get_flag(Flags::C) << 7;
        set_flag(Flags::C, bit0);
      },
      reg);
}

void Core::instr_sla(Byte& reg) {
	flag_handle(
			[this](Byte& reg) {
			set_flag(Flags::C, test_bit(7, reg));
			reg <<= 1;
			},
			reg);
}

void Core::instr_sra(Byte& reg) {
	flag_handle(
			[this](Byte& reg) {
			set_flag(Flags::C, test_bit(0, reg));
			reg >>= 1;
			},
			reg);
}

void Core::instr_srl(Byte& reg) {
	flag_handle(
			[this](Byte& reg) {
			set_flag(Flags::C, test_bit(0, reg));
			reg >>= 1;
			reset_bit(7, reg);
			},
			reg);
}

void Core::instr_swap(Byte& reg) { reg = (reg >> 4) | (reg << 4); }

// ----------------------------------------------------------------------------
// Bitwise operations
// ----------------------------------------------------------------------------

void Core::instr_bit(Byte reg, Byte bit) {
	set_flag(Flags::Z, test_bit(bit, reg));
	set_flag(Flags::N, false);
	set_flag(Flags::H, true);
}

void Core::instr_set(Byte& reg, Byte bit) { set_bit(bit, reg); }

void Core::instr_res(Byte& reg, Byte bit) { reset_bit(bit, reg); }

void Core::execute(Core::Iterator it) {
  it += _pc.word;
  Iterator original_it = it;
  auto fetch_word = [&] () -> Word {
    Word ret = *it++ << 8;
    ret |= *it++;
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
