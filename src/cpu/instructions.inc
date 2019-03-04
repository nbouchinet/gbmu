case 0x0:
  exec_instruction([&] () { instr_nop(0); }, 4);
  break;
case 0x1:
  exec_instruction([&] () { instr_ld(_bc.word, fetch_word()); }, 12);
  break;
case 0x2:
  exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, _bc.word, 8);
  break;
case 0x3:
  exec_instruction([&] () { instr_inc(_bc.word); }, 8);
  break;
case 0x4:
  exec_instruction([&] () { instr_inc(_bc.high); }, 4);
  break;
case 0x5:
  exec_instruction([&] () { instr_dec(_bc.high); }, 4);
  break;
case 0x6:
  exec_instruction([&] () { instr_ld(_bc.high, *it++); }, 8);
  break;
case 0x7:
  exec_instruction([&] () { instr_rlca(); }, 4);
  break;
case 0x8:
  exec_instruction([&] (Word &v) { instr_ld(v, _sp.word); }, fetch_word(), 20);
  break;
case 0x9:
  exec_instruction([&] () { instr_add(_hl.word, _bc.word); }, 8);
  break;
case 0xa:
  exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(_bc.word)); }, 8);
  break;
case 0xb:
  exec_instruction([&] () { instr_dec(_bc.word); }, 8);
  break;
case 0xc:
  exec_instruction([&] () { instr_inc(_bc.low); }, 4);
  break;
case 0xd:
  exec_instruction([&] () { instr_dec(_bc.low); }, 4);
  break;
case 0xe:
  exec_instruction([&] () { instr_ld(_bc.low, *it++); }, 8);
  break;
case 0xf:
  exec_instruction([&] () { instr_rrca(); }, 4);
  break;
case 0x10:
  exec_instruction([&] () { instr_stop(); }, 4);
  break;
case 0x11:
  exec_instruction([&] () { instr_ld(_de.word, fetch_word()); }, 12);
  break;
case 0x12:
  exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, _de.word, 8);
  break;
case 0x13:
  exec_instruction([&] () { instr_inc(_de.word); }, 8);
  break;
case 0x14:
  exec_instruction([&] () { instr_inc(_de.high); }, 4);
  break;
case 0x15:
  exec_instruction([&] () { instr_dec(_de.high); }, 4);
  break;
case 0x16:
  exec_instruction([&] () { instr_ld(_de.high, *it++); }, 8);
  break;
case 0x17:
  exec_instruction([&] () { instr_rla(); }, 4);
  break;
case 0x18:
  exec_instruction([&] () { instr_jr(*it++); }, 12);
  break;
case 0x19:
  exec_instruction([&] () { instr_add(_hl.word, _de.word); }, 8);
  break;
case 0x1a:
  exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(_de.word)); }, 8);
  break;
case 0x1b:
  exec_instruction([&] () { instr_dec(_de.word); }, 8);
  break;
case 0x1c:
  exec_instruction([&] () { instr_inc(_de.low); }, 4);
  break;
case 0x1d:
  exec_instruction([&] () { instr_dec(_de.low); }, 4);
  break;
case 0x1e:
  exec_instruction([&] () { instr_ld(_de.low, *it++); }, 8);
  break;
case 0x1f:
  exec_instruction([&] () { instr_rra(); }, 4);
  break;
case 0x20:
  exec_instruction([&] () { instr_jr(JumpCondition::NonZero, *it++); }, 12, 8);
  break;
case 0x21:
  exec_instruction([&] () { instr_ld(_hl.word, fetch_word()); }, 12);
  break;
case 0x22:
  exec_instruction([&] (Byte &v) { instr_ldi(v, _af.high); }, _hl.word, 8);
  break;
case 0x23:
  exec_instruction([&] () { instr_inc(_hl.word); }, 8);
  break;
case 0x24:
  exec_instruction([&] () { instr_inc(_hl.high); }, 4);
  break;
case 0x25:
  exec_instruction([&] () { instr_dec(_hl.high); }, 4);
  break;
case 0x26:
  exec_instruction([&] () { instr_ld(_hl.high, *it++); }, 8);
  break;
case 0x27:
  exec_instruction([&] () { instr_daa(); }, 4);
  break;
case 0x28:
  exec_instruction([&] () { instr_jr(JumpCondition::Zero, *it++); }, 12, 8);
  break;
case 0x29:
  exec_instruction([&] () { instr_add(_hl.word, _hl.word); }, 8);
  break;
case 0x2a:
  exec_instruction([&] () { instr_ldi(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x2b:
  exec_instruction([&] () { instr_dec(_hl.word); }, 8);
  break;
case 0x2c:
  exec_instruction([&] () { instr_inc(_hl.low); }, 4);
  break;
case 0x2d:
  exec_instruction([&] () { instr_dec(_hl.low); }, 4);
  break;
case 0x2e:
  exec_instruction([&] () { instr_ld(_hl.low, *it++); }, 8);
  break;
case 0x2f:
  exec_instruction([&] () { instr_cpl(); }, 4);
  break;
case 0x30:
  exec_instruction([&] () { instr_jr(JumpCondition::NonCarry, *it++); }, 12, 8);
  break;
case 0x31:
  exec_instruction([&] () { instr_ld(_sp.word, fetch_word()); }, 12);
  break;
case 0x32:
  exec_instruction([&] (Byte &v) { instr_ldd(v, _af.high); }, _hl.word, 8);
  break;
case 0x33:
  exec_instruction([&] () { instr_inc(_sp.word); }, 8);
  break;
case 0x34:
  exec_instruction([&] (Byte &v) { instr_inc(v); }, _hl.word, 12);
  break;
case 0x35:
  exec_instruction([&] (Byte &v) { instr_dec(v); }, _hl.word, 12);
  break;
case 0x36:
  exec_instruction([&] (Byte &v) { instr_ld(v, *it++); }, _hl.word, 12);
  break;
case 0x37:
  exec_instruction([&] () { instr_scf(); }, 4);
  break;
case 0x38:
  exec_instruction([&] () { instr_jr(JumpCondition::Carry, *it++); }, 12, 8);
  break;
case 0x39:
  exec_instruction([&] () { instr_add(_hl.word, _sp.word); }, 8);
  break;
case 0x3a:
  exec_instruction([&] () { instr_ldd(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x3b:
  exec_instruction([&] () { instr_dec(_sp.word); }, 8);
  break;
case 0x3c:
  exec_instruction([&] () { instr_inc(_af.high); }, 4);
  break;
case 0x3d:
  exec_instruction([&] () { instr_dec(_af.high); }, 4);
  break;
case 0x3e:
  exec_instruction([&] () { instr_ld(_af.high, *it++); }, 8);
  break;
case 0x3f:
  exec_instruction([&] () { instr_ccf(); }, 4);
  break;
case 0x40:
  exec_instruction([&] () { instr_ld(_bc.high, _bc.high); }, 4);
  break;
case 0x41:
  exec_instruction([&] () { instr_ld(_bc.high, _bc.low); }, 4);
  break;
case 0x42:
  exec_instruction([&] () { instr_ld(_bc.high, _de.high); }, 4);
  break;
case 0x43:
  exec_instruction([&] () { instr_ld(_bc.high, _de.low); }, 4);
  break;
case 0x44:
  exec_instruction([&] () { instr_ld(_bc.high, _hl.high); }, 4);
  break;
case 0x45:
  exec_instruction([&] () { instr_ld(_bc.high, _hl.low); }, 4);
  break;
case 0x46:
  exec_instruction([&] () { instr_ld(_bc.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x47:
  exec_instruction([&] () { instr_ld(_bc.high, _af.high); }, 4);
  break;
case 0x48:
  exec_instruction([&] () { instr_ld(_bc.low, _bc.high); }, 4);
  break;
case 0x49:
  exec_instruction([&] () { instr_ld(_bc.low, _bc.low); }, 4);
  break;
case 0x4a:
  exec_instruction([&] () { instr_ld(_bc.low, _de.high); }, 4);
  break;
case 0x4b:
  exec_instruction([&] () { instr_ld(_bc.low, _de.low); }, 4);
  break;
case 0x4c:
  exec_instruction([&] () { instr_ld(_bc.low, _hl.high); }, 4);
  break;
case 0x4d:
  exec_instruction([&] () { instr_ld(_bc.low, _hl.low); }, 4);
  break;
case 0x4e:
  exec_instruction([&] () { instr_ld(_bc.low, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x4f:
  exec_instruction([&] () { instr_ld(_bc.low, _af.high); }, 4);
  break;
case 0x50:
  exec_instruction([&] () { instr_ld(_de.high, _bc.high); }, 4);
  break;
case 0x51:
  exec_instruction([&] () { instr_ld(_de.high, _bc.low); }, 4);
  break;
case 0x52:
  exec_instruction([&] () { instr_ld(_de.high, _de.high); }, 4);
  break;
case 0x53:
  exec_instruction([&] () { instr_ld(_de.high, _de.low); }, 4);
  break;
case 0x54:
  exec_instruction([&] () { instr_ld(_de.high, _hl.high); }, 4);
  break;
case 0x55:
  exec_instruction([&] () { instr_ld(_de.high, _hl.low); }, 4);
  break;
case 0x56:
  exec_instruction([&] () { instr_ld(_de.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x57:
  exec_instruction([&] () { instr_ld(_de.high, _af.high); }, 4);
  break;
case 0x58:
  exec_instruction([&] () { instr_ld(_de.low, _bc.high); }, 4);
  break;
case 0x59:
  exec_instruction([&] () { instr_ld(_de.low, _bc.low); }, 4);
  break;
case 0x5a:
  exec_instruction([&] () { instr_ld(_de.low, _de.high); }, 4);
  break;
case 0x5b:
  exec_instruction([&] () { instr_ld(_de.low, _de.low); }, 4);
  break;
case 0x5c:
  exec_instruction([&] () { instr_ld(_de.low, _hl.high); }, 4);
  break;
case 0x5d:
  exec_instruction([&] () { instr_ld(_de.low, _hl.low); }, 4);
  break;
case 0x5e:
  exec_instruction([&] () { instr_ld(_de.low, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x5f:
  exec_instruction([&] () { instr_ld(_de.low, _af.high); }, 4);
  break;
case 0x60:
  exec_instruction([&] () { instr_ld(_hl.high, _bc.high); }, 4);
  break;
case 0x61:
  exec_instruction([&] () { instr_ld(_hl.high, _bc.low); }, 4);
  break;
case 0x62:
  exec_instruction([&] () { instr_ld(_hl.high, _de.high); }, 4);
  break;
case 0x63:
  exec_instruction([&] () { instr_ld(_hl.high, _de.low); }, 4);
  break;
case 0x64:
  exec_instruction([&] () { instr_ld(_hl.high, _hl.high); }, 4);
  break;
case 0x65:
  exec_instruction([&] () { instr_ld(_hl.high, _hl.low); }, 4);
  break;
case 0x66:
  exec_instruction([&] () { instr_ld(_hl.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x67:
  exec_instruction([&] () { instr_ld(_hl.high, _af.high); }, 4);
  break;
case 0x68:
  exec_instruction([&] () { instr_ld(_hl.low, _bc.high); }, 4);
  break;
case 0x69:
  exec_instruction([&] () { instr_ld(_hl.low, _bc.low); }, 4);
  break;
case 0x6a:
  exec_instruction([&] () { instr_ld(_hl.low, _de.high); }, 4);
  break;
case 0x6b:
  exec_instruction([&] () { instr_ld(_hl.low, _de.low); }, 4);
  break;
case 0x6c:
  exec_instruction([&] () { instr_ld(_hl.low, _hl.high); }, 4);
  break;
case 0x6d:
  exec_instruction([&] () { instr_ld(_hl.low, _hl.low); }, 4);
  break;
case 0x6e:
  exec_instruction([&] () { instr_ld(_hl.low, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x6f:
  exec_instruction([&] () { instr_ld(_hl.low, _af.high); }, 4);
  break;
case 0x70:
  exec_instruction([&] (Byte &v) { instr_ld(v, _bc.high); }, _hl.word, 8);
  break;
case 0x71:
  exec_instruction([&] (Byte &v) { instr_ld(v, _bc.low); }, _hl.word, 8);
  break;
case 0x72:
  exec_instruction([&] (Byte &v) { instr_ld(v, _de.high); }, _hl.word, 8);
  break;
case 0x73:
  exec_instruction([&] (Byte &v) { instr_ld(v, _de.low); }, _hl.word, 8);
  break;
case 0x74:
  exec_instruction([&] (Byte &v) { instr_ld(v, _hl.high); }, _hl.word, 8);
  break;
case 0x75:
  exec_instruction([&] (Byte &v) { instr_ld(v, _hl.low); }, _hl.word, 8);
  break;
case 0x76:
  exec_instruction([&] () { instr_halt(); }, 4);
  break;
case 0x77:
  exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, _hl.word, 8);
  break;
case 0x78:
  exec_instruction([&] () { instr_ld(_af.high, _bc.high); }, 4);
  break;
case 0x79:
  exec_instruction([&] () { instr_ld(_af.high, _bc.low); }, 4);
  break;
case 0x7a:
  exec_instruction([&] () { instr_ld(_af.high, _de.high); }, 4);
  break;
case 0x7b:
  exec_instruction([&] () { instr_ld(_af.high, _de.low); }, 4);
  break;
case 0x7c:
  exec_instruction([&] () { instr_ld(_af.high, _hl.high); }, 4);
  break;
case 0x7d:
  exec_instruction([&] () { instr_ld(_af.high, _hl.low); }, 4);
  break;
case 0x7e:
  exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x7f:
  exec_instruction([&] () { instr_ld(_af.high, _af.high); }, 4);
  break;
case 0x80:
  exec_instruction([&] () { instr_add(_af.high, _bc.high); }, 4);
  break;
case 0x81:
  exec_instruction([&] () { instr_add(_af.high, _bc.low); }, 4);
  break;
case 0x82:
  exec_instruction([&] () { instr_add(_af.high, _de.high); }, 4);
  break;
case 0x83:
  exec_instruction([&] () { instr_add(_af.high, _de.low); }, 4);
  break;
case 0x84:
  exec_instruction([&] () { instr_add(_af.high, _hl.high); }, 4);
  break;
case 0x85:
  exec_instruction([&] () { instr_add(_af.high, _hl.low); }, 4);
  break;
case 0x86:
  exec_instruction([&] () { instr_add(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x87:
  exec_instruction([&] () { instr_add(_af.high, _af.high); }, 4);
  break;
case 0x88:
  exec_instruction([&] () { instr_adc(_af.high, _bc.high); }, 4);
  break;
case 0x89:
  exec_instruction([&] () { instr_adc(_af.high, _bc.low); }, 4);
  break;
case 0x8a:
  exec_instruction([&] () { instr_adc(_af.high, _de.high); }, 4);
  break;
case 0x8b:
  exec_instruction([&] () { instr_adc(_af.high, _de.low); }, 4);
  break;
case 0x8c:
  exec_instruction([&] () { instr_adc(_af.high, _hl.high); }, 4);
  break;
case 0x8d:
  exec_instruction([&] () { instr_adc(_af.high, _hl.low); }, 4);
  break;
case 0x8e:
  exec_instruction([&] () { instr_adc(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x8f:
  exec_instruction([&] () { instr_adc(_af.high, _af.high); }, 4);
  break;
case 0x90:
  exec_instruction([&] () { instr_sub(_af.high, _bc.high); }, 4);
  break;
case 0x91:
  exec_instruction([&] () { instr_sub(_af.high, _bc.low); }, 4);
  break;
case 0x92:
  exec_instruction([&] () { instr_sub(_af.high, _de.high); }, 4);
  break;
case 0x93:
  exec_instruction([&] () { instr_sub(_af.high, _de.low); }, 4);
  break;
case 0x94:
  exec_instruction([&] () { instr_sub(_af.high, _hl.high); }, 4);
  break;
case 0x95:
  exec_instruction([&] () { instr_sub(_af.high, _hl.low); }, 4);
  break;
case 0x96:
  exec_instruction([&] () { instr_sub(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x97:
  exec_instruction([&] () { instr_sub(_af.high, _af.high); }, 4);
  break;
case 0x98:
  exec_instruction([&] () { instr_sbc(_af.high, _bc.high); }, 4);
  break;
case 0x99:
  exec_instruction([&] () { instr_sbc(_af.high, _bc.low); }, 4);
  break;
case 0x9a:
  exec_instruction([&] () { instr_sbc(_af.high, _de.high); }, 4);
  break;
case 0x9b:
  exec_instruction([&] () { instr_sbc(_af.high, _de.low); }, 4);
  break;
case 0x9c:
  exec_instruction([&] () { instr_sbc(_af.high, _hl.high); }, 4);
  break;
case 0x9d:
  exec_instruction([&] () { instr_sbc(_af.high, _hl.low); }, 4);
  break;
case 0x9e:
  exec_instruction([&] () { instr_sbc(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0x9f:
  exec_instruction([&] () { instr_sbc(_af.high, _af.high); }, 4);
  break;
case 0xa0:
  exec_instruction([&] () { instr_and(_af.high, _bc.high); }, 4);
  break;
case 0xa1:
  exec_instruction([&] () { instr_and(_af.high, _bc.low); }, 4);
  break;
case 0xa2:
  exec_instruction([&] () { instr_and(_af.high, _de.high); }, 4);
  break;
case 0xa3:
  exec_instruction([&] () { instr_and(_af.high, _de.low); }, 4);
  break;
case 0xa4:
  exec_instruction([&] () { instr_and(_af.high, _hl.high); }, 4);
  break;
case 0xa5:
  exec_instruction([&] () { instr_and(_af.high, _hl.low); }, 4);
  break;
case 0xa6:
  exec_instruction([&] () { instr_and(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0xa7:
  exec_instruction([&] () { instr_and(_af.high, _af.high); }, 4);
  break;
case 0xa8:
  exec_instruction([&] () { instr_xor(_af.high, _bc.high); }, 4);
  break;
case 0xa9:
  exec_instruction([&] () { instr_xor(_af.high, _bc.low); }, 4);
  break;
case 0xaa:
  exec_instruction([&] () { instr_xor(_af.high, _de.high); }, 4);
  break;
case 0xab:
  exec_instruction([&] () { instr_xor(_af.high, _de.low); }, 4);
  break;
case 0xac:
  exec_instruction([&] () { instr_xor(_af.high, _hl.high); }, 4);
  break;
case 0xad:
  exec_instruction([&] () { instr_xor(_af.high, _hl.low); }, 4);
  break;
case 0xae:
  exec_instruction([&] () { instr_xor(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0xaf:
  exec_instruction([&] () { instr_xor(_af.high, _af.high); }, 4);
  break;
case 0xb0:
  exec_instruction([&] () { instr_or(_af.high, _bc.high); }, 4);
  break;
case 0xb1:
  exec_instruction([&] () { instr_or(_af.high, _bc.low); }, 4);
  break;
case 0xb2:
  exec_instruction([&] () { instr_or(_af.high, _de.high); }, 4);
  break;
case 0xb3:
  exec_instruction([&] () { instr_or(_af.high, _de.low); }, 4);
  break;
case 0xb4:
  exec_instruction([&] () { instr_or(_af.high, _hl.high); }, 4);
  break;
case 0xb5:
  exec_instruction([&] () { instr_or(_af.high, _hl.low); }, 4);
  break;
case 0xb6:
  exec_instruction([&] () { instr_or(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0xb7:
  exec_instruction([&] () { instr_or(_af.high, _af.high); }, 4);
  break;
case 0xb8:
  exec_instruction([&] () { instr_cp(_af.high, _bc.high); }, 4);
  break;
case 0xb9:
  exec_instruction([&] () { instr_cp(_af.high, _bc.low); }, 4);
  break;
case 0xba:
  exec_instruction([&] () { instr_cp(_af.high, _de.high); }, 4);
  break;
case 0xbb:
  exec_instruction([&] () { instr_cp(_af.high, _de.low); }, 4);
  break;
case 0xbc:
  exec_instruction([&] () { instr_cp(_af.high, _hl.high); }, 4);
  break;
case 0xbd:
  exec_instruction([&] () { instr_cp(_af.high, _hl.low); }, 4);
  break;
case 0xbe:
  exec_instruction([&] () { instr_cp(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
  break;
case 0xbf:
  exec_instruction([&] () { instr_cp(_af.high, _af.high); }, 4);
  break;
case 0xc0:
  exec_instruction([&] () { instr_ret(JumpCondition::NonZero); }, 20, 8);
  break;
case 0xc1:
  exec_instruction([&] () { instr_pop(_bc.word); }, 12);
  break;
case 0xc2:
  exec_instruction([&] () { instr_jp(JumpCondition::NonZero, fetch_word()); }, 16, 12);
  break;
case 0xc3:
  exec_instruction([&] () { instr_jp(fetch_word()); }, 16);
  break;
case 0xc4:
  exec_instruction([&] () { instr_call(JumpCondition::NonZero, fetch_word()); }, 24, 12);
  break;
case 0xc5:
  exec_instruction([&] () { instr_push(_bc.word); }, 16);
  break;
case 0xc6:
  exec_instruction([&] () { instr_add(_af.high, *it++); }, 8);
  break;
case 0xc7:
  exec_instruction([&] () { instr_rst(0x00); }, 16);
  break;
case 0xc8:
  exec_instruction([&] () { instr_ret(JumpCondition::Zero); }, 20, 8);
  break;
case 0xc9:
  exec_instruction([&] () { instr_ret(); }, 16);
  break;
case 0xca:
  exec_instruction([&] () { instr_jp(JumpCondition::Zero, fetch_word()); }, 16, 12);
  break;
case 0xcc:
  exec_instruction([&] () { instr_call(JumpCondition::Zero, fetch_word()); }, 24, 12);
  break;
case 0xcd:
  exec_instruction([&] () { instr_call(fetch_word()); }, 24);
  break;
case 0xce:
  exec_instruction([&] () { instr_adc(_af.high, *it++); }, 8);
  break;
case 0xcf:
  exec_instruction([&] () { instr_rst(0x08); }, 16);
  break;
case 0xd0:
  exec_instruction([&] () { instr_ret(JumpCondition::NonCarry); }, 20, 8);
  break;
case 0xd1:
  exec_instruction([&] () { instr_pop(_de.word); }, 12);
  break;
case 0xd2:
  exec_instruction([&] () { instr_jp(JumpCondition::NonCarry, fetch_word()); }, 16, 12);
  break;
case 0xd4:
  exec_instruction([&] () { instr_call(JumpCondition::NonCarry, fetch_word()); }, 24, 12);
  break;
case 0xd5:
  exec_instruction([&] () { instr_push(_de.word); }, 16);
  break;
case 0xd6:
  exec_instruction([&] () { instr_sub(_af.high, *it++); }, 8);
  break;
case 0xd7:
  exec_instruction([&] () { instr_rst(0x10); }, 16);
  break;
case 0xd8:
  exec_instruction([&] () { instr_ret(JumpCondition::Carry); }, 20, 8);
  break;
case 0xd9:
  exec_instruction([&] () { instr_reti(); }, 16);
  break;
case 0xda:
  exec_instruction([&] () { instr_jp(JumpCondition::Carry, fetch_word()); }, 16, 12);
  break;
case 0xdc:
  exec_instruction([&] () { instr_call(JumpCondition::Carry, fetch_word()); }, 24, 12);
  break;
case 0xde:
  exec_instruction([&] () { instr_sbc(_af.high, *it++); }, 8);
  break;
case 0xdf:
  exec_instruction([&] () { instr_rst(0x18); }, 16);
  break;
case 0xe0:
  exec_instruction([&] (Byte &v) { instr_ldh(v, _af.high); }, 0xFF00 + *it++, 12);
  break;
case 0xe1:
  exec_instruction([&] () { instr_pop(_hl.word); }, 12);
  break;
case 0xe2:
  exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, 0xFF00 + _bc.low, 8);
  break;
case 0xe5:
  exec_instruction([&] () { instr_push(_hl.word); }, 16);
  break;
case 0xe6:
  exec_instruction([&] () { instr_and(_af.high, *it++); }, 8);
  break;
case 0xe7:
  exec_instruction([&] () { instr_rst(0x20); }, 16);
  break;
case 0xe8:
  exec_instruction([&] () { instr_add(_sp.word, *it++); }, 16);
  break;
case 0xe9:
  exec_instruction([&] (Byte &v) { instr_jp(v); }, _hl.word, 4);
  break;
case 0xea:
  exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, fetch_word(), 16);
  break;
case 0xee:
  exec_instruction([&] () { instr_xor(_af.high, *it++); }, 8);
  break;
case 0xef:
  exec_instruction([&] () { instr_rst(0x28); }, 16);
  break;
case 0xf0:
  exec_instruction([&] () { instr_ldh(_af.high, _components.mem_bus->read<Byte>(0xFF00 + *it++)); }, 12);
  break;
case 0xf1:
  exec_instruction([&] () { instr_pop(_af.word); }, 12);
  break;
case 0xf2:
  exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(0xFF00 + _bc.low)); }, 8);
  break;
case 0xf3:
  exec_instruction([&] () { instr_di(); }, 4);
  break;
case 0xf5:
  exec_instruction([&] () { instr_push(_af.word); }, 16);
  break;
case 0xf6:
  exec_instruction([&] () { instr_or(_af.high, *it++); }, 8);
  break;
case 0xf7:
  exec_instruction([&] () { instr_rst(0x30); }, 16);
  break;
case 0xf8:
  exec_instruction([&] () { instr_ld(_hl.word, static_cast<Word>(_sp.word + *it++)); }, 12);
  break;
case 0xf9:
  exec_instruction([&] () { instr_ld(_sp.word, _hl.word); }, 8);
  break;
case 0xfa:
  exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(fetch_word())); }, 16);
  break;
case 0xfb:
  exec_instruction([&] () { instr_ei(); }, 4);
  break;
case 0xfe:
  exec_instruction([&] () { instr_cp(_af.high, *it++); }, 8);
  break;
case 0xff:
  exec_instruction([&] () { instr_rst(0x38); }, 16);
  break;
  case 0xCB:
switch (*it++) {
case 0x0:
  exec_instruction([&] () { instr_rlc(_bc.high); }, 8);
  break;
case 0x1:
  exec_instruction([&] () { instr_rlc(_bc.low); }, 8);
  break;
case 0x2:
  exec_instruction([&] () { instr_rlc(_de.high); }, 8);
  break;
case 0x3:
  exec_instruction([&] () { instr_rlc(_de.low); }, 8);
  break;
case 0x4:
  exec_instruction([&] () { instr_rlc(_hl.high); }, 8);
  break;
case 0x5:
  exec_instruction([&] () { instr_rlc(_hl.low); }, 8);
  break;
case 0x6:
  exec_instruction([&] (Byte &v) { instr_rlc(v); }, _hl.word, 16);
  break;
case 0x7:
  exec_instruction([&] () { instr_rlc(_af.high); }, 8);
  break;
case 0x8:
  exec_instruction([&] () { instr_rrc(_bc.high); }, 8);
  break;
case 0x9:
  exec_instruction([&] () { instr_rrc(_bc.low); }, 8);
  break;
case 0xa:
  exec_instruction([&] () { instr_rrc(_de.high); }, 8);
  break;
case 0xb:
  exec_instruction([&] () { instr_rrc(_de.low); }, 8);
  break;
case 0xc:
  exec_instruction([&] () { instr_rrc(_hl.high); }, 8);
  break;
case 0xd:
  exec_instruction([&] () { instr_rrc(_hl.low); }, 8);
  break;
case 0xe:
  exec_instruction([&] (Byte &v) { instr_rrc(v); }, _hl.word, 16);
  break;
case 0xf:
  exec_instruction([&] () { instr_rrc(_af.high); }, 8);
  break;
case 0x10:
  exec_instruction([&] () { instr_rl(_bc.high); }, 8);
  break;
case 0x11:
  exec_instruction([&] () { instr_rl(_bc.low); }, 8);
  break;
case 0x12:
  exec_instruction([&] () { instr_rl(_de.high); }, 8);
  break;
case 0x13:
  exec_instruction([&] () { instr_rl(_de.low); }, 8);
  break;
case 0x14:
  exec_instruction([&] () { instr_rl(_hl.high); }, 8);
  break;
case 0x15:
  exec_instruction([&] () { instr_rl(_hl.low); }, 8);
  break;
case 0x16:
  exec_instruction([&] (Byte &v) { instr_rl(v); }, _hl.word, 16);
  break;
case 0x17:
  exec_instruction([&] () { instr_rl(_af.high); }, 8);
  break;
case 0x18:
  exec_instruction([&] () { instr_rr(_bc.high); }, 8);
  break;
case 0x19:
  exec_instruction([&] () { instr_rr(_bc.low); }, 8);
  break;
case 0x1a:
  exec_instruction([&] () { instr_rr(_de.high); }, 8);
  break;
case 0x1b:
  exec_instruction([&] () { instr_rr(_de.low); }, 8);
  break;
case 0x1c:
  exec_instruction([&] () { instr_rr(_hl.high); }, 8);
  break;
case 0x1d:
  exec_instruction([&] () { instr_rr(_hl.low); }, 8);
  break;
case 0x1e:
  exec_instruction([&] (Byte &v) { instr_rr(v); }, _hl.word, 16);
  break;
case 0x1f:
  exec_instruction([&] () { instr_rr(_af.high); }, 8);
  break;
case 0x20:
  exec_instruction([&] () { instr_sla(_bc.high); }, 8);
  break;
case 0x21:
  exec_instruction([&] () { instr_sla(_bc.low); }, 8);
  break;
case 0x22:
  exec_instruction([&] () { instr_sla(_de.high); }, 8);
  break;
case 0x23:
  exec_instruction([&] () { instr_sla(_de.low); }, 8);
  break;
case 0x24:
  exec_instruction([&] () { instr_sla(_hl.high); }, 8);
  break;
case 0x25:
  exec_instruction([&] () { instr_sla(_hl.low); }, 8);
  break;
case 0x26:
  exec_instruction([&] (Byte &v) { instr_sla(v); }, _hl.word, 16);
  break;
case 0x27:
  exec_instruction([&] () { instr_sla(_af.high); }, 8);
  break;
case 0x28:
  exec_instruction([&] () { instr_sra(_bc.high); }, 8);
  break;
case 0x29:
  exec_instruction([&] () { instr_sra(_bc.low); }, 8);
  break;
case 0x2a:
  exec_instruction([&] () { instr_sra(_de.high); }, 8);
  break;
case 0x2b:
  exec_instruction([&] () { instr_sra(_de.low); }, 8);
  break;
case 0x2c:
  exec_instruction([&] () { instr_sra(_hl.high); }, 8);
  break;
case 0x2d:
  exec_instruction([&] () { instr_sra(_hl.low); }, 8);
  break;
case 0x2e:
  exec_instruction([&] (Byte &v) { instr_sra(v); }, _hl.word, 16);
  break;
case 0x2f:
  exec_instruction([&] () { instr_sra(_af.high); }, 8);
  break;
case 0x30:
  exec_instruction([&] () { instr_swap(_bc.high); }, 8);
  break;
case 0x31:
  exec_instruction([&] () { instr_swap(_bc.low); }, 8);
  break;
case 0x32:
  exec_instruction([&] () { instr_swap(_de.high); }, 8);
  break;
case 0x33:
  exec_instruction([&] () { instr_swap(_de.low); }, 8);
  break;
case 0x34:
  exec_instruction([&] () { instr_swap(_hl.high); }, 8);
  break;
case 0x35:
  exec_instruction([&] () { instr_swap(_hl.low); }, 8);
  break;
case 0x36:
  exec_instruction([&] (Byte &v) { instr_swap(v); }, _hl.word, 16);
  break;
case 0x37:
  exec_instruction([&] () { instr_swap(_af.high); }, 8);
  break;
case 0x38:
  exec_instruction([&] () { instr_srl(_bc.high); }, 8);
  break;
case 0x39:
  exec_instruction([&] () { instr_srl(_bc.low); }, 8);
  break;
case 0x3a:
  exec_instruction([&] () { instr_srl(_de.high); }, 8);
  break;
case 0x3b:
  exec_instruction([&] () { instr_srl(_de.low); }, 8);
  break;
case 0x3c:
  exec_instruction([&] () { instr_srl(_hl.high); }, 8);
  break;
case 0x3d:
  exec_instruction([&] () { instr_srl(_hl.low); }, 8);
  break;
case 0x3e:
  exec_instruction([&] (Byte &v) { instr_srl(v); }, _hl.word, 16);
  break;
case 0x3f:
  exec_instruction([&] () { instr_srl(_af.high); }, 8);
  break;
case 0x40:
  exec_instruction([&] () { instr_bit(0, _bc.high); }, 8);
  break;
case 0x41:
  exec_instruction([&] () { instr_bit(0, _bc.low); }, 8);
  break;
case 0x42:
  exec_instruction([&] () { instr_bit(0, _de.high); }, 8);
  break;
case 0x43:
  exec_instruction([&] () { instr_bit(0, _de.low); }, 8);
  break;
case 0x44:
  exec_instruction([&] () { instr_bit(0, _hl.high); }, 8);
  break;
case 0x45:
  exec_instruction([&] () { instr_bit(0, _hl.low); }, 8);
  break;
case 0x46:
  exec_instruction([&] (Byte &v) { instr_bit(0, v); }, _hl.word, 16);
  break;
case 0x47:
  exec_instruction([&] () { instr_bit(0, _af.high); }, 8);
  break;
case 0x48:
  exec_instruction([&] () { instr_bit(1, _bc.high); }, 8);
  break;
case 0x49:
  exec_instruction([&] () { instr_bit(1, _bc.low); }, 8);
  break;
case 0x4a:
  exec_instruction([&] () { instr_bit(1, _de.high); }, 8);
  break;
case 0x4b:
  exec_instruction([&] () { instr_bit(1, _de.low); }, 8);
  break;
case 0x4c:
  exec_instruction([&] () { instr_bit(1, _hl.high); }, 8);
  break;
case 0x4d:
  exec_instruction([&] () { instr_bit(1, _hl.low); }, 8);
  break;
case 0x4e:
  exec_instruction([&] (Byte &v) { instr_bit(1, v); }, _hl.word, 16);
  break;
case 0x4f:
  exec_instruction([&] () { instr_bit(1, _af.high); }, 8);
  break;
case 0x50:
  exec_instruction([&] () { instr_bit(2, _bc.high); }, 8);
  break;
case 0x51:
  exec_instruction([&] () { instr_bit(2, _bc.low); }, 8);
  break;
case 0x52:
  exec_instruction([&] () { instr_bit(2, _de.high); }, 8);
  break;
case 0x53:
  exec_instruction([&] () { instr_bit(2, _de.low); }, 8);
  break;
case 0x54:
  exec_instruction([&] () { instr_bit(2, _hl.high); }, 8);
  break;
case 0x55:
  exec_instruction([&] () { instr_bit(2, _hl.low); }, 8);
  break;
case 0x56:
  exec_instruction([&] (Byte &v) { instr_bit(2, v); }, _hl.word, 16);
  break;
case 0x57:
  exec_instruction([&] () { instr_bit(2, _af.high); }, 8);
  break;
case 0x58:
  exec_instruction([&] () { instr_bit(3, _bc.high); }, 8);
  break;
case 0x59:
  exec_instruction([&] () { instr_bit(3, _bc.low); }, 8);
  break;
case 0x5a:
  exec_instruction([&] () { instr_bit(3, _de.high); }, 8);
  break;
case 0x5b:
  exec_instruction([&] () { instr_bit(3, _de.low); }, 8);
  break;
case 0x5c:
  exec_instruction([&] () { instr_bit(3, _hl.high); }, 8);
  break;
case 0x5d:
  exec_instruction([&] () { instr_bit(3, _hl.low); }, 8);
  break;
case 0x5e:
  exec_instruction([&] (Byte &v) { instr_bit(3, v); }, _hl.word, 16);
  break;
case 0x5f:
  exec_instruction([&] () { instr_bit(3, _af.high); }, 8);
  break;
case 0x60:
  exec_instruction([&] () { instr_bit(4, _bc.high); }, 8);
  break;
case 0x61:
  exec_instruction([&] () { instr_bit(4, _bc.low); }, 8);
  break;
case 0x62:
  exec_instruction([&] () { instr_bit(4, _de.high); }, 8);
  break;
case 0x63:
  exec_instruction([&] () { instr_bit(4, _de.low); }, 8);
  break;
case 0x64:
  exec_instruction([&] () { instr_bit(4, _hl.high); }, 8);
  break;
case 0x65:
  exec_instruction([&] () { instr_bit(4, _hl.low); }, 8);
  break;
case 0x66:
  exec_instruction([&] (Byte &v) { instr_bit(4, v); }, _hl.word, 16);
  break;
case 0x67:
  exec_instruction([&] () { instr_bit(4, _af.high); }, 8);
  break;
case 0x68:
  exec_instruction([&] () { instr_bit(5, _bc.high); }, 8);
  break;
case 0x69:
  exec_instruction([&] () { instr_bit(5, _bc.low); }, 8);
  break;
case 0x6a:
  exec_instruction([&] () { instr_bit(5, _de.high); }, 8);
  break;
case 0x6b:
  exec_instruction([&] () { instr_bit(5, _de.low); }, 8);
  break;
case 0x6c:
  exec_instruction([&] () { instr_bit(5, _hl.high); }, 8);
  break;
case 0x6d:
  exec_instruction([&] () { instr_bit(5, _hl.low); }, 8);
  break;
case 0x6e:
  exec_instruction([&] (Byte &v) { instr_bit(5, v); }, _hl.word, 16);
  break;
case 0x6f:
  exec_instruction([&] () { instr_bit(5, _af.high); }, 8);
  break;
case 0x70:
  exec_instruction([&] () { instr_bit(6, _bc.high); }, 8);
  break;
case 0x71:
  exec_instruction([&] () { instr_bit(6, _bc.low); }, 8);
  break;
case 0x72:
  exec_instruction([&] () { instr_bit(6, _de.high); }, 8);
  break;
case 0x73:
  exec_instruction([&] () { instr_bit(6, _de.low); }, 8);
  break;
case 0x74:
  exec_instruction([&] () { instr_bit(6, _hl.high); }, 8);
  break;
case 0x75:
  exec_instruction([&] () { instr_bit(6, _hl.low); }, 8);
  break;
case 0x76:
  exec_instruction([&] (Byte &v) { instr_bit(6, v); }, _hl.word, 16);
  break;
case 0x77:
  exec_instruction([&] () { instr_bit(6, _af.high); }, 8);
  break;
case 0x78:
  exec_instruction([&] () { instr_bit(7, _bc.high); }, 8);
  break;
case 0x79:
  exec_instruction([&] () { instr_bit(7, _bc.low); }, 8);
  break;
case 0x7a:
  exec_instruction([&] () { instr_bit(7, _de.high); }, 8);
  break;
case 0x7b:
  exec_instruction([&] () { instr_bit(7, _de.low); }, 8);
  break;
case 0x7c:
  exec_instruction([&] () { instr_bit(7, _hl.high); }, 8);
  break;
case 0x7d:
  exec_instruction([&] () { instr_bit(7, _hl.low); }, 8);
  break;
case 0x7e:
  exec_instruction([&] (Byte &v) { instr_bit(7, v); }, _hl.word, 16);
  break;
case 0x7f:
  exec_instruction([&] () { instr_bit(7, _af.high); }, 8);
  break;
case 0x80:
  exec_instruction([&] () { instr_res(0, _bc.high); }, 8);
  break;
case 0x81:
  exec_instruction([&] () { instr_res(0, _bc.low); }, 8);
  break;
case 0x82:
  exec_instruction([&] () { instr_res(0, _de.high); }, 8);
  break;
case 0x83:
  exec_instruction([&] () { instr_res(0, _de.low); }, 8);
  break;
case 0x84:
  exec_instruction([&] () { instr_res(0, _hl.high); }, 8);
  break;
case 0x85:
  exec_instruction([&] () { instr_res(0, _hl.low); }, 8);
  break;
case 0x86:
  exec_instruction([&] (Byte &v) { instr_res(0, v); }, _hl.word, 16);
  break;
case 0x87:
  exec_instruction([&] () { instr_res(0, _af.high); }, 8);
  break;
case 0x88:
  exec_instruction([&] () { instr_res(1, _bc.high); }, 8);
  break;
case 0x89:
  exec_instruction([&] () { instr_res(1, _bc.low); }, 8);
  break;
case 0x8a:
  exec_instruction([&] () { instr_res(1, _de.high); }, 8);
  break;
case 0x8b:
  exec_instruction([&] () { instr_res(1, _de.low); }, 8);
  break;
case 0x8c:
  exec_instruction([&] () { instr_res(1, _hl.high); }, 8);
  break;
case 0x8d:
  exec_instruction([&] () { instr_res(1, _hl.low); }, 8);
  break;
case 0x8e:
  exec_instruction([&] (Byte &v) { instr_res(1, v); }, _hl.word, 16);
  break;
case 0x8f:
  exec_instruction([&] () { instr_res(1, _af.high); }, 8);
  break;
case 0x90:
  exec_instruction([&] () { instr_res(2, _bc.high); }, 8);
  break;
case 0x91:
  exec_instruction([&] () { instr_res(2, _bc.low); }, 8);
  break;
case 0x92:
  exec_instruction([&] () { instr_res(2, _de.high); }, 8);
  break;
case 0x93:
  exec_instruction([&] () { instr_res(2, _de.low); }, 8);
  break;
case 0x94:
  exec_instruction([&] () { instr_res(2, _hl.high); }, 8);
  break;
case 0x95:
  exec_instruction([&] () { instr_res(2, _hl.low); }, 8);
  break;
case 0x96:
  exec_instruction([&] (Byte &v) { instr_res(2, v); }, _hl.word, 16);
  break;
case 0x97:
  exec_instruction([&] () { instr_res(2, _af.high); }, 8);
  break;
case 0x98:
  exec_instruction([&] () { instr_res(3, _bc.high); }, 8);
  break;
case 0x99:
  exec_instruction([&] () { instr_res(3, _bc.low); }, 8);
  break;
case 0x9a:
  exec_instruction([&] () { instr_res(3, _de.high); }, 8);
  break;
case 0x9b:
  exec_instruction([&] () { instr_res(3, _de.low); }, 8);
  break;
case 0x9c:
  exec_instruction([&] () { instr_res(3, _hl.high); }, 8);
  break;
case 0x9d:
  exec_instruction([&] () { instr_res(3, _hl.low); }, 8);
  break;
case 0x9e:
  exec_instruction([&] (Byte &v) { instr_res(3, v); }, _hl.word, 16);
  break;
case 0x9f:
  exec_instruction([&] () { instr_res(3, _af.high); }, 8);
  break;
case 0xa0:
  exec_instruction([&] () { instr_res(4, _bc.high); }, 8);
  break;
case 0xa1:
  exec_instruction([&] () { instr_res(4, _bc.low); }, 8);
  break;
case 0xa2:
  exec_instruction([&] () { instr_res(4, _de.high); }, 8);
  break;
case 0xa3:
  exec_instruction([&] () { instr_res(4, _de.low); }, 8);
  break;
case 0xa4:
  exec_instruction([&] () { instr_res(4, _hl.high); }, 8);
  break;
case 0xa5:
  exec_instruction([&] () { instr_res(4, _hl.low); }, 8);
  break;
case 0xa6:
  exec_instruction([&] (Byte &v) { instr_res(4, v); }, _hl.word, 16);
  break;
case 0xa7:
  exec_instruction([&] () { instr_res(4, _af.high); }, 8);
  break;
case 0xa8:
  exec_instruction([&] () { instr_res(5, _bc.high); }, 8);
  break;
case 0xa9:
  exec_instruction([&] () { instr_res(5, _bc.low); }, 8);
  break;
case 0xaa:
  exec_instruction([&] () { instr_res(5, _de.high); }, 8);
  break;
case 0xab:
  exec_instruction([&] () { instr_res(5, _de.low); }, 8);
  break;
case 0xac:
  exec_instruction([&] () { instr_res(5, _hl.high); }, 8);
  break;
case 0xad:
  exec_instruction([&] () { instr_res(5, _hl.low); }, 8);
  break;
case 0xae:
  exec_instruction([&] (Byte &v) { instr_res(5, v); }, _hl.word, 16);
  break;
case 0xaf:
  exec_instruction([&] () { instr_res(5, _af.high); }, 8);
  break;
case 0xb0:
  exec_instruction([&] () { instr_res(6, _bc.high); }, 8);
  break;
case 0xb1:
  exec_instruction([&] () { instr_res(6, _bc.low); }, 8);
  break;
case 0xb2:
  exec_instruction([&] () { instr_res(6, _de.high); }, 8);
  break;
case 0xb3:
  exec_instruction([&] () { instr_res(6, _de.low); }, 8);
  break;
case 0xb4:
  exec_instruction([&] () { instr_res(6, _hl.high); }, 8);
  break;
case 0xb5:
  exec_instruction([&] () { instr_res(6, _hl.low); }, 8);
  break;
case 0xb6:
  exec_instruction([&] (Byte &v) { instr_res(6, v); }, _hl.word, 16);
  break;
case 0xb7:
  exec_instruction([&] () { instr_res(6, _af.high); }, 8);
  break;
case 0xb8:
  exec_instruction([&] () { instr_res(7, _bc.high); }, 8);
  break;
case 0xb9:
  exec_instruction([&] () { instr_res(7, _bc.low); }, 8);
  break;
case 0xba:
  exec_instruction([&] () { instr_res(7, _de.high); }, 8);
  break;
case 0xbb:
  exec_instruction([&] () { instr_res(7, _de.low); }, 8);
  break;
case 0xbc:
  exec_instruction([&] () { instr_res(7, _hl.high); }, 8);
  break;
case 0xbd:
  exec_instruction([&] () { instr_res(7, _hl.low); }, 8);
  break;
case 0xbe:
  exec_instruction([&] (Byte &v) { instr_res(7, v); }, _hl.word, 16);
  break;
case 0xbf:
  exec_instruction([&] () { instr_res(7, _af.high); }, 8);
  break;
case 0xc0:
  exec_instruction([&] () { instr_set(0, _bc.high); }, 8);
  break;
case 0xc1:
  exec_instruction([&] () { instr_set(0, _bc.low); }, 8);
  break;
case 0xc2:
  exec_instruction([&] () { instr_set(0, _de.high); }, 8);
  break;
case 0xc3:
  exec_instruction([&] () { instr_set(0, _de.low); }, 8);
  break;
case 0xc4:
  exec_instruction([&] () { instr_set(0, _hl.high); }, 8);
  break;
case 0xc5:
  exec_instruction([&] () { instr_set(0, _hl.low); }, 8);
  break;
case 0xc6:
  exec_instruction([&] (Byte &v) { instr_set(0, v); }, _hl.word, 16);
  break;
case 0xc7:
  exec_instruction([&] () { instr_set(0, _af.high); }, 8);
  break;
case 0xc8:
  exec_instruction([&] () { instr_set(1, _bc.high); }, 8);
  break;
case 0xc9:
  exec_instruction([&] () { instr_set(1, _bc.low); }, 8);
  break;
case 0xca:
  exec_instruction([&] () { instr_set(1, _de.high); }, 8);
  break;
case 0xcb:
  exec_instruction([&] () { instr_set(1, _de.low); }, 8);
  break;
case 0xcc:
  exec_instruction([&] () { instr_set(1, _hl.high); }, 8);
  break;
case 0xcd:
  exec_instruction([&] () { instr_set(1, _hl.low); }, 8);
  break;
case 0xce:
  exec_instruction([&] (Byte &v) { instr_set(1, v); }, _hl.word, 16);
  break;
case 0xcf:
  exec_instruction([&] () { instr_set(1, _af.high); }, 8);
  break;
case 0xd0:
  exec_instruction([&] () { instr_set(2, _bc.high); }, 8);
  break;
case 0xd1:
  exec_instruction([&] () { instr_set(2, _bc.low); }, 8);
  break;
case 0xd2:
  exec_instruction([&] () { instr_set(2, _de.high); }, 8);
  break;
case 0xd3:
  exec_instruction([&] () { instr_set(2, _de.low); }, 8);
  break;
case 0xd4:
  exec_instruction([&] () { instr_set(2, _hl.high); }, 8);
  break;
case 0xd5:
  exec_instruction([&] () { instr_set(2, _hl.low); }, 8);
  break;
case 0xd6:
  exec_instruction([&] (Byte &v) { instr_set(2, v); }, _hl.word, 16);
  break;
case 0xd7:
  exec_instruction([&] () { instr_set(2, _af.high); }, 8);
  break;
case 0xd8:
  exec_instruction([&] () { instr_set(3, _bc.high); }, 8);
  break;
case 0xd9:
  exec_instruction([&] () { instr_set(3, _bc.low); }, 8);
  break;
case 0xda:
  exec_instruction([&] () { instr_set(3, _de.high); }, 8);
  break;
case 0xdb:
  exec_instruction([&] () { instr_set(3, _de.low); }, 8);
  break;
case 0xdc:
  exec_instruction([&] () { instr_set(3, _hl.high); }, 8);
  break;
case 0xdd:
  exec_instruction([&] () { instr_set(3, _hl.low); }, 8);
  break;
case 0xde:
  exec_instruction([&] (Byte &v) { instr_set(3, v); }, _hl.word, 16);
  break;
case 0xdf:
  exec_instruction([&] () { instr_set(3, _af.high); }, 8);
  break;
case 0xe0:
  exec_instruction([&] () { instr_set(4, _bc.high); }, 8);
  break;
case 0xe1:
  exec_instruction([&] () { instr_set(4, _bc.low); }, 8);
  break;
case 0xe2:
  exec_instruction([&] () { instr_set(4, _de.high); }, 8);
  break;
case 0xe3:
  exec_instruction([&] () { instr_set(4, _de.low); }, 8);
  break;
case 0xe4:
  exec_instruction([&] () { instr_set(4, _hl.high); }, 8);
  break;
case 0xe5:
  exec_instruction([&] () { instr_set(4, _hl.low); }, 8);
  break;
case 0xe6:
  exec_instruction([&] (Byte &v) { instr_set(4, v); }, _hl.word, 16);
  break;
case 0xe7:
  exec_instruction([&] () { instr_set(4, _af.high); }, 8);
  break;
case 0xe8:
  exec_instruction([&] () { instr_set(5, _bc.high); }, 8);
  break;
case 0xe9:
  exec_instruction([&] () { instr_set(5, _bc.low); }, 8);
  break;
case 0xea:
  exec_instruction([&] () { instr_set(5, _de.high); }, 8);
  break;
case 0xeb:
  exec_instruction([&] () { instr_set(5, _de.low); }, 8);
  break;
case 0xec:
  exec_instruction([&] () { instr_set(5, _hl.high); }, 8);
  break;
case 0xed:
  exec_instruction([&] () { instr_set(5, _hl.low); }, 8);
  break;
case 0xee:
  exec_instruction([&] (Byte &v) { instr_set(5, v); }, _hl.word, 16);
  break;
case 0xef:
  exec_instruction([&] () { instr_set(5, _af.high); }, 8);
  break;
case 0xf0:
  exec_instruction([&] () { instr_set(6, _bc.high); }, 8);
  break;
case 0xf1:
  exec_instruction([&] () { instr_set(6, _bc.low); }, 8);
  break;
case 0xf2:
  exec_instruction([&] () { instr_set(6, _de.high); }, 8);
  break;
case 0xf3:
  exec_instruction([&] () { instr_set(6, _de.low); }, 8);
  break;
case 0xf4:
  exec_instruction([&] () { instr_set(6, _hl.high); }, 8);
  break;
case 0xf5:
  exec_instruction([&] () { instr_set(6, _hl.low); }, 8);
  break;
case 0xf6:
  exec_instruction([&] (Byte &v) { instr_set(6, v); }, _hl.word, 16);
  break;
case 0xf7:
  exec_instruction([&] () { instr_set(6, _af.high); }, 8);
  break;
case 0xf8:
  exec_instruction([&] () { instr_set(7, _bc.high); }, 8);
  break;
case 0xf9:
  exec_instruction([&] () { instr_set(7, _bc.low); }, 8);
  break;
case 0xfa:
  exec_instruction([&] () { instr_set(7, _de.high); }, 8);
  break;
case 0xfb:
  exec_instruction([&] () { instr_set(7, _de.low); }, 8);
  break;
case 0xfc:
  exec_instruction([&] () { instr_set(7, _hl.high); }, 8);
  break;
case 0xfd:
  exec_instruction([&] () { instr_set(7, _hl.low); }, 8);
  break;
case 0xfe:
  exec_instruction([&] (Byte &v) { instr_set(7, v); }, _hl.word, 16);
  break;
case 0xff:
  exec_instruction([&] () { instr_set(7, _af.high); }, 8);
  break;
}
