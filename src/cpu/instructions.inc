case 0x0:
#ifdef DEBUG_CORE
std::printf("%04x: nop\n", _pc.word);
#endif
  _current_opcode = 0x0;
  exec_instruction([&] () { instr_nop(); }, 4);
  break;
case 0x1:
#ifdef DEBUG_CORE
std::printf("%04x: ld BC d16\n", _pc.word);
#endif
  _current_opcode = 0x1;
  exec_instruction([&] () { instr_ld(_bc.word, fetch_word()); }, 12);
  break;
case 0x2:
#ifdef DEBUG_CORE
std::printf("%04x: ld (BC) A\n", _pc.word);
#endif
  _current_opcode = 0x2;
  exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, _bc.word, 8);
  break;
case 0x3:
#ifdef DEBUG_CORE
std::printf("%04x: inc BC\n", _pc.word);
#endif
  _current_opcode = 0x3;
  exec_instruction([&] () { instr_inc(_bc.word); }, 8);
  break;
case 0x4:
#ifdef DEBUG_CORE
std::printf("%04x: inc B\n", _pc.word);
#endif
  _current_opcode = 0x4;
  exec_instruction([&] () { instr_inc(_bc.high); }, 4);
  break;
case 0x5:
#ifdef DEBUG_CORE
std::printf("%04x: dec B\n", _pc.word);
#endif
  _current_opcode = 0x5;
  exec_instruction([&] () { instr_dec(_bc.high); }, 4);
  break;
case 0x6:
#ifdef DEBUG_CORE
std::printf("%04x: ld B d8\n", _pc.word);
#endif
  _current_opcode = 0x6;
  exec_instruction([&] () { instr_ld(_bc.high, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0x7:
#ifdef DEBUG_CORE
std::printf("%04x: rlca\n", _pc.word);
#endif
  _current_opcode = 0x7;
  exec_instruction([&] () { instr_rlca(); }, 4);
  break;
case 0x8:
#ifdef DEBUG_CORE
std::printf("%04x: ld (a16) SP\n", _pc.word);
#endif
  _current_opcode = 0x8;
  exec_instruction([&] (Word &v) { instr_ld(v, _sp.word); }, fetch_word(), 20);
  break;
case 0x9:
#ifdef DEBUG_CORE
std::printf("%04x: add HL BC\n", _pc.word);
#endif
  _current_opcode = 0x9;
  exec_instruction([&] () { instr_add(_hl.word, _bc.word); }, 8);
  break;
case 0xa:
#ifdef DEBUG_CORE
std::printf("%04x: ld A (BC)\n", _pc.word);
#endif
  _current_opcode = 0xa;
  exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(_bc.word)); }, 8);
  break;
case 0xb:
#ifdef DEBUG_CORE
std::printf("%04x: dec BC\n", _pc.word);
#endif
  _current_opcode = 0xb;
  exec_instruction([&] () { instr_dec(_bc.word); }, 8);
  break;
case 0xc:
#ifdef DEBUG_CORE
std::printf("%04x: inc C\n", _pc.word);
#endif
  _current_opcode = 0xc;
  exec_instruction([&] () { instr_inc(_bc.low); }, 4);
  break;
case 0xd:
#ifdef DEBUG_CORE
std::printf("%04x: dec C\n", _pc.word);
#endif
  _current_opcode = 0xd;
  exec_instruction([&] () { instr_dec(_bc.low); }, 4);
  break;
case 0xe:
#ifdef DEBUG_CORE
std::printf("%04x: ld C d8\n", _pc.word);
#endif
  _current_opcode = 0xe;
  exec_instruction([&] () { instr_ld(_bc.low, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0xf:
#ifdef DEBUG_CORE
std::printf("%04x: rrca\n", _pc.word);
#endif
  _current_opcode = 0xf;
  exec_instruction([&] () { instr_rrca(); }, 4);
  break;
case 0x10:
#ifdef DEBUG_CORE
std::printf("%04x: stop 0\n", _pc.word);
#endif
  _current_opcode = 0x10;
  exec_instruction([&] () { instr_stop(0); }, 4);
  break;
case 0x11:
#ifdef DEBUG_CORE
std::printf("%04x: ld DE d16\n", _pc.word);
#endif
  _current_opcode = 0x11;
  exec_instruction([&] () { instr_ld(_de.word, fetch_word()); }, 12);
  break;
case 0x12:
#ifdef DEBUG_CORE
std::printf("%04x: ld (DE) A\n", _pc.word);
#endif
  _current_opcode = 0x12;
  exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, _de.word, 8);
  break;
case 0x13:
#ifdef DEBUG_CORE
std::printf("%04x: inc DE\n", _pc.word);
#endif
  _current_opcode = 0x13;
  exec_instruction([&] () { instr_inc(_de.word); }, 8);
  break;
case 0x14:
#ifdef DEBUG_CORE
std::printf("%04x: inc D\n", _pc.word);
#endif
  _current_opcode = 0x14;
  exec_instruction([&] () { instr_inc(_de.high); }, 4);
  break;
case 0x15:
#ifdef DEBUG_CORE
std::printf("%04x: dec D\n", _pc.word);
#endif
  _current_opcode = 0x15;
  exec_instruction([&] () { instr_dec(_de.high); }, 4);
  break;
case 0x16:
#ifdef DEBUG_CORE
std::printf("%04x: ld D d8\n", _pc.word);
#endif
  _current_opcode = 0x16;
  exec_instruction([&] () { instr_ld(_de.high, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0x17:
#ifdef DEBUG_CORE
std::printf("%04x: rla\n", _pc.word);
#endif
  _current_opcode = 0x17;
  exec_instruction([&] () { instr_rla(); }, 4);
  break;
case 0x18:
#ifdef DEBUG_CORE
std::printf("%04x: jr r8\n", _pc.word);
#endif
  _current_opcode = 0x18;
  exec_instruction([&] () { instr_jr(_components.mem_bus->read<Byte>(addr++)); }, 12);
  break;
case 0x19:
#ifdef DEBUG_CORE
std::printf("%04x: add HL DE\n", _pc.word);
#endif
  _current_opcode = 0x19;
  exec_instruction([&] () { instr_add(_hl.word, _de.word); }, 8);
  break;
case 0x1a:
#ifdef DEBUG_CORE
std::printf("%04x: ld A (DE)\n", _pc.word);
#endif
  _current_opcode = 0x1a;
  exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(_de.word)); }, 8);
  break;
case 0x1b:
#ifdef DEBUG_CORE
std::printf("%04x: dec DE\n", _pc.word);
#endif
  _current_opcode = 0x1b;
  exec_instruction([&] () { instr_dec(_de.word); }, 8);
  break;
case 0x1c:
#ifdef DEBUG_CORE
std::printf("%04x: inc E\n", _pc.word);
#endif
  _current_opcode = 0x1c;
  exec_instruction([&] () { instr_inc(_de.low); }, 4);
  break;
case 0x1d:
#ifdef DEBUG_CORE
std::printf("%04x: dec E\n", _pc.word);
#endif
  _current_opcode = 0x1d;
  exec_instruction([&] () { instr_dec(_de.low); }, 4);
  break;
case 0x1e:
#ifdef DEBUG_CORE
std::printf("%04x: ld E d8\n", _pc.word);
#endif
  _current_opcode = 0x1e;
  exec_instruction([&] () { instr_ld(_de.low, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0x1f:
#ifdef DEBUG_CORE
std::printf("%04x: rra\n", _pc.word);
#endif
  _current_opcode = 0x1f;
  exec_instruction([&] () { instr_rra(); }, 4);
  break;
case 0x20:
#ifdef DEBUG_CORE
std::printf("%04x: jr NZ r8\n", _pc.word);
#endif
  _current_opcode = 0x20;
  exec_instruction([&] () { instr_jr(JumpCondition::NonZero, _components.mem_bus->read<Byte>(addr++)); }, 12, 8);
  break;
case 0x21:
#ifdef DEBUG_CORE
std::printf("%04x: ld HL d16\n", _pc.word);
#endif
  _current_opcode = 0x21;
  exec_instruction([&] () { instr_ld(_hl.word, fetch_word()); }, 12);
  break;
case 0x22:
#ifdef DEBUG_CORE
std::printf("%04x: ldi (HL) A\n", _pc.word);
#endif
  _current_opcode = 0x22;
  exec_instruction([&] (Byte &v) { instr_ldi(v, _af.high); }, _hl.word, 8);
  break;
case 0x23:
#ifdef DEBUG_CORE
std::printf("%04x: inc HL\n", _pc.word);
#endif
  _current_opcode = 0x23;
  exec_instruction([&] () { instr_inc(_hl.word); }, 8);
  break;
case 0x24:
#ifdef DEBUG_CORE
std::printf("%04x: inc H\n", _pc.word);
#endif
  _current_opcode = 0x24;
  exec_instruction([&] () { instr_inc(_hl.high); }, 4);
  break;
case 0x25:
#ifdef DEBUG_CORE
std::printf("%04x: dec H\n", _pc.word);
#endif
  _current_opcode = 0x25;
  exec_instruction([&] () { instr_dec(_hl.high); }, 4);
  break;
case 0x26:
#ifdef DEBUG_CORE
std::printf("%04x: ld H d8\n", _pc.word);
#endif
  _current_opcode = 0x26;
  exec_instruction([&] () { instr_ld(_hl.high, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0x27:
#ifdef DEBUG_CORE
std::printf("%04x: daa\n", _pc.word);
#endif
  _current_opcode = 0x27;
  exec_instruction([&] () { instr_daa(); }, 4);
  break;
case 0x28:
#ifdef DEBUG_CORE
std::printf("%04x: jr Z r8\n", _pc.word);
#endif
  _current_opcode = 0x28;
  exec_instruction([&] () { instr_jr(JumpCondition::Zero, _components.mem_bus->read<Byte>(addr++)); }, 12, 8);
  break;
case 0x29:
#ifdef DEBUG_CORE
std::printf("%04x: add HL HL\n", _pc.word);
#endif
  _current_opcode = 0x29;
  exec_instruction([&] () { instr_add(_hl.word, _hl.word); }, 8);
  break;
case 0x2a:
#ifdef DEBUG_CORE
std::printf("%04x: ldi A (HL)\n", _pc.word);
#endif
  _current_opcode = 0x2a;
  exec_instruction([&] () { instr_ldi(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x2b:
#ifdef DEBUG_CORE
std::printf("%04x: dec HL\n", _pc.word);
#endif
  _current_opcode = 0x2b;
  exec_instruction([&] () { instr_dec(_hl.word); }, 8);
  break;
case 0x2c:
#ifdef DEBUG_CORE
std::printf("%04x: inc L\n", _pc.word);
#endif
  _current_opcode = 0x2c;
  exec_instruction([&] () { instr_inc(_hl.low); }, 4);
  break;
case 0x2d:
#ifdef DEBUG_CORE
std::printf("%04x: dec L\n", _pc.word);
#endif
  _current_opcode = 0x2d;
  exec_instruction([&] () { instr_dec(_hl.low); }, 4);
  break;
case 0x2e:
#ifdef DEBUG_CORE
std::printf("%04x: ld L d8\n", _pc.word);
#endif
  _current_opcode = 0x2e;
  exec_instruction([&] () { instr_ld(_hl.low, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0x2f:
#ifdef DEBUG_CORE
std::printf("%04x: cpl\n", _pc.word);
#endif
  _current_opcode = 0x2f;
  exec_instruction([&] () { instr_cpl(); }, 4);
  break;
case 0x30:
#ifdef DEBUG_CORE
std::printf("%04x: jr NC r8\n", _pc.word);
#endif
  _current_opcode = 0x30;
  exec_instruction([&] () { instr_jr(JumpCondition::NonCarry, _components.mem_bus->read<Byte>(addr++)); }, 12, 8);
  break;
case 0x31:
#ifdef DEBUG_CORE
std::printf("%04x: ld SP d16\n", _pc.word);
#endif
  _current_opcode = 0x31;
  exec_instruction([&] () { instr_ld(_sp.word, fetch_word()); }, 12);
  break;
case 0x32:
#ifdef DEBUG_CORE
std::printf("%04x: ldd (HL) A\n", _pc.word);
#endif
  _current_opcode = 0x32;
  exec_instruction([&] (Byte &v) { instr_ldd(v, _af.high); }, _hl.word, 8);
  break;
case 0x33:
#ifdef DEBUG_CORE
std::printf("%04x: inc SP\n", _pc.word);
#endif
  _current_opcode = 0x33;
  exec_instruction([&] () { instr_inc(_sp.word); }, 8);
  break;
case 0x34:
#ifdef DEBUG_CORE
std::printf("%04x: inc (HL)\n", _pc.word);
#endif
  _current_opcode = 0x34;
  exec_instruction([&] (Byte &v) { instr_inc(v); }, _hl.word, 12);
  break;
case 0x35:
#ifdef DEBUG_CORE
std::printf("%04x: dec (HL)\n", _pc.word);
#endif
  _current_opcode = 0x35;
  exec_instruction([&] (Byte &v) { instr_dec(v); }, _hl.word, 12);
  break;
case 0x36:
#ifdef DEBUG_CORE
std::printf("%04x: ld (HL) d8\n", _pc.word);
#endif
  _current_opcode = 0x36;
  exec_instruction([&] (Byte &v) { instr_ld(v, _components.mem_bus->read<Byte>(addr++)); }, _hl.word, 12);
  break;
case 0x37:
#ifdef DEBUG_CORE
std::printf("%04x: scf\n", _pc.word);
#endif
  _current_opcode = 0x37;
  exec_instruction([&] () { instr_scf(); }, 4);
  break;
case 0x38:
#ifdef DEBUG_CORE
std::printf("%04x: jr C r8\n", _pc.word);
#endif
  _current_opcode = 0x38;
  exec_instruction([&] () { instr_jr(JumpCondition::Carry, _components.mem_bus->read<Byte>(addr++)); }, 12, 8);
  break;
case 0x39:
#ifdef DEBUG_CORE
std::printf("%04x: add HL SP\n", _pc.word);
#endif
  _current_opcode = 0x39;
  exec_instruction([&] () { instr_add(_hl.word, _sp.word); }, 8);
  break;
case 0x3a:
#ifdef DEBUG_CORE
std::printf("%04x: ldd A (HL)\n", _pc.word);
#endif
  _current_opcode = 0x3a;
  exec_instruction([&] () { instr_ldd(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x3b:
#ifdef DEBUG_CORE
std::printf("%04x: dec SP\n", _pc.word);
#endif
  _current_opcode = 0x3b;
  exec_instruction([&] () { instr_dec(_sp.word); }, 8);
  break;
case 0x3c:
#ifdef DEBUG_CORE
std::printf("%04x: inc A\n", _pc.word);
#endif
  _current_opcode = 0x3c;
  exec_instruction([&] () { instr_inc(_af.high); }, 4);
  break;
case 0x3d:
#ifdef DEBUG_CORE
std::printf("%04x: dec A\n", _pc.word);
#endif
  _current_opcode = 0x3d;
  exec_instruction([&] () { instr_dec(_af.high); }, 4);
  break;
case 0x3e:
#ifdef DEBUG_CORE
std::printf("%04x: ld A d8\n", _pc.word);
#endif
  _current_opcode = 0x3e;
  exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0x3f:
#ifdef DEBUG_CORE
std::printf("%04x: ccf\n", _pc.word);
#endif
  _current_opcode = 0x3f;
  exec_instruction([&] () { instr_ccf(); }, 4);
  break;
case 0x40:
#ifdef DEBUG_CORE
std::printf("%04x: ld B B\n", _pc.word);
#endif
  _current_opcode = 0x40;
  exec_instruction([&] () { instr_ld(_bc.high, _bc.high); }, 4);
  break;
case 0x41:
#ifdef DEBUG_CORE
std::printf("%04x: ld B C\n", _pc.word);
#endif
  _current_opcode = 0x41;
  exec_instruction([&] () { instr_ld(_bc.high, _bc.low); }, 4);
  break;
case 0x42:
#ifdef DEBUG_CORE
std::printf("%04x: ld B D\n", _pc.word);
#endif
  _current_opcode = 0x42;
  exec_instruction([&] () { instr_ld(_bc.high, _de.high); }, 4);
  break;
case 0x43:
#ifdef DEBUG_CORE
std::printf("%04x: ld B E\n", _pc.word);
#endif
  _current_opcode = 0x43;
  exec_instruction([&] () { instr_ld(_bc.high, _de.low); }, 4);
  break;
case 0x44:
#ifdef DEBUG_CORE
std::printf("%04x: ld B H\n", _pc.word);
#endif
  _current_opcode = 0x44;
  exec_instruction([&] () { instr_ld(_bc.high, _hl.high); }, 4);
  break;
case 0x45:
#ifdef DEBUG_CORE
std::printf("%04x: ld B L\n", _pc.word);
#endif
  _current_opcode = 0x45;
  exec_instruction([&] () { instr_ld(_bc.high, _hl.low); }, 4);
  break;
case 0x46:
#ifdef DEBUG_CORE
std::printf("%04x: ld B (HL)\n", _pc.word);
#endif
  _current_opcode = 0x46;
  exec_instruction([&] () { instr_ld(_bc.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x47:
#ifdef DEBUG_CORE
std::printf("%04x: ld B A\n", _pc.word);
#endif
  _current_opcode = 0x47;
  exec_instruction([&] () { instr_ld(_bc.high, _af.high); }, 4);
  break;
case 0x48:
#ifdef DEBUG_CORE
std::printf("%04x: ld C B\n", _pc.word);
#endif
  _current_opcode = 0x48;
  exec_instruction([&] () { instr_ld(_bc.low, _bc.high); }, 4);
  break;
case 0x49:
#ifdef DEBUG_CORE
std::printf("%04x: ld C C\n", _pc.word);
#endif
  _current_opcode = 0x49;
  exec_instruction([&] () { instr_ld(_bc.low, _bc.low); }, 4);
  break;
case 0x4a:
#ifdef DEBUG_CORE
std::printf("%04x: ld C D\n", _pc.word);
#endif
  _current_opcode = 0x4a;
  exec_instruction([&] () { instr_ld(_bc.low, _de.high); }, 4);
  break;
case 0x4b:
#ifdef DEBUG_CORE
std::printf("%04x: ld C E\n", _pc.word);
#endif
  _current_opcode = 0x4b;
  exec_instruction([&] () { instr_ld(_bc.low, _de.low); }, 4);
  break;
case 0x4c:
#ifdef DEBUG_CORE
std::printf("%04x: ld C H\n", _pc.word);
#endif
  _current_opcode = 0x4c;
  exec_instruction([&] () { instr_ld(_bc.low, _hl.high); }, 4);
  break;
case 0x4d:
#ifdef DEBUG_CORE
std::printf("%04x: ld C L\n", _pc.word);
#endif
  _current_opcode = 0x4d;
  exec_instruction([&] () { instr_ld(_bc.low, _hl.low); }, 4);
  break;
case 0x4e:
#ifdef DEBUG_CORE
std::printf("%04x: ld C (HL)\n", _pc.word);
#endif
  _current_opcode = 0x4e;
  exec_instruction([&] () { instr_ld(_bc.low, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x4f:
#ifdef DEBUG_CORE
std::printf("%04x: ld C A\n", _pc.word);
#endif
  _current_opcode = 0x4f;
  exec_instruction([&] () { instr_ld(_bc.low, _af.high); }, 4);
  break;
case 0x50:
#ifdef DEBUG_CORE
std::printf("%04x: ld D B\n", _pc.word);
#endif
  _current_opcode = 0x50;
  exec_instruction([&] () { instr_ld(_de.high, _bc.high); }, 4);
  break;
case 0x51:
#ifdef DEBUG_CORE
std::printf("%04x: ld D C\n", _pc.word);
#endif
  _current_opcode = 0x51;
  exec_instruction([&] () { instr_ld(_de.high, _bc.low); }, 4);
  break;
case 0x52:
#ifdef DEBUG_CORE
std::printf("%04x: ld D D\n", _pc.word);
#endif
  _current_opcode = 0x52;
  exec_instruction([&] () { instr_ld(_de.high, _de.high); }, 4);
  break;
case 0x53:
#ifdef DEBUG_CORE
std::printf("%04x: ld D E\n", _pc.word);
#endif
  _current_opcode = 0x53;
  exec_instruction([&] () { instr_ld(_de.high, _de.low); }, 4);
  break;
case 0x54:
#ifdef DEBUG_CORE
std::printf("%04x: ld D H\n", _pc.word);
#endif
  _current_opcode = 0x54;
  exec_instruction([&] () { instr_ld(_de.high, _hl.high); }, 4);
  break;
case 0x55:
#ifdef DEBUG_CORE
std::printf("%04x: ld D L\n", _pc.word);
#endif
  _current_opcode = 0x55;
  exec_instruction([&] () { instr_ld(_de.high, _hl.low); }, 4);
  break;
case 0x56:
#ifdef DEBUG_CORE
std::printf("%04x: ld D (HL)\n", _pc.word);
#endif
  _current_opcode = 0x56;
  exec_instruction([&] () { instr_ld(_de.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x57:
#ifdef DEBUG_CORE
std::printf("%04x: ld D A\n", _pc.word);
#endif
  _current_opcode = 0x57;
  exec_instruction([&] () { instr_ld(_de.high, _af.high); }, 4);
  break;
case 0x58:
#ifdef DEBUG_CORE
std::printf("%04x: ld E B\n", _pc.word);
#endif
  _current_opcode = 0x58;
  exec_instruction([&] () { instr_ld(_de.low, _bc.high); }, 4);
  break;
case 0x59:
#ifdef DEBUG_CORE
std::printf("%04x: ld E C\n", _pc.word);
#endif
  _current_opcode = 0x59;
  exec_instruction([&] () { instr_ld(_de.low, _bc.low); }, 4);
  break;
case 0x5a:
#ifdef DEBUG_CORE
std::printf("%04x: ld E D\n", _pc.word);
#endif
  _current_opcode = 0x5a;
  exec_instruction([&] () { instr_ld(_de.low, _de.high); }, 4);
  break;
case 0x5b:
#ifdef DEBUG_CORE
std::printf("%04x: ld E E\n", _pc.word);
#endif
  _current_opcode = 0x5b;
  exec_instruction([&] () { instr_ld(_de.low, _de.low); }, 4);
  break;
case 0x5c:
#ifdef DEBUG_CORE
std::printf("%04x: ld E H\n", _pc.word);
#endif
  _current_opcode = 0x5c;
  exec_instruction([&] () { instr_ld(_de.low, _hl.high); }, 4);
  break;
case 0x5d:
#ifdef DEBUG_CORE
std::printf("%04x: ld E L\n", _pc.word);
#endif
  _current_opcode = 0x5d;
  exec_instruction([&] () { instr_ld(_de.low, _hl.low); }, 4);
  break;
case 0x5e:
#ifdef DEBUG_CORE
std::printf("%04x: ld E (HL)\n", _pc.word);
#endif
  _current_opcode = 0x5e;
  exec_instruction([&] () { instr_ld(_de.low, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x5f:
#ifdef DEBUG_CORE
std::printf("%04x: ld E A\n", _pc.word);
#endif
  _current_opcode = 0x5f;
  exec_instruction([&] () { instr_ld(_de.low, _af.high); }, 4);
  break;
case 0x60:
#ifdef DEBUG_CORE
std::printf("%04x: ld H B\n", _pc.word);
#endif
  _current_opcode = 0x60;
  exec_instruction([&] () { instr_ld(_hl.high, _bc.high); }, 4);
  break;
case 0x61:
#ifdef DEBUG_CORE
std::printf("%04x: ld H C\n", _pc.word);
#endif
  _current_opcode = 0x61;
  exec_instruction([&] () { instr_ld(_hl.high, _bc.low); }, 4);
  break;
case 0x62:
#ifdef DEBUG_CORE
std::printf("%04x: ld H D\n", _pc.word);
#endif
  _current_opcode = 0x62;
  exec_instruction([&] () { instr_ld(_hl.high, _de.high); }, 4);
  break;
case 0x63:
#ifdef DEBUG_CORE
std::printf("%04x: ld H E\n", _pc.word);
#endif
  _current_opcode = 0x63;
  exec_instruction([&] () { instr_ld(_hl.high, _de.low); }, 4);
  break;
case 0x64:
#ifdef DEBUG_CORE
std::printf("%04x: ld H H\n", _pc.word);
#endif
  _current_opcode = 0x64;
  exec_instruction([&] () { instr_ld(_hl.high, _hl.high); }, 4);
  break;
case 0x65:
#ifdef DEBUG_CORE
std::printf("%04x: ld H L\n", _pc.word);
#endif
  _current_opcode = 0x65;
  exec_instruction([&] () { instr_ld(_hl.high, _hl.low); }, 4);
  break;
case 0x66:
#ifdef DEBUG_CORE
std::printf("%04x: ld H (HL)\n", _pc.word);
#endif
  _current_opcode = 0x66;
  exec_instruction([&] () { instr_ld(_hl.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x67:
#ifdef DEBUG_CORE
std::printf("%04x: ld H A\n", _pc.word);
#endif
  _current_opcode = 0x67;
  exec_instruction([&] () { instr_ld(_hl.high, _af.high); }, 4);
  break;
case 0x68:
#ifdef DEBUG_CORE
std::printf("%04x: ld L B\n", _pc.word);
#endif
  _current_opcode = 0x68;
  exec_instruction([&] () { instr_ld(_hl.low, _bc.high); }, 4);
  break;
case 0x69:
#ifdef DEBUG_CORE
std::printf("%04x: ld L C\n", _pc.word);
#endif
  _current_opcode = 0x69;
  exec_instruction([&] () { instr_ld(_hl.low, _bc.low); }, 4);
  break;
case 0x6a:
#ifdef DEBUG_CORE
std::printf("%04x: ld L D\n", _pc.word);
#endif
  _current_opcode = 0x6a;
  exec_instruction([&] () { instr_ld(_hl.low, _de.high); }, 4);
  break;
case 0x6b:
#ifdef DEBUG_CORE
std::printf("%04x: ld L E\n", _pc.word);
#endif
  _current_opcode = 0x6b;
  exec_instruction([&] () { instr_ld(_hl.low, _de.low); }, 4);
  break;
case 0x6c:
#ifdef DEBUG_CORE
std::printf("%04x: ld L H\n", _pc.word);
#endif
  _current_opcode = 0x6c;
  exec_instruction([&] () { instr_ld(_hl.low, _hl.high); }, 4);
  break;
case 0x6d:
#ifdef DEBUG_CORE
std::printf("%04x: ld L L\n", _pc.word);
#endif
  _current_opcode = 0x6d;
  exec_instruction([&] () { instr_ld(_hl.low, _hl.low); }, 4);
  break;
case 0x6e:
#ifdef DEBUG_CORE
std::printf("%04x: ld L (HL)\n", _pc.word);
#endif
  _current_opcode = 0x6e;
  exec_instruction([&] () { instr_ld(_hl.low, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x6f:
#ifdef DEBUG_CORE
std::printf("%04x: ld L A\n", _pc.word);
#endif
  _current_opcode = 0x6f;
  exec_instruction([&] () { instr_ld(_hl.low, _af.high); }, 4);
  break;
case 0x70:
#ifdef DEBUG_CORE
std::printf("%04x: ld (HL) B\n", _pc.word);
#endif
  _current_opcode = 0x70;
  exec_instruction([&] (Byte &v) { instr_ld(v, _bc.high); }, _hl.word, 8);
  break;
case 0x71:
#ifdef DEBUG_CORE
std::printf("%04x: ld (HL) C\n", _pc.word);
#endif
  _current_opcode = 0x71;
  exec_instruction([&] (Byte &v) { instr_ld(v, _bc.low); }, _hl.word, 8);
  break;
case 0x72:
#ifdef DEBUG_CORE
std::printf("%04x: ld (HL) D\n", _pc.word);
#endif
  _current_opcode = 0x72;
  exec_instruction([&] (Byte &v) { instr_ld(v, _de.high); }, _hl.word, 8);
  break;
case 0x73:
#ifdef DEBUG_CORE
std::printf("%04x: ld (HL) E\n", _pc.word);
#endif
  _current_opcode = 0x73;
  exec_instruction([&] (Byte &v) { instr_ld(v, _de.low); }, _hl.word, 8);
  break;
case 0x74:
#ifdef DEBUG_CORE
std::printf("%04x: ld (HL) H\n", _pc.word);
#endif
  _current_opcode = 0x74;
  exec_instruction([&] (Byte &v) { instr_ld(v, _hl.high); }, _hl.word, 8);
  break;
case 0x75:
#ifdef DEBUG_CORE
std::printf("%04x: ld (HL) L\n", _pc.word);
#endif
  _current_opcode = 0x75;
  exec_instruction([&] (Byte &v) { instr_ld(v, _hl.low); }, _hl.word, 8);
  break;
case 0x76:
#ifdef DEBUG_CORE
std::printf("%04x: halt\n", _pc.word);
#endif
  _current_opcode = 0x76;
  exec_instruction([&] () { instr_halt(); }, 4);
  break;
case 0x77:
#ifdef DEBUG_CORE
std::printf("%04x: ld (HL) A\n", _pc.word);
#endif
  _current_opcode = 0x77;
  exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, _hl.word, 8);
  break;
case 0x78:
#ifdef DEBUG_CORE
std::printf("%04x: ld A B\n", _pc.word);
#endif
  _current_opcode = 0x78;
  exec_instruction([&] () { instr_ld(_af.high, _bc.high); }, 4);
  break;
case 0x79:
#ifdef DEBUG_CORE
std::printf("%04x: ld A C\n", _pc.word);
#endif
  _current_opcode = 0x79;
  exec_instruction([&] () { instr_ld(_af.high, _bc.low); }, 4);
  break;
case 0x7a:
#ifdef DEBUG_CORE
std::printf("%04x: ld A D\n", _pc.word);
#endif
  _current_opcode = 0x7a;
  exec_instruction([&] () { instr_ld(_af.high, _de.high); }, 4);
  break;
case 0x7b:
#ifdef DEBUG_CORE
std::printf("%04x: ld A E\n", _pc.word);
#endif
  _current_opcode = 0x7b;
  exec_instruction([&] () { instr_ld(_af.high, _de.low); }, 4);
  break;
case 0x7c:
#ifdef DEBUG_CORE
std::printf("%04x: ld A H\n", _pc.word);
#endif
  _current_opcode = 0x7c;
  exec_instruction([&] () { instr_ld(_af.high, _hl.high); }, 4);
  break;
case 0x7d:
#ifdef DEBUG_CORE
std::printf("%04x: ld A L\n", _pc.word);
#endif
  _current_opcode = 0x7d;
  exec_instruction([&] () { instr_ld(_af.high, _hl.low); }, 4);
  break;
case 0x7e:
#ifdef DEBUG_CORE
std::printf("%04x: ld A (HL)\n", _pc.word);
#endif
  _current_opcode = 0x7e;
  exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x7f:
#ifdef DEBUG_CORE
std::printf("%04x: ld A A\n", _pc.word);
#endif
  _current_opcode = 0x7f;
  exec_instruction([&] () { instr_ld(_af.high, _af.high); }, 4);
  break;
case 0x80:
#ifdef DEBUG_CORE
std::printf("%04x: add A B\n", _pc.word);
#endif
  _current_opcode = 0x80;
  exec_instruction([&] () { instr_add(_af.high, _bc.high); }, 4);
  break;
case 0x81:
#ifdef DEBUG_CORE
std::printf("%04x: add A C\n", _pc.word);
#endif
  _current_opcode = 0x81;
  exec_instruction([&] () { instr_add(_af.high, _bc.low); }, 4);
  break;
case 0x82:
#ifdef DEBUG_CORE
std::printf("%04x: add A D\n", _pc.word);
#endif
  _current_opcode = 0x82;
  exec_instruction([&] () { instr_add(_af.high, _de.high); }, 4);
  break;
case 0x83:
#ifdef DEBUG_CORE
std::printf("%04x: add A E\n", _pc.word);
#endif
  _current_opcode = 0x83;
  exec_instruction([&] () { instr_add(_af.high, _de.low); }, 4);
  break;
case 0x84:
#ifdef DEBUG_CORE
std::printf("%04x: add A H\n", _pc.word);
#endif
  _current_opcode = 0x84;
  exec_instruction([&] () { instr_add(_af.high, _hl.high); }, 4);
  break;
case 0x85:
#ifdef DEBUG_CORE
std::printf("%04x: add A L\n", _pc.word);
#endif
  _current_opcode = 0x85;
  exec_instruction([&] () { instr_add(_af.high, _hl.low); }, 4);
  break;
case 0x86:
#ifdef DEBUG_CORE
std::printf("%04x: add A (HL)\n", _pc.word);
#endif
  _current_opcode = 0x86;
  exec_instruction([&] () { instr_add(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x87:
#ifdef DEBUG_CORE
std::printf("%04x: add A A\n", _pc.word);
#endif
  _current_opcode = 0x87;
  exec_instruction([&] () { instr_add(_af.high, _af.high); }, 4);
  break;
case 0x88:
#ifdef DEBUG_CORE
std::printf("%04x: adc A B\n", _pc.word);
#endif
  _current_opcode = 0x88;
  exec_instruction([&] () { instr_adc(_af.high, _bc.high); }, 4);
  break;
case 0x89:
#ifdef DEBUG_CORE
std::printf("%04x: adc A C\n", _pc.word);
#endif
  _current_opcode = 0x89;
  exec_instruction([&] () { instr_adc(_af.high, _bc.low); }, 4);
  break;
case 0x8a:
#ifdef DEBUG_CORE
std::printf("%04x: adc A D\n", _pc.word);
#endif
  _current_opcode = 0x8a;
  exec_instruction([&] () { instr_adc(_af.high, _de.high); }, 4);
  break;
case 0x8b:
#ifdef DEBUG_CORE
std::printf("%04x: adc A E\n", _pc.word);
#endif
  _current_opcode = 0x8b;
  exec_instruction([&] () { instr_adc(_af.high, _de.low); }, 4);
  break;
case 0x8c:
#ifdef DEBUG_CORE
std::printf("%04x: adc A H\n", _pc.word);
#endif
  _current_opcode = 0x8c;
  exec_instruction([&] () { instr_adc(_af.high, _hl.high); }, 4);
  break;
case 0x8d:
#ifdef DEBUG_CORE
std::printf("%04x: adc A L\n", _pc.word);
#endif
  _current_opcode = 0x8d;
  exec_instruction([&] () { instr_adc(_af.high, _hl.low); }, 4);
  break;
case 0x8e:
#ifdef DEBUG_CORE
std::printf("%04x: adc A (HL)\n", _pc.word);
#endif
  _current_opcode = 0x8e;
  exec_instruction([&] () { instr_adc(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x8f:
#ifdef DEBUG_CORE
std::printf("%04x: adc A A\n", _pc.word);
#endif
  _current_opcode = 0x8f;
  exec_instruction([&] () { instr_adc(_af.high, _af.high); }, 4);
  break;
case 0x90:
#ifdef DEBUG_CORE
std::printf("%04x: sub B\n", _pc.word);
#endif
  _current_opcode = 0x90;
  exec_instruction([&] () { instr_sub(_af.high, _bc.high); }, 4);
  break;
case 0x91:
#ifdef DEBUG_CORE
std::printf("%04x: sub C\n", _pc.word);
#endif
  _current_opcode = 0x91;
  exec_instruction([&] () { instr_sub(_af.high, _bc.low); }, 4);
  break;
case 0x92:
#ifdef DEBUG_CORE
std::printf("%04x: sub D\n", _pc.word);
#endif
  _current_opcode = 0x92;
  exec_instruction([&] () { instr_sub(_af.high, _de.high); }, 4);
  break;
case 0x93:
#ifdef DEBUG_CORE
std::printf("%04x: sub E\n", _pc.word);
#endif
  _current_opcode = 0x93;
  exec_instruction([&] () { instr_sub(_af.high, _de.low); }, 4);
  break;
case 0x94:
#ifdef DEBUG_CORE
std::printf("%04x: sub H\n", _pc.word);
#endif
  _current_opcode = 0x94;
  exec_instruction([&] () { instr_sub(_af.high, _hl.high); }, 4);
  break;
case 0x95:
#ifdef DEBUG_CORE
std::printf("%04x: sub L\n", _pc.word);
#endif
  _current_opcode = 0x95;
  exec_instruction([&] () { instr_sub(_af.high, _hl.low); }, 4);
  break;
case 0x96:
#ifdef DEBUG_CORE
std::printf("%04x: sub (HL)\n", _pc.word);
#endif
  _current_opcode = 0x96;
  exec_instruction([&] () { instr_sub(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x97:
#ifdef DEBUG_CORE
std::printf("%04x: sub A\n", _pc.word);
#endif
  _current_opcode = 0x97;
  exec_instruction([&] () { instr_sub(_af.high, _af.high); }, 4);
  break;
case 0x98:
#ifdef DEBUG_CORE
std::printf("%04x: sbc A B\n", _pc.word);
#endif
  _current_opcode = 0x98;
  exec_instruction([&] () { instr_sbc(_af.high, _bc.high); }, 4);
  break;
case 0x99:
#ifdef DEBUG_CORE
std::printf("%04x: sbc A C\n", _pc.word);
#endif
  _current_opcode = 0x99;
  exec_instruction([&] () { instr_sbc(_af.high, _bc.low); }, 4);
  break;
case 0x9a:
#ifdef DEBUG_CORE
std::printf("%04x: sbc A D\n", _pc.word);
#endif
  _current_opcode = 0x9a;
  exec_instruction([&] () { instr_sbc(_af.high, _de.high); }, 4);
  break;
case 0x9b:
#ifdef DEBUG_CORE
std::printf("%04x: sbc A E\n", _pc.word);
#endif
  _current_opcode = 0x9b;
  exec_instruction([&] () { instr_sbc(_af.high, _de.low); }, 4);
  break;
case 0x9c:
#ifdef DEBUG_CORE
std::printf("%04x: sbc A H\n", _pc.word);
#endif
  _current_opcode = 0x9c;
  exec_instruction([&] () { instr_sbc(_af.high, _hl.high); }, 4);
  break;
case 0x9d:
#ifdef DEBUG_CORE
std::printf("%04x: sbc A L\n", _pc.word);
#endif
  _current_opcode = 0x9d;
  exec_instruction([&] () { instr_sbc(_af.high, _hl.low); }, 4);
  break;
case 0x9e:
#ifdef DEBUG_CORE
std::printf("%04x: sbc A (HL)\n", _pc.word);
#endif
  _current_opcode = 0x9e;
  exec_instruction([&] () { instr_sbc(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x9f:
#ifdef DEBUG_CORE
std::printf("%04x: sbc A A\n", _pc.word);
#endif
  _current_opcode = 0x9f;
  exec_instruction([&] () { instr_sbc(_af.high, _af.high); }, 4);
  break;
case 0xa0:
#ifdef DEBUG_CORE
std::printf("%04x: and B\n", _pc.word);
#endif
  _current_opcode = 0xa0;
  exec_instruction([&] () { instr_and(_af.high, _bc.high); }, 4);
  break;
case 0xa1:
#ifdef DEBUG_CORE
std::printf("%04x: and C\n", _pc.word);
#endif
  _current_opcode = 0xa1;
  exec_instruction([&] () { instr_and(_af.high, _bc.low); }, 4);
  break;
case 0xa2:
#ifdef DEBUG_CORE
std::printf("%04x: and D\n", _pc.word);
#endif
  _current_opcode = 0xa2;
  exec_instruction([&] () { instr_and(_af.high, _de.high); }, 4);
  break;
case 0xa3:
#ifdef DEBUG_CORE
std::printf("%04x: and E\n", _pc.word);
#endif
  _current_opcode = 0xa3;
  exec_instruction([&] () { instr_and(_af.high, _de.low); }, 4);
  break;
case 0xa4:
#ifdef DEBUG_CORE
std::printf("%04x: and H\n", _pc.word);
#endif
  _current_opcode = 0xa4;
  exec_instruction([&] () { instr_and(_af.high, _hl.high); }, 4);
  break;
case 0xa5:
#ifdef DEBUG_CORE
std::printf("%04x: and L\n", _pc.word);
#endif
  _current_opcode = 0xa5;
  exec_instruction([&] () { instr_and(_af.high, _hl.low); }, 4);
  break;
case 0xa6:
#ifdef DEBUG_CORE
std::printf("%04x: and (HL)\n", _pc.word);
#endif
  _current_opcode = 0xa6;
  exec_instruction([&] () { instr_and(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0xa7:
#ifdef DEBUG_CORE
std::printf("%04x: and A\n", _pc.word);
#endif
  _current_opcode = 0xa7;
  exec_instruction([&] () { instr_and(_af.high, _af.high); }, 4);
  break;
case 0xa8:
#ifdef DEBUG_CORE
std::printf("%04x: xor B\n", _pc.word);
#endif
  _current_opcode = 0xa8;
  exec_instruction([&] () { instr_xor(_af.high, _bc.high); }, 4);
  break;
case 0xa9:
#ifdef DEBUG_CORE
std::printf("%04x: xor C\n", _pc.word);
#endif
  _current_opcode = 0xa9;
  exec_instruction([&] () { instr_xor(_af.high, _bc.low); }, 4);
  break;
case 0xaa:
#ifdef DEBUG_CORE
std::printf("%04x: xor D\n", _pc.word);
#endif
  _current_opcode = 0xaa;
  exec_instruction([&] () { instr_xor(_af.high, _de.high); }, 4);
  break;
case 0xab:
#ifdef DEBUG_CORE
std::printf("%04x: xor E\n", _pc.word);
#endif
  _current_opcode = 0xab;
  exec_instruction([&] () { instr_xor(_af.high, _de.low); }, 4);
  break;
case 0xac:
#ifdef DEBUG_CORE
std::printf("%04x: xor H\n", _pc.word);
#endif
  _current_opcode = 0xac;
  exec_instruction([&] () { instr_xor(_af.high, _hl.high); }, 4);
  break;
case 0xad:
#ifdef DEBUG_CORE
std::printf("%04x: xor L\n", _pc.word);
#endif
  _current_opcode = 0xad;
  exec_instruction([&] () { instr_xor(_af.high, _hl.low); }, 4);
  break;
case 0xae:
#ifdef DEBUG_CORE
std::printf("%04x: xor (HL)\n", _pc.word);
#endif
  _current_opcode = 0xae;
  exec_instruction([&] () { instr_xor(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0xaf:
#ifdef DEBUG_CORE
std::printf("%04x: xor A\n", _pc.word);
#endif
  _current_opcode = 0xaf;
  exec_instruction([&] () { instr_xor(_af.high, _af.high); }, 4);
  break;
case 0xb0:
#ifdef DEBUG_CORE
std::printf("%04x: or B\n", _pc.word);
#endif
  _current_opcode = 0xb0;
  exec_instruction([&] () { instr_or(_af.high, _bc.high); }, 4);
  break;
case 0xb1:
#ifdef DEBUG_CORE
std::printf("%04x: or C\n", _pc.word);
#endif
  _current_opcode = 0xb1;
  exec_instruction([&] () { instr_or(_af.high, _bc.low); }, 4);
  break;
case 0xb2:
#ifdef DEBUG_CORE
std::printf("%04x: or D\n", _pc.word);
#endif
  _current_opcode = 0xb2;
  exec_instruction([&] () { instr_or(_af.high, _de.high); }, 4);
  break;
case 0xb3:
#ifdef DEBUG_CORE
std::printf("%04x: or E\n", _pc.word);
#endif
  _current_opcode = 0xb3;
  exec_instruction([&] () { instr_or(_af.high, _de.low); }, 4);
  break;
case 0xb4:
#ifdef DEBUG_CORE
std::printf("%04x: or H\n", _pc.word);
#endif
  _current_opcode = 0xb4;
  exec_instruction([&] () { instr_or(_af.high, _hl.high); }, 4);
  break;
case 0xb5:
#ifdef DEBUG_CORE
std::printf("%04x: or L\n", _pc.word);
#endif
  _current_opcode = 0xb5;
  exec_instruction([&] () { instr_or(_af.high, _hl.low); }, 4);
  break;
case 0xb6:
#ifdef DEBUG_CORE
std::printf("%04x: or (HL)\n", _pc.word);
#endif
  _current_opcode = 0xb6;
  exec_instruction([&] () { instr_or(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0xb7:
#ifdef DEBUG_CORE
std::printf("%04x: or A\n", _pc.word);
#endif
  _current_opcode = 0xb7;
  exec_instruction([&] () { instr_or(_af.high, _af.high); }, 4);
  break;
case 0xb8:
#ifdef DEBUG_CORE
std::printf("%04x: cp B\n", _pc.word);
#endif
  _current_opcode = 0xb8;
  exec_instruction([&] () { instr_cp(_af.high, _bc.high); }, 4);
  break;
case 0xb9:
#ifdef DEBUG_CORE
std::printf("%04x: cp C\n", _pc.word);
#endif
  _current_opcode = 0xb9;
  exec_instruction([&] () { instr_cp(_af.high, _bc.low); }, 4);
  break;
case 0xba:
#ifdef DEBUG_CORE
std::printf("%04x: cp D\n", _pc.word);
#endif
  _current_opcode = 0xba;
  exec_instruction([&] () { instr_cp(_af.high, _de.high); }, 4);
  break;
case 0xbb:
#ifdef DEBUG_CORE
std::printf("%04x: cp E\n", _pc.word);
#endif
  _current_opcode = 0xbb;
  exec_instruction([&] () { instr_cp(_af.high, _de.low); }, 4);
  break;
case 0xbc:
#ifdef DEBUG_CORE
std::printf("%04x: cp H\n", _pc.word);
#endif
  _current_opcode = 0xbc;
  exec_instruction([&] () { instr_cp(_af.high, _hl.high); }, 4);
  break;
case 0xbd:
#ifdef DEBUG_CORE
std::printf("%04x: cp L\n", _pc.word);
#endif
  _current_opcode = 0xbd;
  exec_instruction([&] () { instr_cp(_af.high, _hl.low); }, 4);
  break;
case 0xbe:
#ifdef DEBUG_CORE
std::printf("%04x: cp (HL)\n", _pc.word);
#endif
  _current_opcode = 0xbe;
  exec_instruction([&] () { instr_cp(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0xbf:
#ifdef DEBUG_CORE
std::printf("%04x: cp A\n", _pc.word);
#endif
  _current_opcode = 0xbf;
  exec_instruction([&] () { instr_cp(_af.high, _af.high); }, 4);
  break;
case 0xc0:
#ifdef DEBUG_CORE
std::printf("%04x: ret NZ\n", _pc.word);
#endif
  _current_opcode = 0xc0;
  exec_instruction([&] () { instr_ret(JumpCondition::NonZero); }, 20, 8);
  break;
case 0xc1:
#ifdef DEBUG_CORE
std::printf("%04x: pop BC\n", _pc.word);
#endif
  _current_opcode = 0xc1;
  exec_instruction([&] () { instr_pop(_bc.word); }, 12);
  break;
case 0xc2:
#ifdef DEBUG_CORE
std::printf("%04x: jp NZ a16\n", _pc.word);
#endif
  _current_opcode = 0xc2;
  exec_instruction([&] () { instr_jp(JumpCondition::NonZero, fetch_word()); }, 16, 12);
  break;
case 0xc3:
#ifdef DEBUG_CORE
std::printf("%04x: jp a16\n", _pc.word);
#endif
  _current_opcode = 0xc3;
  exec_instruction([&] () { instr_jp(fetch_word()); }, 16);
  break;
case 0xc4:
#ifdef DEBUG_CORE
std::printf("%04x: call NZ a16\n", _pc.word);
#endif
  _current_opcode = 0xc4;
  exec_instruction([&] () { instr_call(JumpCondition::NonZero, fetch_word()); }, 24, 12);
  break;
case 0xc5:
#ifdef DEBUG_CORE
std::printf("%04x: push BC\n", _pc.word);
#endif
  _current_opcode = 0xc5;
  exec_instruction([&] () { instr_push(_bc.word); }, 16);
  break;
case 0xc6:
#ifdef DEBUG_CORE
std::printf("%04x: add A d8\n", _pc.word);
#endif
  _current_opcode = 0xc6;
  exec_instruction([&] () { instr_add(_af.high, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0xc7:
#ifdef DEBUG_CORE
std::printf("%04x: rst 00H\n", _pc.word);
#endif
  _current_opcode = 0xc7;
  exec_instruction([&] () { instr_rst(0x00); }, 16);
  break;
case 0xc8:
#ifdef DEBUG_CORE
std::printf("%04x: ret Z\n", _pc.word);
#endif
  _current_opcode = 0xc8;
  exec_instruction([&] () { instr_ret(JumpCondition::Zero); }, 20, 8);
  break;
case 0xc9:
#ifdef DEBUG_CORE
std::printf("%04x: ret\n", _pc.word);
#endif
  _current_opcode = 0xc9;
  exec_instruction([&] () { instr_ret(); }, 16);
  break;
case 0xca:
#ifdef DEBUG_CORE
std::printf("%04x: jp Z a16\n", _pc.word);
#endif
  _current_opcode = 0xca;
  exec_instruction([&] () { instr_jp(JumpCondition::Zero, fetch_word()); }, 16, 12);
  break;
case 0xcc:
#ifdef DEBUG_CORE
std::printf("%04x: call Z a16\n", _pc.word);
#endif
  _current_opcode = 0xcc;
  exec_instruction([&] () { instr_call(JumpCondition::Zero, fetch_word()); }, 24, 12);
  break;
case 0xcd:
#ifdef DEBUG_CORE
std::printf("%04x: call a16\n", _pc.word);
#endif
  _current_opcode = 0xcd;
  exec_instruction([&] () { instr_call(fetch_word()); }, 24);
  break;
case 0xce:
#ifdef DEBUG_CORE
std::printf("%04x: adc A d8\n", _pc.word);
#endif
  _current_opcode = 0xce;
  exec_instruction([&] () { instr_adc(_af.high, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0xcf:
#ifdef DEBUG_CORE
std::printf("%04x: rst 08H\n", _pc.word);
#endif
  _current_opcode = 0xcf;
  exec_instruction([&] () { instr_rst(0x08); }, 16);
  break;
case 0xd0:
#ifdef DEBUG_CORE
std::printf("%04x: ret NC\n", _pc.word);
#endif
  _current_opcode = 0xd0;
  exec_instruction([&] () { instr_ret(JumpCondition::NonCarry); }, 20, 8);
  break;
case 0xd1:
#ifdef DEBUG_CORE
std::printf("%04x: pop DE\n", _pc.word);
#endif
  _current_opcode = 0xd1;
  exec_instruction([&] () { instr_pop(_de.word); }, 12);
  break;
case 0xd2:
#ifdef DEBUG_CORE
std::printf("%04x: jp NC a16\n", _pc.word);
#endif
  _current_opcode = 0xd2;
  exec_instruction([&] () { instr_jp(JumpCondition::NonCarry, fetch_word()); }, 16, 12);
  break;
case 0xd4:
#ifdef DEBUG_CORE
std::printf("%04x: call NC a16\n", _pc.word);
#endif
  _current_opcode = 0xd4;
  exec_instruction([&] () { instr_call(JumpCondition::NonCarry, fetch_word()); }, 24, 12);
  break;
case 0xd5:
#ifdef DEBUG_CORE
std::printf("%04x: push DE\n", _pc.word);
#endif
  _current_opcode = 0xd5;
  exec_instruction([&] () { instr_push(_de.word); }, 16);
  break;
case 0xd6:
#ifdef DEBUG_CORE
std::printf("%04x: sub d8\n", _pc.word);
#endif
  _current_opcode = 0xd6;
  exec_instruction([&] () { instr_sub(_af.high, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0xd7:
#ifdef DEBUG_CORE
std::printf("%04x: rst 10H\n", _pc.word);
#endif
  _current_opcode = 0xd7;
  exec_instruction([&] () { instr_rst(0x10); }, 16);
  break;
case 0xd8:
#ifdef DEBUG_CORE
std::printf("%04x: ret C\n", _pc.word);
#endif
  _current_opcode = 0xd8;
  exec_instruction([&] () { instr_ret(JumpCondition::Carry); }, 20, 8);
  break;
case 0xd9:
#ifdef DEBUG_CORE
std::printf("%04x: reti\n", _pc.word);
#endif
  _current_opcode = 0xd9;
  exec_instruction([&] () { instr_reti(); }, 16);
  break;
case 0xda:
#ifdef DEBUG_CORE
std::printf("%04x: jp C a16\n", _pc.word);
#endif
  _current_opcode = 0xda;
  exec_instruction([&] () { instr_jp(JumpCondition::Carry, fetch_word()); }, 16, 12);
  break;
case 0xdc:
#ifdef DEBUG_CORE
std::printf("%04x: call C a16\n", _pc.word);
#endif
  _current_opcode = 0xdc;
  exec_instruction([&] () { instr_call(JumpCondition::Carry, fetch_word()); }, 24, 12);
  break;
case 0xde:
#ifdef DEBUG_CORE
std::printf("%04x: sbc A d8\n", _pc.word);
#endif
  _current_opcode = 0xde;
  exec_instruction([&] () { instr_sbc(_af.high, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0xdf:
#ifdef DEBUG_CORE
std::printf("%04x: rst 18H\n", _pc.word);
#endif
  _current_opcode = 0xdf;
  exec_instruction([&] () { instr_rst(0x18); }, 16);
  break;
case 0xe0:
#ifdef DEBUG_CORE
std::printf("%04x: ldh (a8) A\n", _pc.word);
#endif
  _current_opcode = 0xe0;
  exec_instruction([&] (Byte &v) { instr_ldh(v, _af.high); }, 0xFF00 + _components.mem_bus->read<Byte>(addr++), 12);
  break;
case 0xe1:
#ifdef DEBUG_CORE
std::printf("%04x: pop HL\n", _pc.word);
#endif
  _current_opcode = 0xe1;
  exec_instruction([&] () { instr_pop(_hl.word); }, 12);
  break;
case 0xe2:
#ifdef DEBUG_CORE
std::printf("%04x: ld (C) A\n", _pc.word);
#endif
  _current_opcode = 0xe2;
  exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, 0xFF00 + _bc.low, 8);
  break;
case 0xe5:
#ifdef DEBUG_CORE
std::printf("%04x: push HL\n", _pc.word);
#endif
  _current_opcode = 0xe5;
  exec_instruction([&] () { instr_push(_hl.word); }, 16);
  break;
case 0xe6:
#ifdef DEBUG_CORE
std::printf("%04x: and d8\n", _pc.word);
#endif
  _current_opcode = 0xe6;
  exec_instruction([&] () { instr_and(_af.high, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0xe7:
#ifdef DEBUG_CORE
std::printf("%04x: rst 20H\n", _pc.word);
#endif
  _current_opcode = 0xe7;
  exec_instruction([&] () { instr_rst(0x20); }, 16);
  break;
case 0xe8:
#ifdef DEBUG_CORE
std::printf("%04x: add SP r8\n", _pc.word);
#endif
  _current_opcode = 0xe8;
  exec_instruction([&] () { instr_add(_sp.word, _components.mem_bus->read<Byte>(addr++)); }, 16);
  break;
case 0xe9:
#ifdef DEBUG_CORE
std::printf("%04x: jp HL\n", _pc.word);
#endif
  _current_opcode = 0xe9;
  exec_instruction([&] () { instr_jp(_hl.word); }, 4);
  break;
case 0xea:
#ifdef DEBUG_CORE
std::printf("%04x: ld (a16) A\n", _pc.word);
#endif
  _current_opcode = 0xea;
  exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, fetch_word(), 16);
  break;
case 0xee:
#ifdef DEBUG_CORE
std::printf("%04x: xor d8\n", _pc.word);
#endif
  _current_opcode = 0xee;
  exec_instruction([&] () { instr_xor(_af.high, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0xef:
#ifdef DEBUG_CORE
std::printf("%04x: rst 28H\n", _pc.word);
#endif
  _current_opcode = 0xef;
  exec_instruction([&] () { instr_rst(0x28); }, 16);
  break;
case 0xf0:
#ifdef DEBUG_CORE
std::printf("%04x: ldh A (a8)\n", _pc.word);
#endif
  _current_opcode = 0xf0;
  exec_instruction([&] () { instr_ldh(_af.high, _components.mem_bus->read<Byte>(0xFF00 + _components.mem_bus->read<Byte>(addr++))); }, 12);
  break;
case 0xf1:
#ifdef DEBUG_CORE
std::printf("%04x: pop AF\n", _pc.word);
#endif
  _current_opcode = 0xf1;
  exec_instruction([&] () { instr_pop(_af.word); }, 12);
  break;
case 0xf2:
#ifdef DEBUG_CORE
std::printf("%04x: ld A (C)\n", _pc.word);
#endif
  _current_opcode = 0xf2;
  exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(0xFF00 + _bc.low)); }, 8);
  break;
case 0xf3:
#ifdef DEBUG_CORE
std::printf("%04x: di\n", _pc.word);
#endif
  _current_opcode = 0xf3;
  exec_instruction([&] () { instr_di(); }, 4);
  break;
case 0xf5:
#ifdef DEBUG_CORE
std::printf("%04x: push AF\n", _pc.word);
#endif
  _current_opcode = 0xf5;
  exec_instruction([&] () { instr_push(_af.word); }, 16);
  break;
case 0xf6:
#ifdef DEBUG_CORE
std::printf("%04x: or d8\n", _pc.word);
#endif
  _current_opcode = 0xf6;
  exec_instruction([&] () { instr_or(_af.high, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0xf7:
#ifdef DEBUG_CORE
std::printf("%04x: rst 30H\n", _pc.word);
#endif
  _current_opcode = 0xf7;
  exec_instruction([&] () { instr_rst(0x30); }, 16);
  break;
case 0xf8:
#ifdef DEBUG_CORE
std::printf("%04x: ldhl SP+r8\n", _pc.word);
#endif
  _current_opcode = 0xf8;
  exec_instruction([&] () { instr_ldhl(_components.mem_bus->read<Byte>(addr++)); }, 12);
  break;
case 0xf9:
#ifdef DEBUG_CORE
std::printf("%04x: ld SP HL\n", _pc.word);
#endif
  _current_opcode = 0xf9;
  exec_instruction([&] () { instr_ld(_sp.word, _hl.word); }, 8);
  break;
case 0xfa:
#ifdef DEBUG_CORE
std::printf("%04x: ld A (a16)\n", _pc.word);
#endif
  _current_opcode = 0xfa;
  exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(fetch_word())); }, 16);
  break;
case 0xfb:
#ifdef DEBUG_CORE
std::printf("%04x: ei\n", _pc.word);
#endif
  _current_opcode = 0xfb;
  exec_instruction([&] () { instr_ei(); }, 4);
  break;
case 0xfe:
#ifdef DEBUG_CORE
std::printf("%04x: cp d8\n", _pc.word);
#endif
  _current_opcode = 0xfe;
  exec_instruction([&] () { instr_cp(_af.high, _components.mem_bus->read<Byte>(addr++)); }, 8);
  break;
case 0xff:
#ifdef DEBUG_CORE
std::printf("%04x: rst 38H\n", _pc.word);
#endif
  _current_opcode = 0xff;
  exec_instruction([&] () { instr_rst(0x38); }, 16);
  break;
  case 0xCB:
switch (_components.mem_bus->read<Byte>(addr++)) {
case 0x0:
#ifdef DEBUG_CORE
std::printf("%04x: rlc B\n", _pc.word);
#endif
  _current_opcode = 0x0;
  exec_instruction([&] () { instr_rlc(_bc.high); }, 8);
  break;
case 0x1:
#ifdef DEBUG_CORE
std::printf("%04x: rlc C\n", _pc.word);
#endif
  _current_opcode = 0x1;
  exec_instruction([&] () { instr_rlc(_bc.low); }, 8);
  break;
case 0x2:
#ifdef DEBUG_CORE
std::printf("%04x: rlc D\n", _pc.word);
#endif
  _current_opcode = 0x2;
  exec_instruction([&] () { instr_rlc(_de.high); }, 8);
  break;
case 0x3:
#ifdef DEBUG_CORE
std::printf("%04x: rlc E\n", _pc.word);
#endif
  _current_opcode = 0x3;
  exec_instruction([&] () { instr_rlc(_de.low); }, 8);
  break;
case 0x4:
#ifdef DEBUG_CORE
std::printf("%04x: rlc H\n", _pc.word);
#endif
  _current_opcode = 0x4;
  exec_instruction([&] () { instr_rlc(_hl.high); }, 8);
  break;
case 0x5:
#ifdef DEBUG_CORE
std::printf("%04x: rlc L\n", _pc.word);
#endif
  _current_opcode = 0x5;
  exec_instruction([&] () { instr_rlc(_hl.low); }, 8);
  break;
case 0x6:
#ifdef DEBUG_CORE
std::printf("%04x: rlc (HL)\n", _pc.word);
#endif
  _current_opcode = 0x6;
  exec_instruction([&] (Byte &v) { instr_rlc(v); }, _hl.word, 16);
  break;
case 0x7:
#ifdef DEBUG_CORE
std::printf("%04x: rlc A\n", _pc.word);
#endif
  _current_opcode = 0x7;
  exec_instruction([&] () { instr_rlc(_af.high); }, 8);
  break;
case 0x8:
#ifdef DEBUG_CORE
std::printf("%04x: rrc B\n", _pc.word);
#endif
  _current_opcode = 0x8;
  exec_instruction([&] () { instr_rrc(_bc.high); }, 8);
  break;
case 0x9:
#ifdef DEBUG_CORE
std::printf("%04x: rrc C\n", _pc.word);
#endif
  _current_opcode = 0x9;
  exec_instruction([&] () { instr_rrc(_bc.low); }, 8);
  break;
case 0xa:
#ifdef DEBUG_CORE
std::printf("%04x: rrc D\n", _pc.word);
#endif
  _current_opcode = 0xa;
  exec_instruction([&] () { instr_rrc(_de.high); }, 8);
  break;
case 0xb:
#ifdef DEBUG_CORE
std::printf("%04x: rrc E\n", _pc.word);
#endif
  _current_opcode = 0xb;
  exec_instruction([&] () { instr_rrc(_de.low); }, 8);
  break;
case 0xc:
#ifdef DEBUG_CORE
std::printf("%04x: rrc H\n", _pc.word);
#endif
  _current_opcode = 0xc;
  exec_instruction([&] () { instr_rrc(_hl.high); }, 8);
  break;
case 0xd:
#ifdef DEBUG_CORE
std::printf("%04x: rrc L\n", _pc.word);
#endif
  _current_opcode = 0xd;
  exec_instruction([&] () { instr_rrc(_hl.low); }, 8);
  break;
case 0xe:
#ifdef DEBUG_CORE
std::printf("%04x: rrc (HL)\n", _pc.word);
#endif
  _current_opcode = 0xe;
  exec_instruction([&] (Byte &v) { instr_rrc(v); }, _hl.word, 16);
  break;
case 0xf:
#ifdef DEBUG_CORE
std::printf("%04x: rrc A\n", _pc.word);
#endif
  _current_opcode = 0xf;
  exec_instruction([&] () { instr_rrc(_af.high); }, 8);
  break;
case 0x10:
#ifdef DEBUG_CORE
std::printf("%04x: rl B\n", _pc.word);
#endif
  _current_opcode = 0x10;
  exec_instruction([&] () { instr_rl(_bc.high); }, 8);
  break;
case 0x11:
#ifdef DEBUG_CORE
std::printf("%04x: rl C\n", _pc.word);
#endif
  _current_opcode = 0x11;
  exec_instruction([&] () { instr_rl(_bc.low); }, 8);
  break;
case 0x12:
#ifdef DEBUG_CORE
std::printf("%04x: rl D\n", _pc.word);
#endif
  _current_opcode = 0x12;
  exec_instruction([&] () { instr_rl(_de.high); }, 8);
  break;
case 0x13:
#ifdef DEBUG_CORE
std::printf("%04x: rl E\n", _pc.word);
#endif
  _current_opcode = 0x13;
  exec_instruction([&] () { instr_rl(_de.low); }, 8);
  break;
case 0x14:
#ifdef DEBUG_CORE
std::printf("%04x: rl H\n", _pc.word);
#endif
  _current_opcode = 0x14;
  exec_instruction([&] () { instr_rl(_hl.high); }, 8);
  break;
case 0x15:
#ifdef DEBUG_CORE
std::printf("%04x: rl L\n", _pc.word);
#endif
  _current_opcode = 0x15;
  exec_instruction([&] () { instr_rl(_hl.low); }, 8);
  break;
case 0x16:
#ifdef DEBUG_CORE
std::printf("%04x: rl (HL)\n", _pc.word);
#endif
  _current_opcode = 0x16;
  exec_instruction([&] (Byte &v) { instr_rl(v); }, _hl.word, 16);
  break;
case 0x17:
#ifdef DEBUG_CORE
std::printf("%04x: rl A\n", _pc.word);
#endif
  _current_opcode = 0x17;
  exec_instruction([&] () { instr_rl(_af.high); }, 8);
  break;
case 0x18:
#ifdef DEBUG_CORE
std::printf("%04x: rr B\n", _pc.word);
#endif
  _current_opcode = 0x18;
  exec_instruction([&] () { instr_rr(_bc.high); }, 8);
  break;
case 0x19:
#ifdef DEBUG_CORE
std::printf("%04x: rr C\n", _pc.word);
#endif
  _current_opcode = 0x19;
  exec_instruction([&] () { instr_rr(_bc.low); }, 8);
  break;
case 0x1a:
#ifdef DEBUG_CORE
std::printf("%04x: rr D\n", _pc.word);
#endif
  _current_opcode = 0x1a;
  exec_instruction([&] () { instr_rr(_de.high); }, 8);
  break;
case 0x1b:
#ifdef DEBUG_CORE
std::printf("%04x: rr E\n", _pc.word);
#endif
  _current_opcode = 0x1b;
  exec_instruction([&] () { instr_rr(_de.low); }, 8);
  break;
case 0x1c:
#ifdef DEBUG_CORE
std::printf("%04x: rr H\n", _pc.word);
#endif
  _current_opcode = 0x1c;
  exec_instruction([&] () { instr_rr(_hl.high); }, 8);
  break;
case 0x1d:
#ifdef DEBUG_CORE
std::printf("%04x: rr L\n", _pc.word);
#endif
  _current_opcode = 0x1d;
  exec_instruction([&] () { instr_rr(_hl.low); }, 8);
  break;
case 0x1e:
#ifdef DEBUG_CORE
std::printf("%04x: rr (HL)\n", _pc.word);
#endif
  _current_opcode = 0x1e;
  exec_instruction([&] (Byte &v) { instr_rr(v); }, _hl.word, 16);
  break;
case 0x1f:
#ifdef DEBUG_CORE
std::printf("%04x: rr A\n", _pc.word);
#endif
  _current_opcode = 0x1f;
  exec_instruction([&] () { instr_rr(_af.high); }, 8);
  break;
case 0x20:
#ifdef DEBUG_CORE
std::printf("%04x: sla B\n", _pc.word);
#endif
  _current_opcode = 0x20;
  exec_instruction([&] () { instr_sla(_bc.high); }, 8);
  break;
case 0x21:
#ifdef DEBUG_CORE
std::printf("%04x: sla C\n", _pc.word);
#endif
  _current_opcode = 0x21;
  exec_instruction([&] () { instr_sla(_bc.low); }, 8);
  break;
case 0x22:
#ifdef DEBUG_CORE
std::printf("%04x: sla D\n", _pc.word);
#endif
  _current_opcode = 0x22;
  exec_instruction([&] () { instr_sla(_de.high); }, 8);
  break;
case 0x23:
#ifdef DEBUG_CORE
std::printf("%04x: sla E\n", _pc.word);
#endif
  _current_opcode = 0x23;
  exec_instruction([&] () { instr_sla(_de.low); }, 8);
  break;
case 0x24:
#ifdef DEBUG_CORE
std::printf("%04x: sla H\n", _pc.word);
#endif
  _current_opcode = 0x24;
  exec_instruction([&] () { instr_sla(_hl.high); }, 8);
  break;
case 0x25:
#ifdef DEBUG_CORE
std::printf("%04x: sla L\n", _pc.word);
#endif
  _current_opcode = 0x25;
  exec_instruction([&] () { instr_sla(_hl.low); }, 8);
  break;
case 0x26:
#ifdef DEBUG_CORE
std::printf("%04x: sla (HL)\n", _pc.word);
#endif
  _current_opcode = 0x26;
  exec_instruction([&] (Byte &v) { instr_sla(v); }, _hl.word, 16);
  break;
case 0x27:
#ifdef DEBUG_CORE
std::printf("%04x: sla A\n", _pc.word);
#endif
  _current_opcode = 0x27;
  exec_instruction([&] () { instr_sla(_af.high); }, 8);
  break;
case 0x28:
#ifdef DEBUG_CORE
std::printf("%04x: sra B\n", _pc.word);
#endif
  _current_opcode = 0x28;
  exec_instruction([&] () { instr_sra(_bc.high); }, 8);
  break;
case 0x29:
#ifdef DEBUG_CORE
std::printf("%04x: sra C\n", _pc.word);
#endif
  _current_opcode = 0x29;
  exec_instruction([&] () { instr_sra(_bc.low); }, 8);
  break;
case 0x2a:
#ifdef DEBUG_CORE
std::printf("%04x: sra D\n", _pc.word);
#endif
  _current_opcode = 0x2a;
  exec_instruction([&] () { instr_sra(_de.high); }, 8);
  break;
case 0x2b:
#ifdef DEBUG_CORE
std::printf("%04x: sra E\n", _pc.word);
#endif
  _current_opcode = 0x2b;
  exec_instruction([&] () { instr_sra(_de.low); }, 8);
  break;
case 0x2c:
#ifdef DEBUG_CORE
std::printf("%04x: sra H\n", _pc.word);
#endif
  _current_opcode = 0x2c;
  exec_instruction([&] () { instr_sra(_hl.high); }, 8);
  break;
case 0x2d:
#ifdef DEBUG_CORE
std::printf("%04x: sra L\n", _pc.word);
#endif
  _current_opcode = 0x2d;
  exec_instruction([&] () { instr_sra(_hl.low); }, 8);
  break;
case 0x2e:
#ifdef DEBUG_CORE
std::printf("%04x: sra (HL)\n", _pc.word);
#endif
  _current_opcode = 0x2e;
  exec_instruction([&] (Byte &v) { instr_sra(v); }, _hl.word, 16);
  break;
case 0x2f:
#ifdef DEBUG_CORE
std::printf("%04x: sra A\n", _pc.word);
#endif
  _current_opcode = 0x2f;
  exec_instruction([&] () { instr_sra(_af.high); }, 8);
  break;
case 0x30:
#ifdef DEBUG_CORE
std::printf("%04x: swap B\n", _pc.word);
#endif
  _current_opcode = 0x30;
  exec_instruction([&] () { instr_swap(_bc.high); }, 8);
  break;
case 0x31:
#ifdef DEBUG_CORE
std::printf("%04x: swap C\n", _pc.word);
#endif
  _current_opcode = 0x31;
  exec_instruction([&] () { instr_swap(_bc.low); }, 8);
  break;
case 0x32:
#ifdef DEBUG_CORE
std::printf("%04x: swap D\n", _pc.word);
#endif
  _current_opcode = 0x32;
  exec_instruction([&] () { instr_swap(_de.high); }, 8);
  break;
case 0x33:
#ifdef DEBUG_CORE
std::printf("%04x: swap E\n", _pc.word);
#endif
  _current_opcode = 0x33;
  exec_instruction([&] () { instr_swap(_de.low); }, 8);
  break;
case 0x34:
#ifdef DEBUG_CORE
std::printf("%04x: swap H\n", _pc.word);
#endif
  _current_opcode = 0x34;
  exec_instruction([&] () { instr_swap(_hl.high); }, 8);
  break;
case 0x35:
#ifdef DEBUG_CORE
std::printf("%04x: swap L\n", _pc.word);
#endif
  _current_opcode = 0x35;
  exec_instruction([&] () { instr_swap(_hl.low); }, 8);
  break;
case 0x36:
#ifdef DEBUG_CORE
std::printf("%04x: swap (HL)\n", _pc.word);
#endif
  _current_opcode = 0x36;
  exec_instruction([&] (Byte &v) { instr_swap(v); }, _hl.word, 16);
  break;
case 0x37:
#ifdef DEBUG_CORE
std::printf("%04x: swap A\n", _pc.word);
#endif
  _current_opcode = 0x37;
  exec_instruction([&] () { instr_swap(_af.high); }, 8);
  break;
case 0x38:
#ifdef DEBUG_CORE
std::printf("%04x: srl B\n", _pc.word);
#endif
  _current_opcode = 0x38;
  exec_instruction([&] () { instr_srl(_bc.high); }, 8);
  break;
case 0x39:
#ifdef DEBUG_CORE
std::printf("%04x: srl C\n", _pc.word);
#endif
  _current_opcode = 0x39;
  exec_instruction([&] () { instr_srl(_bc.low); }, 8);
  break;
case 0x3a:
#ifdef DEBUG_CORE
std::printf("%04x: srl D\n", _pc.word);
#endif
  _current_opcode = 0x3a;
  exec_instruction([&] () { instr_srl(_de.high); }, 8);
  break;
case 0x3b:
#ifdef DEBUG_CORE
std::printf("%04x: srl E\n", _pc.word);
#endif
  _current_opcode = 0x3b;
  exec_instruction([&] () { instr_srl(_de.low); }, 8);
  break;
case 0x3c:
#ifdef DEBUG_CORE
std::printf("%04x: srl H\n", _pc.word);
#endif
  _current_opcode = 0x3c;
  exec_instruction([&] () { instr_srl(_hl.high); }, 8);
  break;
case 0x3d:
#ifdef DEBUG_CORE
std::printf("%04x: srl L\n", _pc.word);
#endif
  _current_opcode = 0x3d;
  exec_instruction([&] () { instr_srl(_hl.low); }, 8);
  break;
case 0x3e:
#ifdef DEBUG_CORE
std::printf("%04x: srl (HL)\n", _pc.word);
#endif
  _current_opcode = 0x3e;
  exec_instruction([&] (Byte &v) { instr_srl(v); }, _hl.word, 16);
  break;
case 0x3f:
#ifdef DEBUG_CORE
std::printf("%04x: srl A\n", _pc.word);
#endif
  _current_opcode = 0x3f;
  exec_instruction([&] () { instr_srl(_af.high); }, 8);
  break;
case 0x40:
#ifdef DEBUG_CORE
std::printf("%04x: bit 0 B\n", _pc.word);
#endif
  _current_opcode = 0x40;
  exec_instruction([&] () { instr_bit(0, _bc.high); }, 8);
  break;
case 0x41:
#ifdef DEBUG_CORE
std::printf("%04x: bit 0 C\n", _pc.word);
#endif
  _current_opcode = 0x41;
  exec_instruction([&] () { instr_bit(0, _bc.low); }, 8);
  break;
case 0x42:
#ifdef DEBUG_CORE
std::printf("%04x: bit 0 D\n", _pc.word);
#endif
  _current_opcode = 0x42;
  exec_instruction([&] () { instr_bit(0, _de.high); }, 8);
  break;
case 0x43:
#ifdef DEBUG_CORE
std::printf("%04x: bit 0 E\n", _pc.word);
#endif
  _current_opcode = 0x43;
  exec_instruction([&] () { instr_bit(0, _de.low); }, 8);
  break;
case 0x44:
#ifdef DEBUG_CORE
std::printf("%04x: bit 0 H\n", _pc.word);
#endif
  _current_opcode = 0x44;
  exec_instruction([&] () { instr_bit(0, _hl.high); }, 8);
  break;
case 0x45:
#ifdef DEBUG_CORE
std::printf("%04x: bit 0 L\n", _pc.word);
#endif
  _current_opcode = 0x45;
  exec_instruction([&] () { instr_bit(0, _hl.low); }, 8);
  break;
case 0x46:
#ifdef DEBUG_CORE
std::printf("%04x: bit 0 (HL)\n", _pc.word);
#endif
  _current_opcode = 0x46;
  exec_instruction([&] (Byte &v) { instr_bit(0, v); }, _hl.word, 12);
  break;
case 0x47:
#ifdef DEBUG_CORE
std::printf("%04x: bit 0 A\n", _pc.word);
#endif
  _current_opcode = 0x47;
  exec_instruction([&] () { instr_bit(0, _af.high); }, 8);
  break;
case 0x48:
#ifdef DEBUG_CORE
std::printf("%04x: bit 1 B\n", _pc.word);
#endif
  _current_opcode = 0x48;
  exec_instruction([&] () { instr_bit(1, _bc.high); }, 8);
  break;
case 0x49:
#ifdef DEBUG_CORE
std::printf("%04x: bit 1 C\n", _pc.word);
#endif
  _current_opcode = 0x49;
  exec_instruction([&] () { instr_bit(1, _bc.low); }, 8);
  break;
case 0x4a:
#ifdef DEBUG_CORE
std::printf("%04x: bit 1 D\n", _pc.word);
#endif
  _current_opcode = 0x4a;
  exec_instruction([&] () { instr_bit(1, _de.high); }, 8);
  break;
case 0x4b:
#ifdef DEBUG_CORE
std::printf("%04x: bit 1 E\n", _pc.word);
#endif
  _current_opcode = 0x4b;
  exec_instruction([&] () { instr_bit(1, _de.low); }, 8);
  break;
case 0x4c:
#ifdef DEBUG_CORE
std::printf("%04x: bit 1 H\n", _pc.word);
#endif
  _current_opcode = 0x4c;
  exec_instruction([&] () { instr_bit(1, _hl.high); }, 8);
  break;
case 0x4d:
#ifdef DEBUG_CORE
std::printf("%04x: bit 1 L\n", _pc.word);
#endif
  _current_opcode = 0x4d;
  exec_instruction([&] () { instr_bit(1, _hl.low); }, 8);
  break;
case 0x4e:
#ifdef DEBUG_CORE
std::printf("%04x: bit 1 (HL)\n", _pc.word);
#endif
  _current_opcode = 0x4e;
  exec_instruction([&] (Byte &v) { instr_bit(1, v); }, _hl.word, 12);
  break;
case 0x4f:
#ifdef DEBUG_CORE
std::printf("%04x: bit 1 A\n", _pc.word);
#endif
  _current_opcode = 0x4f;
  exec_instruction([&] () { instr_bit(1, _af.high); }, 8);
  break;
case 0x50:
#ifdef DEBUG_CORE
std::printf("%04x: bit 2 B\n", _pc.word);
#endif
  _current_opcode = 0x50;
  exec_instruction([&] () { instr_bit(2, _bc.high); }, 8);
  break;
case 0x51:
#ifdef DEBUG_CORE
std::printf("%04x: bit 2 C\n", _pc.word);
#endif
  _current_opcode = 0x51;
  exec_instruction([&] () { instr_bit(2, _bc.low); }, 8);
  break;
case 0x52:
#ifdef DEBUG_CORE
std::printf("%04x: bit 2 D\n", _pc.word);
#endif
  _current_opcode = 0x52;
  exec_instruction([&] () { instr_bit(2, _de.high); }, 8);
  break;
case 0x53:
#ifdef DEBUG_CORE
std::printf("%04x: bit 2 E\n", _pc.word);
#endif
  _current_opcode = 0x53;
  exec_instruction([&] () { instr_bit(2, _de.low); }, 8);
  break;
case 0x54:
#ifdef DEBUG_CORE
std::printf("%04x: bit 2 H\n", _pc.word);
#endif
  _current_opcode = 0x54;
  exec_instruction([&] () { instr_bit(2, _hl.high); }, 8);
  break;
case 0x55:
#ifdef DEBUG_CORE
std::printf("%04x: bit 2 L\n", _pc.word);
#endif
  _current_opcode = 0x55;
  exec_instruction([&] () { instr_bit(2, _hl.low); }, 8);
  break;
case 0x56:
#ifdef DEBUG_CORE
std::printf("%04x: bit 2 (HL)\n", _pc.word);
#endif
  _current_opcode = 0x56;
  exec_instruction([&] (Byte &v) { instr_bit(2, v); }, _hl.word, 12);
  break;
case 0x57:
#ifdef DEBUG_CORE
std::printf("%04x: bit 2 A\n", _pc.word);
#endif
  _current_opcode = 0x57;
  exec_instruction([&] () { instr_bit(2, _af.high); }, 8);
  break;
case 0x58:
#ifdef DEBUG_CORE
std::printf("%04x: bit 3 B\n", _pc.word);
#endif
  _current_opcode = 0x58;
  exec_instruction([&] () { instr_bit(3, _bc.high); }, 8);
  break;
case 0x59:
#ifdef DEBUG_CORE
std::printf("%04x: bit 3 C\n", _pc.word);
#endif
  _current_opcode = 0x59;
  exec_instruction([&] () { instr_bit(3, _bc.low); }, 8);
  break;
case 0x5a:
#ifdef DEBUG_CORE
std::printf("%04x: bit 3 D\n", _pc.word);
#endif
  _current_opcode = 0x5a;
  exec_instruction([&] () { instr_bit(3, _de.high); }, 8);
  break;
case 0x5b:
#ifdef DEBUG_CORE
std::printf("%04x: bit 3 E\n", _pc.word);
#endif
  _current_opcode = 0x5b;
  exec_instruction([&] () { instr_bit(3, _de.low); }, 8);
  break;
case 0x5c:
#ifdef DEBUG_CORE
std::printf("%04x: bit 3 H\n", _pc.word);
#endif
  _current_opcode = 0x5c;
  exec_instruction([&] () { instr_bit(3, _hl.high); }, 8);
  break;
case 0x5d:
#ifdef DEBUG_CORE
std::printf("%04x: bit 3 L\n", _pc.word);
#endif
  _current_opcode = 0x5d;
  exec_instruction([&] () { instr_bit(3, _hl.low); }, 8);
  break;
case 0x5e:
#ifdef DEBUG_CORE
std::printf("%04x: bit 3 (HL)\n", _pc.word);
#endif
  _current_opcode = 0x5e;
  exec_instruction([&] (Byte &v) { instr_bit(3, v); }, _hl.word, 12);
  break;
case 0x5f:
#ifdef DEBUG_CORE
std::printf("%04x: bit 3 A\n", _pc.word);
#endif
  _current_opcode = 0x5f;
  exec_instruction([&] () { instr_bit(3, _af.high); }, 8);
  break;
case 0x60:
#ifdef DEBUG_CORE
std::printf("%04x: bit 4 B\n", _pc.word);
#endif
  _current_opcode = 0x60;
  exec_instruction([&] () { instr_bit(4, _bc.high); }, 8);
  break;
case 0x61:
#ifdef DEBUG_CORE
std::printf("%04x: bit 4 C\n", _pc.word);
#endif
  _current_opcode = 0x61;
  exec_instruction([&] () { instr_bit(4, _bc.low); }, 8);
  break;
case 0x62:
#ifdef DEBUG_CORE
std::printf("%04x: bit 4 D\n", _pc.word);
#endif
  _current_opcode = 0x62;
  exec_instruction([&] () { instr_bit(4, _de.high); }, 8);
  break;
case 0x63:
#ifdef DEBUG_CORE
std::printf("%04x: bit 4 E\n", _pc.word);
#endif
  _current_opcode = 0x63;
  exec_instruction([&] () { instr_bit(4, _de.low); }, 8);
  break;
case 0x64:
#ifdef DEBUG_CORE
std::printf("%04x: bit 4 H\n", _pc.word);
#endif
  _current_opcode = 0x64;
  exec_instruction([&] () { instr_bit(4, _hl.high); }, 8);
  break;
case 0x65:
#ifdef DEBUG_CORE
std::printf("%04x: bit 4 L\n", _pc.word);
#endif
  _current_opcode = 0x65;
  exec_instruction([&] () { instr_bit(4, _hl.low); }, 8);
  break;
case 0x66:
#ifdef DEBUG_CORE
std::printf("%04x: bit 4 (HL)\n", _pc.word);
#endif
  _current_opcode = 0x66;
  exec_instruction([&] (Byte &v) { instr_bit(4, v); }, _hl.word, 12);
  break;
case 0x67:
#ifdef DEBUG_CORE
std::printf("%04x: bit 4 A\n", _pc.word);
#endif
  _current_opcode = 0x67;
  exec_instruction([&] () { instr_bit(4, _af.high); }, 8);
  break;
case 0x68:
#ifdef DEBUG_CORE
std::printf("%04x: bit 5 B\n", _pc.word);
#endif
  _current_opcode = 0x68;
  exec_instruction([&] () { instr_bit(5, _bc.high); }, 8);
  break;
case 0x69:
#ifdef DEBUG_CORE
std::printf("%04x: bit 5 C\n", _pc.word);
#endif
  _current_opcode = 0x69;
  exec_instruction([&] () { instr_bit(5, _bc.low); }, 8);
  break;
case 0x6a:
#ifdef DEBUG_CORE
std::printf("%04x: bit 5 D\n", _pc.word);
#endif
  _current_opcode = 0x6a;
  exec_instruction([&] () { instr_bit(5, _de.high); }, 8);
  break;
case 0x6b:
#ifdef DEBUG_CORE
std::printf("%04x: bit 5 E\n", _pc.word);
#endif
  _current_opcode = 0x6b;
  exec_instruction([&] () { instr_bit(5, _de.low); }, 8);
  break;
case 0x6c:
#ifdef DEBUG_CORE
std::printf("%04x: bit 5 H\n", _pc.word);
#endif
  _current_opcode = 0x6c;
  exec_instruction([&] () { instr_bit(5, _hl.high); }, 8);
  break;
case 0x6d:
#ifdef DEBUG_CORE
std::printf("%04x: bit 5 L\n", _pc.word);
#endif
  _current_opcode = 0x6d;
  exec_instruction([&] () { instr_bit(5, _hl.low); }, 8);
  break;
case 0x6e:
#ifdef DEBUG_CORE
std::printf("%04x: bit 5 (HL)\n", _pc.word);
#endif
  _current_opcode = 0x6e;
  exec_instruction([&] (Byte &v) { instr_bit(5, v); }, _hl.word, 12);
  break;
case 0x6f:
#ifdef DEBUG_CORE
std::printf("%04x: bit 5 A\n", _pc.word);
#endif
  _current_opcode = 0x6f;
  exec_instruction([&] () { instr_bit(5, _af.high); }, 8);
  break;
case 0x70:
#ifdef DEBUG_CORE
std::printf("%04x: bit 6 B\n", _pc.word);
#endif
  _current_opcode = 0x70;
  exec_instruction([&] () { instr_bit(6, _bc.high); }, 8);
  break;
case 0x71:
#ifdef DEBUG_CORE
std::printf("%04x: bit 6 C\n", _pc.word);
#endif
  _current_opcode = 0x71;
  exec_instruction([&] () { instr_bit(6, _bc.low); }, 8);
  break;
case 0x72:
#ifdef DEBUG_CORE
std::printf("%04x: bit 6 D\n", _pc.word);
#endif
  _current_opcode = 0x72;
  exec_instruction([&] () { instr_bit(6, _de.high); }, 8);
  break;
case 0x73:
#ifdef DEBUG_CORE
std::printf("%04x: bit 6 E\n", _pc.word);
#endif
  _current_opcode = 0x73;
  exec_instruction([&] () { instr_bit(6, _de.low); }, 8);
  break;
case 0x74:
#ifdef DEBUG_CORE
std::printf("%04x: bit 6 H\n", _pc.word);
#endif
  _current_opcode = 0x74;
  exec_instruction([&] () { instr_bit(6, _hl.high); }, 8);
  break;
case 0x75:
#ifdef DEBUG_CORE
std::printf("%04x: bit 6 L\n", _pc.word);
#endif
  _current_opcode = 0x75;
  exec_instruction([&] () { instr_bit(6, _hl.low); }, 8);
  break;
case 0x76:
#ifdef DEBUG_CORE
std::printf("%04x: bit 6 (HL)\n", _pc.word);
#endif
  _current_opcode = 0x76;
  exec_instruction([&] (Byte &v) { instr_bit(6, v); }, _hl.word, 12);
  break;
case 0x77:
#ifdef DEBUG_CORE
std::printf("%04x: bit 6 A\n", _pc.word);
#endif
  _current_opcode = 0x77;
  exec_instruction([&] () { instr_bit(6, _af.high); }, 8);
  break;
case 0x78:
#ifdef DEBUG_CORE
std::printf("%04x: bit 7 B\n", _pc.word);
#endif
  _current_opcode = 0x78;
  exec_instruction([&] () { instr_bit(7, _bc.high); }, 8);
  break;
case 0x79:
#ifdef DEBUG_CORE
std::printf("%04x: bit 7 C\n", _pc.word);
#endif
  _current_opcode = 0x79;
  exec_instruction([&] () { instr_bit(7, _bc.low); }, 8);
  break;
case 0x7a:
#ifdef DEBUG_CORE
std::printf("%04x: bit 7 D\n", _pc.word);
#endif
  _current_opcode = 0x7a;
  exec_instruction([&] () { instr_bit(7, _de.high); }, 8);
  break;
case 0x7b:
#ifdef DEBUG_CORE
std::printf("%04x: bit 7 E\n", _pc.word);
#endif
  _current_opcode = 0x7b;
  exec_instruction([&] () { instr_bit(7, _de.low); }, 8);
  break;
case 0x7c:
#ifdef DEBUG_CORE
std::printf("%04x: bit 7 H\n", _pc.word);
#endif
  _current_opcode = 0x7c;
  exec_instruction([&] () { instr_bit(7, _hl.high); }, 8);
  break;
case 0x7d:
#ifdef DEBUG_CORE
std::printf("%04x: bit 7 L\n", _pc.word);
#endif
  _current_opcode = 0x7d;
  exec_instruction([&] () { instr_bit(7, _hl.low); }, 8);
  break;
case 0x7e:
#ifdef DEBUG_CORE
std::printf("%04x: bit 7 (HL)\n", _pc.word);
#endif
  _current_opcode = 0x7e;
  exec_instruction([&] (Byte &v) { instr_bit(7, v); }, _hl.word, 12);
  break;
case 0x7f:
#ifdef DEBUG_CORE
std::printf("%04x: bit 7 A\n", _pc.word);
#endif
  _current_opcode = 0x7f;
  exec_instruction([&] () { instr_bit(7, _af.high); }, 8);
  break;
case 0x80:
#ifdef DEBUG_CORE
std::printf("%04x: res 0 B\n", _pc.word);
#endif
  _current_opcode = 0x80;
  exec_instruction([&] () { instr_res(0, _bc.high); }, 8);
  break;
case 0x81:
#ifdef DEBUG_CORE
std::printf("%04x: res 0 C\n", _pc.word);
#endif
  _current_opcode = 0x81;
  exec_instruction([&] () { instr_res(0, _bc.low); }, 8);
  break;
case 0x82:
#ifdef DEBUG_CORE
std::printf("%04x: res 0 D\n", _pc.word);
#endif
  _current_opcode = 0x82;
  exec_instruction([&] () { instr_res(0, _de.high); }, 8);
  break;
case 0x83:
#ifdef DEBUG_CORE
std::printf("%04x: res 0 E\n", _pc.word);
#endif
  _current_opcode = 0x83;
  exec_instruction([&] () { instr_res(0, _de.low); }, 8);
  break;
case 0x84:
#ifdef DEBUG_CORE
std::printf("%04x: res 0 H\n", _pc.word);
#endif
  _current_opcode = 0x84;
  exec_instruction([&] () { instr_res(0, _hl.high); }, 8);
  break;
case 0x85:
#ifdef DEBUG_CORE
std::printf("%04x: res 0 L\n", _pc.word);
#endif
  _current_opcode = 0x85;
  exec_instruction([&] () { instr_res(0, _hl.low); }, 8);
  break;
case 0x86:
#ifdef DEBUG_CORE
std::printf("%04x: res 0 (HL)\n", _pc.word);
#endif
  _current_opcode = 0x86;
  exec_instruction([&] (Byte &v) { instr_res(0, v); }, _hl.word, 16);
  break;
case 0x87:
#ifdef DEBUG_CORE
std::printf("%04x: res 0 A\n", _pc.word);
#endif
  _current_opcode = 0x87;
  exec_instruction([&] () { instr_res(0, _af.high); }, 8);
  break;
case 0x88:
#ifdef DEBUG_CORE
std::printf("%04x: res 1 B\n", _pc.word);
#endif
  _current_opcode = 0x88;
  exec_instruction([&] () { instr_res(1, _bc.high); }, 8);
  break;
case 0x89:
#ifdef DEBUG_CORE
std::printf("%04x: res 1 C\n", _pc.word);
#endif
  _current_opcode = 0x89;
  exec_instruction([&] () { instr_res(1, _bc.low); }, 8);
  break;
case 0x8a:
#ifdef DEBUG_CORE
std::printf("%04x: res 1 D\n", _pc.word);
#endif
  _current_opcode = 0x8a;
  exec_instruction([&] () { instr_res(1, _de.high); }, 8);
  break;
case 0x8b:
#ifdef DEBUG_CORE
std::printf("%04x: res 1 E\n", _pc.word);
#endif
  _current_opcode = 0x8b;
  exec_instruction([&] () { instr_res(1, _de.low); }, 8);
  break;
case 0x8c:
#ifdef DEBUG_CORE
std::printf("%04x: res 1 H\n", _pc.word);
#endif
  _current_opcode = 0x8c;
  exec_instruction([&] () { instr_res(1, _hl.high); }, 8);
  break;
case 0x8d:
#ifdef DEBUG_CORE
std::printf("%04x: res 1 L\n", _pc.word);
#endif
  _current_opcode = 0x8d;
  exec_instruction([&] () { instr_res(1, _hl.low); }, 8);
  break;
case 0x8e:
#ifdef DEBUG_CORE
std::printf("%04x: res 1 (HL)\n", _pc.word);
#endif
  _current_opcode = 0x8e;
  exec_instruction([&] (Byte &v) { instr_res(1, v); }, _hl.word, 16);
  break;
case 0x8f:
#ifdef DEBUG_CORE
std::printf("%04x: res 1 A\n", _pc.word);
#endif
  _current_opcode = 0x8f;
  exec_instruction([&] () { instr_res(1, _af.high); }, 8);
  break;
case 0x90:
#ifdef DEBUG_CORE
std::printf("%04x: res 2 B\n", _pc.word);
#endif
  _current_opcode = 0x90;
  exec_instruction([&] () { instr_res(2, _bc.high); }, 8);
  break;
case 0x91:
#ifdef DEBUG_CORE
std::printf("%04x: res 2 C\n", _pc.word);
#endif
  _current_opcode = 0x91;
  exec_instruction([&] () { instr_res(2, _bc.low); }, 8);
  break;
case 0x92:
#ifdef DEBUG_CORE
std::printf("%04x: res 2 D\n", _pc.word);
#endif
  _current_opcode = 0x92;
  exec_instruction([&] () { instr_res(2, _de.high); }, 8);
  break;
case 0x93:
#ifdef DEBUG_CORE
std::printf("%04x: res 2 E\n", _pc.word);
#endif
  _current_opcode = 0x93;
  exec_instruction([&] () { instr_res(2, _de.low); }, 8);
  break;
case 0x94:
#ifdef DEBUG_CORE
std::printf("%04x: res 2 H\n", _pc.word);
#endif
  _current_opcode = 0x94;
  exec_instruction([&] () { instr_res(2, _hl.high); }, 8);
  break;
case 0x95:
#ifdef DEBUG_CORE
std::printf("%04x: res 2 L\n", _pc.word);
#endif
  _current_opcode = 0x95;
  exec_instruction([&] () { instr_res(2, _hl.low); }, 8);
  break;
case 0x96:
#ifdef DEBUG_CORE
std::printf("%04x: res 2 (HL)\n", _pc.word);
#endif
  _current_opcode = 0x96;
  exec_instruction([&] (Byte &v) { instr_res(2, v); }, _hl.word, 16);
  break;
case 0x97:
#ifdef DEBUG_CORE
std::printf("%04x: res 2 A\n", _pc.word);
#endif
  _current_opcode = 0x97;
  exec_instruction([&] () { instr_res(2, _af.high); }, 8);
  break;
case 0x98:
#ifdef DEBUG_CORE
std::printf("%04x: res 3 B\n", _pc.word);
#endif
  _current_opcode = 0x98;
  exec_instruction([&] () { instr_res(3, _bc.high); }, 8);
  break;
case 0x99:
#ifdef DEBUG_CORE
std::printf("%04x: res 3 C\n", _pc.word);
#endif
  _current_opcode = 0x99;
  exec_instruction([&] () { instr_res(3, _bc.low); }, 8);
  break;
case 0x9a:
#ifdef DEBUG_CORE
std::printf("%04x: res 3 D\n", _pc.word);
#endif
  _current_opcode = 0x9a;
  exec_instruction([&] () { instr_res(3, _de.high); }, 8);
  break;
case 0x9b:
#ifdef DEBUG_CORE
std::printf("%04x: res 3 E\n", _pc.word);
#endif
  _current_opcode = 0x9b;
  exec_instruction([&] () { instr_res(3, _de.low); }, 8);
  break;
case 0x9c:
#ifdef DEBUG_CORE
std::printf("%04x: res 3 H\n", _pc.word);
#endif
  _current_opcode = 0x9c;
  exec_instruction([&] () { instr_res(3, _hl.high); }, 8);
  break;
case 0x9d:
#ifdef DEBUG_CORE
std::printf("%04x: res 3 L\n", _pc.word);
#endif
  _current_opcode = 0x9d;
  exec_instruction([&] () { instr_res(3, _hl.low); }, 8);
  break;
case 0x9e:
#ifdef DEBUG_CORE
std::printf("%04x: res 3 (HL)\n", _pc.word);
#endif
  _current_opcode = 0x9e;
  exec_instruction([&] (Byte &v) { instr_res(3, v); }, _hl.word, 16);
  break;
case 0x9f:
#ifdef DEBUG_CORE
std::printf("%04x: res 3 A\n", _pc.word);
#endif
  _current_opcode = 0x9f;
  exec_instruction([&] () { instr_res(3, _af.high); }, 8);
  break;
case 0xa0:
#ifdef DEBUG_CORE
std::printf("%04x: res 4 B\n", _pc.word);
#endif
  _current_opcode = 0xa0;
  exec_instruction([&] () { instr_res(4, _bc.high); }, 8);
  break;
case 0xa1:
#ifdef DEBUG_CORE
std::printf("%04x: res 4 C\n", _pc.word);
#endif
  _current_opcode = 0xa1;
  exec_instruction([&] () { instr_res(4, _bc.low); }, 8);
  break;
case 0xa2:
#ifdef DEBUG_CORE
std::printf("%04x: res 4 D\n", _pc.word);
#endif
  _current_opcode = 0xa2;
  exec_instruction([&] () { instr_res(4, _de.high); }, 8);
  break;
case 0xa3:
#ifdef DEBUG_CORE
std::printf("%04x: res 4 E\n", _pc.word);
#endif
  _current_opcode = 0xa3;
  exec_instruction([&] () { instr_res(4, _de.low); }, 8);
  break;
case 0xa4:
#ifdef DEBUG_CORE
std::printf("%04x: res 4 H\n", _pc.word);
#endif
  _current_opcode = 0xa4;
  exec_instruction([&] () { instr_res(4, _hl.high); }, 8);
  break;
case 0xa5:
#ifdef DEBUG_CORE
std::printf("%04x: res 4 L\n", _pc.word);
#endif
  _current_opcode = 0xa5;
  exec_instruction([&] () { instr_res(4, _hl.low); }, 8);
  break;
case 0xa6:
#ifdef DEBUG_CORE
std::printf("%04x: res 4 (HL)\n", _pc.word);
#endif
  _current_opcode = 0xa6;
  exec_instruction([&] (Byte &v) { instr_res(4, v); }, _hl.word, 16);
  break;
case 0xa7:
#ifdef DEBUG_CORE
std::printf("%04x: res 4 A\n", _pc.word);
#endif
  _current_opcode = 0xa7;
  exec_instruction([&] () { instr_res(4, _af.high); }, 8);
  break;
case 0xa8:
#ifdef DEBUG_CORE
std::printf("%04x: res 5 B\n", _pc.word);
#endif
  _current_opcode = 0xa8;
  exec_instruction([&] () { instr_res(5, _bc.high); }, 8);
  break;
case 0xa9:
#ifdef DEBUG_CORE
std::printf("%04x: res 5 C\n", _pc.word);
#endif
  _current_opcode = 0xa9;
  exec_instruction([&] () { instr_res(5, _bc.low); }, 8);
  break;
case 0xaa:
#ifdef DEBUG_CORE
std::printf("%04x: res 5 D\n", _pc.word);
#endif
  _current_opcode = 0xaa;
  exec_instruction([&] () { instr_res(5, _de.high); }, 8);
  break;
case 0xab:
#ifdef DEBUG_CORE
std::printf("%04x: res 5 E\n", _pc.word);
#endif
  _current_opcode = 0xab;
  exec_instruction([&] () { instr_res(5, _de.low); }, 8);
  break;
case 0xac:
#ifdef DEBUG_CORE
std::printf("%04x: res 5 H\n", _pc.word);
#endif
  _current_opcode = 0xac;
  exec_instruction([&] () { instr_res(5, _hl.high); }, 8);
  break;
case 0xad:
#ifdef DEBUG_CORE
std::printf("%04x: res 5 L\n", _pc.word);
#endif
  _current_opcode = 0xad;
  exec_instruction([&] () { instr_res(5, _hl.low); }, 8);
  break;
case 0xae:
#ifdef DEBUG_CORE
std::printf("%04x: res 5 (HL)\n", _pc.word);
#endif
  _current_opcode = 0xae;
  exec_instruction([&] (Byte &v) { instr_res(5, v); }, _hl.word, 16);
  break;
case 0xaf:
#ifdef DEBUG_CORE
std::printf("%04x: res 5 A\n", _pc.word);
#endif
  _current_opcode = 0xaf;
  exec_instruction([&] () { instr_res(5, _af.high); }, 8);
  break;
case 0xb0:
#ifdef DEBUG_CORE
std::printf("%04x: res 6 B\n", _pc.word);
#endif
  _current_opcode = 0xb0;
  exec_instruction([&] () { instr_res(6, _bc.high); }, 8);
  break;
case 0xb1:
#ifdef DEBUG_CORE
std::printf("%04x: res 6 C\n", _pc.word);
#endif
  _current_opcode = 0xb1;
  exec_instruction([&] () { instr_res(6, _bc.low); }, 8);
  break;
case 0xb2:
#ifdef DEBUG_CORE
std::printf("%04x: res 6 D\n", _pc.word);
#endif
  _current_opcode = 0xb2;
  exec_instruction([&] () { instr_res(6, _de.high); }, 8);
  break;
case 0xb3:
#ifdef DEBUG_CORE
std::printf("%04x: res 6 E\n", _pc.word);
#endif
  _current_opcode = 0xb3;
  exec_instruction([&] () { instr_res(6, _de.low); }, 8);
  break;
case 0xb4:
#ifdef DEBUG_CORE
std::printf("%04x: res 6 H\n", _pc.word);
#endif
  _current_opcode = 0xb4;
  exec_instruction([&] () { instr_res(6, _hl.high); }, 8);
  break;
case 0xb5:
#ifdef DEBUG_CORE
std::printf("%04x: res 6 L\n", _pc.word);
#endif
  _current_opcode = 0xb5;
  exec_instruction([&] () { instr_res(6, _hl.low); }, 8);
  break;
case 0xb6:
#ifdef DEBUG_CORE
std::printf("%04x: res 6 (HL)\n", _pc.word);
#endif
  _current_opcode = 0xb6;
  exec_instruction([&] (Byte &v) { instr_res(6, v); }, _hl.word, 16);
  break;
case 0xb7:
#ifdef DEBUG_CORE
std::printf("%04x: res 6 A\n", _pc.word);
#endif
  _current_opcode = 0xb7;
  exec_instruction([&] () { instr_res(6, _af.high); }, 8);
  break;
case 0xb8:
#ifdef DEBUG_CORE
std::printf("%04x: res 7 B\n", _pc.word);
#endif
  _current_opcode = 0xb8;
  exec_instruction([&] () { instr_res(7, _bc.high); }, 8);
  break;
case 0xb9:
#ifdef DEBUG_CORE
std::printf("%04x: res 7 C\n", _pc.word);
#endif
  _current_opcode = 0xb9;
  exec_instruction([&] () { instr_res(7, _bc.low); }, 8);
  break;
case 0xba:
#ifdef DEBUG_CORE
std::printf("%04x: res 7 D\n", _pc.word);
#endif
  _current_opcode = 0xba;
  exec_instruction([&] () { instr_res(7, _de.high); }, 8);
  break;
case 0xbb:
#ifdef DEBUG_CORE
std::printf("%04x: res 7 E\n", _pc.word);
#endif
  _current_opcode = 0xbb;
  exec_instruction([&] () { instr_res(7, _de.low); }, 8);
  break;
case 0xbc:
#ifdef DEBUG_CORE
std::printf("%04x: res 7 H\n", _pc.word);
#endif
  _current_opcode = 0xbc;
  exec_instruction([&] () { instr_res(7, _hl.high); }, 8);
  break;
case 0xbd:
#ifdef DEBUG_CORE
std::printf("%04x: res 7 L\n", _pc.word);
#endif
  _current_opcode = 0xbd;
  exec_instruction([&] () { instr_res(7, _hl.low); }, 8);
  break;
case 0xbe:
#ifdef DEBUG_CORE
std::printf("%04x: res 7 (HL)\n", _pc.word);
#endif
  _current_opcode = 0xbe;
  exec_instruction([&] (Byte &v) { instr_res(7, v); }, _hl.word, 16);
  break;
case 0xbf:
#ifdef DEBUG_CORE
std::printf("%04x: res 7 A\n", _pc.word);
#endif
  _current_opcode = 0xbf;
  exec_instruction([&] () { instr_res(7, _af.high); }, 8);
  break;
case 0xc0:
#ifdef DEBUG_CORE
std::printf("%04x: set 0 B\n", _pc.word);
#endif
  _current_opcode = 0xc0;
  exec_instruction([&] () { instr_set(0, _bc.high); }, 8);
  break;
case 0xc1:
#ifdef DEBUG_CORE
std::printf("%04x: set 0 C\n", _pc.word);
#endif
  _current_opcode = 0xc1;
  exec_instruction([&] () { instr_set(0, _bc.low); }, 8);
  break;
case 0xc2:
#ifdef DEBUG_CORE
std::printf("%04x: set 0 D\n", _pc.word);
#endif
  _current_opcode = 0xc2;
  exec_instruction([&] () { instr_set(0, _de.high); }, 8);
  break;
case 0xc3:
#ifdef DEBUG_CORE
std::printf("%04x: set 0 E\n", _pc.word);
#endif
  _current_opcode = 0xc3;
  exec_instruction([&] () { instr_set(0, _de.low); }, 8);
  break;
case 0xc4:
#ifdef DEBUG_CORE
std::printf("%04x: set 0 H\n", _pc.word);
#endif
  _current_opcode = 0xc4;
  exec_instruction([&] () { instr_set(0, _hl.high); }, 8);
  break;
case 0xc5:
#ifdef DEBUG_CORE
std::printf("%04x: set 0 L\n", _pc.word);
#endif
  _current_opcode = 0xc5;
  exec_instruction([&] () { instr_set(0, _hl.low); }, 8);
  break;
case 0xc6:
#ifdef DEBUG_CORE
std::printf("%04x: set 0 (HL)\n", _pc.word);
#endif
  _current_opcode = 0xc6;
  exec_instruction([&] (Byte &v) { instr_set(0, v); }, _hl.word, 16);
  break;
case 0xc7:
#ifdef DEBUG_CORE
std::printf("%04x: set 0 A\n", _pc.word);
#endif
  _current_opcode = 0xc7;
  exec_instruction([&] () { instr_set(0, _af.high); }, 8);
  break;
case 0xc8:
#ifdef DEBUG_CORE
std::printf("%04x: set 1 B\n", _pc.word);
#endif
  _current_opcode = 0xc8;
  exec_instruction([&] () { instr_set(1, _bc.high); }, 8);
  break;
case 0xc9:
#ifdef DEBUG_CORE
std::printf("%04x: set 1 C\n", _pc.word);
#endif
  _current_opcode = 0xc9;
  exec_instruction([&] () { instr_set(1, _bc.low); }, 8);
  break;
case 0xca:
#ifdef DEBUG_CORE
std::printf("%04x: set 1 D\n", _pc.word);
#endif
  _current_opcode = 0xca;
  exec_instruction([&] () { instr_set(1, _de.high); }, 8);
  break;
case 0xcb:
#ifdef DEBUG_CORE
std::printf("%04x: set 1 E\n", _pc.word);
#endif
  _current_opcode = 0xcb;
  exec_instruction([&] () { instr_set(1, _de.low); }, 8);
  break;
case 0xcc:
#ifdef DEBUG_CORE
std::printf("%04x: set 1 H\n", _pc.word);
#endif
  _current_opcode = 0xcc;
  exec_instruction([&] () { instr_set(1, _hl.high); }, 8);
  break;
case 0xcd:
#ifdef DEBUG_CORE
std::printf("%04x: set 1 L\n", _pc.word);
#endif
  _current_opcode = 0xcd;
  exec_instruction([&] () { instr_set(1, _hl.low); }, 8);
  break;
case 0xce:
#ifdef DEBUG_CORE
std::printf("%04x: set 1 (HL)\n", _pc.word);
#endif
  _current_opcode = 0xce;
  exec_instruction([&] (Byte &v) { instr_set(1, v); }, _hl.word, 16);
  break;
case 0xcf:
#ifdef DEBUG_CORE
std::printf("%04x: set 1 A\n", _pc.word);
#endif
  _current_opcode = 0xcf;
  exec_instruction([&] () { instr_set(1, _af.high); }, 8);
  break;
case 0xd0:
#ifdef DEBUG_CORE
std::printf("%04x: set 2 B\n", _pc.word);
#endif
  _current_opcode = 0xd0;
  exec_instruction([&] () { instr_set(2, _bc.high); }, 8);
  break;
case 0xd1:
#ifdef DEBUG_CORE
std::printf("%04x: set 2 C\n", _pc.word);
#endif
  _current_opcode = 0xd1;
  exec_instruction([&] () { instr_set(2, _bc.low); }, 8);
  break;
case 0xd2:
#ifdef DEBUG_CORE
std::printf("%04x: set 2 D\n", _pc.word);
#endif
  _current_opcode = 0xd2;
  exec_instruction([&] () { instr_set(2, _de.high); }, 8);
  break;
case 0xd3:
#ifdef DEBUG_CORE
std::printf("%04x: set 2 E\n", _pc.word);
#endif
  _current_opcode = 0xd3;
  exec_instruction([&] () { instr_set(2, _de.low); }, 8);
  break;
case 0xd4:
#ifdef DEBUG_CORE
std::printf("%04x: set 2 H\n", _pc.word);
#endif
  _current_opcode = 0xd4;
  exec_instruction([&] () { instr_set(2, _hl.high); }, 8);
  break;
case 0xd5:
#ifdef DEBUG_CORE
std::printf("%04x: set 2 L\n", _pc.word);
#endif
  _current_opcode = 0xd5;
  exec_instruction([&] () { instr_set(2, _hl.low); }, 8);
  break;
case 0xd6:
#ifdef DEBUG_CORE
std::printf("%04x: set 2 (HL)\n", _pc.word);
#endif
  _current_opcode = 0xd6;
  exec_instruction([&] (Byte &v) { instr_set(2, v); }, _hl.word, 16);
  break;
case 0xd7:
#ifdef DEBUG_CORE
std::printf("%04x: set 2 A\n", _pc.word);
#endif
  _current_opcode = 0xd7;
  exec_instruction([&] () { instr_set(2, _af.high); }, 8);
  break;
case 0xd8:
#ifdef DEBUG_CORE
std::printf("%04x: set 3 B\n", _pc.word);
#endif
  _current_opcode = 0xd8;
  exec_instruction([&] () { instr_set(3, _bc.high); }, 8);
  break;
case 0xd9:
#ifdef DEBUG_CORE
std::printf("%04x: set 3 C\n", _pc.word);
#endif
  _current_opcode = 0xd9;
  exec_instruction([&] () { instr_set(3, _bc.low); }, 8);
  break;
case 0xda:
#ifdef DEBUG_CORE
std::printf("%04x: set 3 D\n", _pc.word);
#endif
  _current_opcode = 0xda;
  exec_instruction([&] () { instr_set(3, _de.high); }, 8);
  break;
case 0xdb:
#ifdef DEBUG_CORE
std::printf("%04x: set 3 E\n", _pc.word);
#endif
  _current_opcode = 0xdb;
  exec_instruction([&] () { instr_set(3, _de.low); }, 8);
  break;
case 0xdc:
#ifdef DEBUG_CORE
std::printf("%04x: set 3 H\n", _pc.word);
#endif
  _current_opcode = 0xdc;
  exec_instruction([&] () { instr_set(3, _hl.high); }, 8);
  break;
case 0xdd:
#ifdef DEBUG_CORE
std::printf("%04x: set 3 L\n", _pc.word);
#endif
  _current_opcode = 0xdd;
  exec_instruction([&] () { instr_set(3, _hl.low); }, 8);
  break;
case 0xde:
#ifdef DEBUG_CORE
std::printf("%04x: set 3 (HL)\n", _pc.word);
#endif
  _current_opcode = 0xde;
  exec_instruction([&] (Byte &v) { instr_set(3, v); }, _hl.word, 16);
  break;
case 0xdf:
#ifdef DEBUG_CORE
std::printf("%04x: set 3 A\n", _pc.word);
#endif
  _current_opcode = 0xdf;
  exec_instruction([&] () { instr_set(3, _af.high); }, 8);
  break;
case 0xe0:
#ifdef DEBUG_CORE
std::printf("%04x: set 4 B\n", _pc.word);
#endif
  _current_opcode = 0xe0;
  exec_instruction([&] () { instr_set(4, _bc.high); }, 8);
  break;
case 0xe1:
#ifdef DEBUG_CORE
std::printf("%04x: set 4 C\n", _pc.word);
#endif
  _current_opcode = 0xe1;
  exec_instruction([&] () { instr_set(4, _bc.low); }, 8);
  break;
case 0xe2:
#ifdef DEBUG_CORE
std::printf("%04x: set 4 D\n", _pc.word);
#endif
  _current_opcode = 0xe2;
  exec_instruction([&] () { instr_set(4, _de.high); }, 8);
  break;
case 0xe3:
#ifdef DEBUG_CORE
std::printf("%04x: set 4 E\n", _pc.word);
#endif
  _current_opcode = 0xe3;
  exec_instruction([&] () { instr_set(4, _de.low); }, 8);
  break;
case 0xe4:
#ifdef DEBUG_CORE
std::printf("%04x: set 4 H\n", _pc.word);
#endif
  _current_opcode = 0xe4;
  exec_instruction([&] () { instr_set(4, _hl.high); }, 8);
  break;
case 0xe5:
#ifdef DEBUG_CORE
std::printf("%04x: set 4 L\n", _pc.word);
#endif
  _current_opcode = 0xe5;
  exec_instruction([&] () { instr_set(4, _hl.low); }, 8);
  break;
case 0xe6:
#ifdef DEBUG_CORE
std::printf("%04x: set 4 (HL)\n", _pc.word);
#endif
  _current_opcode = 0xe6;
  exec_instruction([&] (Byte &v) { instr_set(4, v); }, _hl.word, 16);
  break;
case 0xe7:
#ifdef DEBUG_CORE
std::printf("%04x: set 4 A\n", _pc.word);
#endif
  _current_opcode = 0xe7;
  exec_instruction([&] () { instr_set(4, _af.high); }, 8);
  break;
case 0xe8:
#ifdef DEBUG_CORE
std::printf("%04x: set 5 B\n", _pc.word);
#endif
  _current_opcode = 0xe8;
  exec_instruction([&] () { instr_set(5, _bc.high); }, 8);
  break;
case 0xe9:
#ifdef DEBUG_CORE
std::printf("%04x: set 5 C\n", _pc.word);
#endif
  _current_opcode = 0xe9;
  exec_instruction([&] () { instr_set(5, _bc.low); }, 8);
  break;
case 0xea:
#ifdef DEBUG_CORE
std::printf("%04x: set 5 D\n", _pc.word);
#endif
  _current_opcode = 0xea;
  exec_instruction([&] () { instr_set(5, _de.high); }, 8);
  break;
case 0xeb:
#ifdef DEBUG_CORE
std::printf("%04x: set 5 E\n", _pc.word);
#endif
  _current_opcode = 0xeb;
  exec_instruction([&] () { instr_set(5, _de.low); }, 8);
  break;
case 0xec:
#ifdef DEBUG_CORE
std::printf("%04x: set 5 H\n", _pc.word);
#endif
  _current_opcode = 0xec;
  exec_instruction([&] () { instr_set(5, _hl.high); }, 8);
  break;
case 0xed:
#ifdef DEBUG_CORE
std::printf("%04x: set 5 L\n", _pc.word);
#endif
  _current_opcode = 0xed;
  exec_instruction([&] () { instr_set(5, _hl.low); }, 8);
  break;
case 0xee:
#ifdef DEBUG_CORE
std::printf("%04x: set 5 (HL)\n", _pc.word);
#endif
  _current_opcode = 0xee;
  exec_instruction([&] (Byte &v) { instr_set(5, v); }, _hl.word, 16);
  break;
case 0xef:
#ifdef DEBUG_CORE
std::printf("%04x: set 5 A\n", _pc.word);
#endif
  _current_opcode = 0xef;
  exec_instruction([&] () { instr_set(5, _af.high); }, 8);
  break;
case 0xf0:
#ifdef DEBUG_CORE
std::printf("%04x: set 6 B\n", _pc.word);
#endif
  _current_opcode = 0xf0;
  exec_instruction([&] () { instr_set(6, _bc.high); }, 8);
  break;
case 0xf1:
#ifdef DEBUG_CORE
std::printf("%04x: set 6 C\n", _pc.word);
#endif
  _current_opcode = 0xf1;
  exec_instruction([&] () { instr_set(6, _bc.low); }, 8);
  break;
case 0xf2:
#ifdef DEBUG_CORE
std::printf("%04x: set 6 D\n", _pc.word);
#endif
  _current_opcode = 0xf2;
  exec_instruction([&] () { instr_set(6, _de.high); }, 8);
  break;
case 0xf3:
#ifdef DEBUG_CORE
std::printf("%04x: set 6 E\n", _pc.word);
#endif
  _current_opcode = 0xf3;
  exec_instruction([&] () { instr_set(6, _de.low); }, 8);
  break;
case 0xf4:
#ifdef DEBUG_CORE
std::printf("%04x: set 6 H\n", _pc.word);
#endif
  _current_opcode = 0xf4;
  exec_instruction([&] () { instr_set(6, _hl.high); }, 8);
  break;
case 0xf5:
#ifdef DEBUG_CORE
std::printf("%04x: set 6 L\n", _pc.word);
#endif
  _current_opcode = 0xf5;
  exec_instruction([&] () { instr_set(6, _hl.low); }, 8);
  break;
case 0xf6:
#ifdef DEBUG_CORE
std::printf("%04x: set 6 (HL)\n", _pc.word);
#endif
  _current_opcode = 0xf6;
  exec_instruction([&] (Byte &v) { instr_set(6, v); }, _hl.word, 16);
  break;
case 0xf7:
#ifdef DEBUG_CORE
std::printf("%04x: set 6 A\n", _pc.word);
#endif
  _current_opcode = 0xf7;
  exec_instruction([&] () { instr_set(6, _af.high); }, 8);
  break;
case 0xf8:
#ifdef DEBUG_CORE
std::printf("%04x: set 7 B\n", _pc.word);
#endif
  _current_opcode = 0xf8;
  exec_instruction([&] () { instr_set(7, _bc.high); }, 8);
  break;
case 0xf9:
#ifdef DEBUG_CORE
std::printf("%04x: set 7 C\n", _pc.word);
#endif
  _current_opcode = 0xf9;
  exec_instruction([&] () { instr_set(7, _bc.low); }, 8);
  break;
case 0xfa:
#ifdef DEBUG_CORE
std::printf("%04x: set 7 D\n", _pc.word);
#endif
  _current_opcode = 0xfa;
  exec_instruction([&] () { instr_set(7, _de.high); }, 8);
  break;
case 0xfb:
#ifdef DEBUG_CORE
std::printf("%04x: set 7 E\n", _pc.word);
#endif
  _current_opcode = 0xfb;
  exec_instruction([&] () { instr_set(7, _de.low); }, 8);
  break;
case 0xfc:
#ifdef DEBUG_CORE
std::printf("%04x: set 7 H\n", _pc.word);
#endif
  _current_opcode = 0xfc;
  exec_instruction([&] () { instr_set(7, _hl.high); }, 8);
  break;
case 0xfd:
#ifdef DEBUG_CORE
std::printf("%04x: set 7 L\n", _pc.word);
#endif
  _current_opcode = 0xfd;
  exec_instruction([&] () { instr_set(7, _hl.low); }, 8);
  break;
case 0xfe:
#ifdef DEBUG_CORE
std::printf("%04x: set 7 (HL)\n", _pc.word);
#endif
  _current_opcode = 0xfe;
  exec_instruction([&] (Byte &v) { instr_set(7, v); }, _hl.word, 16);
  break;
case 0xff:
#ifdef DEBUG_CORE
std::printf("%04x: set 7 A\n", _pc.word);
#endif
  _current_opcode = 0xff;
  exec_instruction([&] () { instr_set(7, _af.high); }, 8);
  break;
}
