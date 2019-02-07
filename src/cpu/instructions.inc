case 0x06:
exec_instruction([&] () { instr_ld(_bc.high, *it++); }, 8);
break;
case 0x0E:
exec_instruction([&] () { instr_ld(_bc.low, *it++); }, 8);
break;
case 0x16:
exec_instruction([&] () { instr_ld(_de.high, *it++); }, 8);
break;
case 0x1E:
exec_instruction([&] () { instr_ld(_de.low, *it++); }, 8);
break;
case 0x26:
exec_instruction([&] () { instr_ld(_hl.high, *it++); }, 8);
break;
case 0x2E:
exec_instruction([&] () { instr_ld(_hl.low, *it++); }, 8);
break;
case 0x7F:
exec_instruction([&] () { instr_ld(_af.high, _af.high); }, 4);
break;
case 0x78:
exec_instruction([&] () { instr_ld(_af.high, _bc.high); }, 4);
break;
case 0x79:
exec_instruction([&] () { instr_ld(_af.high, _bc.low); }, 4);
break;
case 0x7A:
exec_instruction([&] () { instr_ld(_af.high, _de.high); }, 4);
break;
case 0x7B:
exec_instruction([&] () { instr_ld(_af.high, _de.low); }, 4);
break;
case 0x7C:
exec_instruction([&] () { instr_ld(_af.high, _hl.high); }, 4);
break;
case 0x7D:
exec_instruction([&] () { instr_ld(_af.high, _hl.low); }, 4);
break;
case 0x7E:
exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
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
case 0x48:
exec_instruction([&] () { instr_ld(_bc.low, _bc.high); }, 4);
break;
case 0x49:
exec_instruction([&] () { instr_ld(_bc.low, _bc.low); }, 4);
break;
case 0x4A:
exec_instruction([&] () { instr_ld(_bc.low, _de.high); }, 4);
break;
case 0x4B:
exec_instruction([&] () { instr_ld(_bc.low, _de.low); }, 4);
break;
case 0x4C:
exec_instruction([&] () { instr_ld(_bc.low, _hl.high); }, 4);
break;
case 0x4D:
exec_instruction([&] () { instr_ld(_bc.low, _hl.low); }, 4);
break;
case 0x4E:
exec_instruction([&] () { instr_ld(_bc.low, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
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
case 0x58:
exec_instruction([&] () { instr_ld(_de.low, _bc.high); }, 4);
break;
case 0x59:
exec_instruction([&] () { instr_ld(_de.low, _bc.low); }, 4);
break;
case 0x5A:
exec_instruction([&] () { instr_ld(_de.low, _de.high); }, 4);
break;
case 0x5B:
exec_instruction([&] () { instr_ld(_de.low, _de.low); }, 4);
break;
case 0x5C:
exec_instruction([&] () { instr_ld(_de.low, _hl.high); }, 4);
break;
case 0x5D:
exec_instruction([&] () { instr_ld(_de.low, _hl.low); }, 4);
break;
case 0x5E:
exec_instruction([&] () { instr_ld(_de.low, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
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
case 0x68:
exec_instruction([&] () { instr_ld(_hl.low, _bc.high); }, 4);
break;
case 0x69:
exec_instruction([&] () { instr_ld(_hl.low, _bc.low); }, 4);
break;
case 0x6A:
exec_instruction([&] () { instr_ld(_hl.low, _de.high); }, 4);
break;
case 0x6B:
exec_instruction([&] () { instr_ld(_hl.low, _de.low); }, 4);
break;
case 0x6C:
exec_instruction([&] () { instr_ld(_hl.low, _hl.high); }, 4);
break;
case 0x6D:
exec_instruction([&] () { instr_ld(_hl.low, _hl.low); }, 4);
break;
case 0x6E:
exec_instruction([&] () { instr_ld(_hl.low, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
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
case 0x36:
exec_instruction([&] (Byte &v) { instr_ld(v, *it++); }, _hl.word, 12);
break;
case 0x0A:
exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(_bc.word)); }, 8);
break;
case 0x1A:
exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(_de.word)); }, 8);
break;
case 0xFA:
exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(fetch_word())); }, 16);
break;
case 0x3E:
exec_instruction([&] () { instr_ld(_af.high, *it++); }, 8);
break;
case 0x47:
exec_instruction([&] () { instr_ld(_bc.high, _af.high); }, 4);
break;
case 0x4F:
exec_instruction([&] () { instr_ld(_bc.low, _af.high); }, 4);
break;
case 0x57:
exec_instruction([&] () { instr_ld(_de.high, _af.high); }, 4);
break;
case 0x5F:
exec_instruction([&] () { instr_ld(_de.low, _af.high); }, 4);
break;
case 0x67:
exec_instruction([&] () { instr_ld(_hl.high, _af.high); }, 4);
break;
case 0x6F:
exec_instruction([&] () { instr_ld(_hl.low, _af.high); }, 4);
break;
case 0x02:
exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, _bc.word, 8);
break;
case 0x12:
exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, _de.word, 8);
break;
case 0x77:
exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, _hl.word, 8);
break;
case 0xEA:
exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, fetch_word(), 16);
break;
case 0xF2:
exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(_bc.low)); }, 8);
break;
case 0xE2:
exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, 0xFF00 + _bc.low, 8);
break;
case 0x3A:
exec_instruction([&] () { instr_ldd(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0x32:
exec_instruction([&] (Byte &v) { instr_ldd(v, _af.high); }, _hl.word, 8);
break;
case 0x2A:
exec_instruction([&] () { instr_ldi(_af.high, _hl.word); }, 8);
break;
case 0xF0:
exec_instruction([&] () { instr_ld(_af.high, _components.mem_bus->read<Byte>(0xFF00 + *it++)); }, 12);
break;
case 0x01:
exec_instruction([&] () { instr_ld(_bc.word, fetch_word()); }, 12);
break;
case 0x11:
exec_instruction([&] () { instr_ld(_de.word, fetch_word()); }, 12);
break;
case 0x21:
exec_instruction([&] () { instr_ld(_hl.word, fetch_word()); }, 12);
break;
case 0x31:
exec_instruction([&] () { instr_ld(_sp.word, fetch_word()); }, 12);
break;
case 0xF9:
exec_instruction([&] () { instr_ld(_sp.word, _hl.word); }, 8);
break;
case 0xF8:
exec_instruction([&] () { instr_ldhl(*it++); }, 12);
break;
case 0x08:
exec_instruction([&] (Word &v) { instr_ld(v, _sp.word); }, fetch_word(), 20);
break;
case 0xF5:
exec_instruction([&] () { instr_push(_af.word); }, 16);
break;
case 0xC5:
exec_instruction([&] () { instr_push(_bc.word); }, 16);
break;
case 0xD5:
exec_instruction([&] () { instr_push(_de.word); }, 16);
break;
case 0xE5:
exec_instruction([&] () { instr_push(_hl.word); }, 16);
break;
case 0xF1:
exec_instruction([&] () { instr_pop(_af.word); }, 12);
break;
case 0xC1:
exec_instruction([&] () { instr_pop(_bc.word); }, 12);
break;
case 0xD1:
exec_instruction([&] () { instr_pop(_de.word); }, 12);
break;
case 0xE1:
exec_instruction([&] () { instr_pop(_hl.word); }, 12);
break;
case 0x87:
exec_instruction([&] () { instr_add(_af.high, _af.high); }, 4);
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
case 0xC6:
exec_instruction([&] () { instr_add(_af.high, *it++); }, 8);
break;
case 0x8F:
exec_instruction([&] () { instr_adc(_af.high, _af.high); }, 4);
break;
case 0x88:
exec_instruction([&] () { instr_adc(_af.high, _bc.high); }, 4);
break;
case 0x89:
exec_instruction([&] () { instr_adc(_af.high, _bc.low); }, 4);
break;
case 0x8A:
exec_instruction([&] () { instr_adc(_af.high, _de.high); }, 4);
break;
case 0x8B:
exec_instruction([&] () { instr_adc(_af.high, _de.low); }, 4);
break;
case 0x8C:
exec_instruction([&] () { instr_adc(_af.high, _hl.high); }, 4);
break;
case 0x8D:
exec_instruction([&] () { instr_adc(_af.high, _hl.low); }, 4);
break;
case 0x8E:
exec_instruction([&] () { instr_adc(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0xCE:
exec_instruction([&] () { instr_adc(_af.high, *it++); }, 8);
break;
case 0x97:
exec_instruction([&] () { instr_sub(_af.high, _af.high); }, 4);
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
case 0xD6:
exec_instruction([&] () { instr_sub(_af.high, *it++); }, 8);
break;
case 0x9F:
exec_instruction([&] () { instr_sbc(_af.high, _af.high); }, 4);
break;
case 0x98:
exec_instruction([&] () { instr_sbc(_af.high, _bc.high); }, 4);
break;
case 0x99:
exec_instruction([&] () { instr_sbc(_af.high, _bc.low); }, 4);
break;
case 0x9A:
exec_instruction([&] () { instr_sbc(_af.high, _de.high); }, 4);
break;
case 0x9B:
exec_instruction([&] () { instr_sbc(_af.high, _de.low); }, 4);
break;
case 0x9C:
exec_instruction([&] () { instr_sbc(_af.high, _hl.high); }, 4);
break;
case 0x9D:
exec_instruction([&] () { instr_sbc(_af.high, _hl.low); }, 4);
break;
case 0x9E:
exec_instruction([&] () { instr_sbc(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0xA7:
exec_instruction([&] () { instr_and(_af.high, _af.high); }, 4);
break;
case 0xA0:
exec_instruction([&] () { instr_and(_af.high, _bc.high); }, 4);
break;
case 0xA1:
exec_instruction([&] () { instr_and(_af.high, _bc.low); }, 4);
break;
case 0xA2:
exec_instruction([&] () { instr_and(_af.high, _de.high); }, 4);
break;
case 0xA3:
exec_instruction([&] () { instr_and(_af.high, _de.low); }, 4);
break;
case 0xA4:
exec_instruction([&] () { instr_and(_af.high, _hl.high); }, 4);
break;
case 0xA5:
exec_instruction([&] () { instr_and(_af.high, _hl.low); }, 4);
break;
case 0xA6:
exec_instruction([&] () { instr_and(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0xE6:
exec_instruction([&] () { instr_and(_af.high, *it++); }, 8);
break;
case 0xB7:
exec_instruction([&] () { instr_or(_af.high, _af.high); }, 4);
break;
case 0xB0:
exec_instruction([&] () { instr_or(_af.high, _bc.high); }, 4);
break;
case 0xB1:
exec_instruction([&] () { instr_or(_af.high, _bc.low); }, 4);
break;
case 0xB2:
exec_instruction([&] () { instr_or(_af.high, _de.high); }, 4);
break;
case 0xB3:
exec_instruction([&] () { instr_or(_af.high, _de.low); }, 4);
break;
case 0xB4:
exec_instruction([&] () { instr_or(_af.high, _hl.high); }, 4);
break;
case 0xB5:
exec_instruction([&] () { instr_or(_af.high, _hl.low); }, 4);
break;
case 0xB6:
exec_instruction([&] () { instr_or(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0xF6:
exec_instruction([&] () { instr_or(_af.high, *it++); }, 8);
break;
case 0xAF:
exec_instruction([&] () { instr_xor(_af.high, _af.high); }, 4);
break;
case 0xA8:
exec_instruction([&] () { instr_xor(_af.high, _bc.high); }, 4);
break;
case 0xA9:
exec_instruction([&] () { instr_xor(_af.high, _bc.low); }, 4);
break;
case 0xAA:
exec_instruction([&] () { instr_xor(_af.high, _de.high); }, 4);
break;
case 0xAB:
exec_instruction([&] () { instr_xor(_af.high, _de.low); }, 4);
break;
case 0xAC:
exec_instruction([&] () { instr_xor(_af.high, _hl.high); }, 4);
break;
case 0xAD:
exec_instruction([&] () { instr_xor(_af.high, _hl.low); }, 4);
break;
case 0xAE:
exec_instruction([&] () { instr_xor(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0xEE:
exec_instruction([&] () { instr_xor(_af.high, *it++); }, 8);
break;
case 0xBF:
exec_instruction([&] () { instr_cp(_af.high, _af.high); }, 4);
break;
case 0xB8:
exec_instruction([&] () { instr_cp(_af.high, _bc.high); }, 4);
break;
case 0xB9:
exec_instruction([&] () { instr_cp(_af.high, _bc.low); }, 4);
break;
case 0xBA:
exec_instruction([&] () { instr_cp(_af.high, _de.high); }, 4);
break;
case 0xBB:
exec_instruction([&] () { instr_cp(_af.high, _de.low); }, 4);
break;
case 0xBC:
exec_instruction([&] () { instr_cp(_af.high, _hl.high); }, 4);
break;
case 0xBD:
exec_instruction([&] () { instr_cp(_af.high, _hl.low); }, 4);
break;
case 0xBE:
exec_instruction([&] () { instr_cp(_af.high, _components.mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0xFE:
exec_instruction([&] () { instr_cp(_af.high, *it++); }, 8);
break;
case 0x3C:
exec_instruction([&] () { instr_inc(_af.high); }, 4);
break;
case 0x04:
exec_instruction([&] () { instr_inc(_bc.high); }, 4);
break;
case 0x0C:
exec_instruction([&] () { instr_inc(_bc.low); }, 4);
break;
case 0x14:
exec_instruction([&] () { instr_inc(_de.high); }, 4);
break;
case 0x1C:
exec_instruction([&] () { instr_inc(_de.low); }, 4);
break;
case 0x24:
exec_instruction([&] () { instr_inc(_hl.high); }, 4);
break;
case 0x2C:
exec_instruction([&] () { instr_inc(_hl.low); }, 4);
break;
case 0x34:
exec_instruction([&] (Byte &v) { instr_inc(v); }, _hl.word, 12);
break;
case 0x3D:
exec_instruction([&] () { instr_dec(_af.high); }, 4);
break;
case 0x05:
exec_instruction([&] () { instr_dec(_bc.high); }, 4);
break;
case 0x0D:
exec_instruction([&] () { instr_dec(_bc.low); }, 4);
break;
case 0x15:
exec_instruction([&] () { instr_dec(_de.high); }, 4);
break;
case 0x1D:
exec_instruction([&] () { instr_dec(_de.low); }, 4);
break;
case 0x25:
exec_instruction([&] () { instr_dec(_hl.high); }, 4);
break;
case 0x2D:
exec_instruction([&] () { instr_dec(_hl.low); }, 4);
break;
case 0x35:
exec_instruction([&] (Byte &v) { instr_dec(v); }, _hl.word, 12);
break;
case 0x09:
exec_instruction([&] () { instr_add(_hl.word, _bc.word); }, 8);
break;
case 0x19:
exec_instruction([&] () { instr_add(_hl.word, _de.word); }, 8);
break;
case 0x29:
exec_instruction([&] () { instr_add(_hl.word, _hl.word); }, 8);
break;
case 0x39:
exec_instruction([&] () { instr_add(_hl.word, _sp.word); }, 8);
break;
case 0xE8:
exec_instruction([&] () { instr_add(_sp.word, *it++); }, 16);
break;
case 0x03:
exec_instruction([&] () { instr_inc(_bc.word); }, 8);
break;
case 0x13:
exec_instruction([&] () { instr_inc(_de.word); }, 8);
break;
case 0x23:
exec_instruction([&] () { instr_inc(_hl.word); }, 8);
break;
case 0x33:
exec_instruction([&] () { instr_inc(_sp.word); }, 8);
break;
case 0x0B:
exec_instruction([&] () { instr_dec(_bc.word); }, 8);
break;
case 0x1B:
exec_instruction([&] () { instr_dec(_de.word); }, 8);
break;
case 0x2B:
exec_instruction([&] () { instr_dec(_hl.word); }, 8);
break;
case 0x3B:
exec_instruction([&] () { instr_dec(_sp.word); }, 8);
break;
case 0x27:
exec_instruction([&] () { instr_daa(); }, 4);
break;
case 0x2F:
exec_instruction([&] () { instr_cpl(); }, 4);
break;
case 0x3F:
exec_instruction([&] () { instr_ccf(); }, 4);
break;
case 0x37:
exec_instruction([&] () { instr_scf(); }, 4);
break;
case 0x00:
exec_instruction([&] () { instr_nop(); }, 4);
break;
case 0x76:
exec_instruction([&] () { instr_halt(); }, 4);
break;
case 0x10:
exec_instruction([&] () { instr_stop(); }, 4);
break;
case 0xF3:
exec_instruction([&] () { instr_di(); }, 4);
break;
case 0xFB:
exec_instruction([&] () { instr_ei(); }, 4);
break;
case 0x07:
exec_instruction([&] () { instr_rlc(_af.high); }, 4);
break;
case 0x17:
exec_instruction([&] () { instr_rl(_af.high); }, 4);
break;
case 0x0F:
exec_instruction([&] () { instr_rrc(_af.high); }, 4);
break;
case 0x1F:
exec_instruction([&] () { instr_rr(_af.high); }, 4);
break;
case 0xC3:
exec_instruction([&] () { instr_jp(JumpCondition::None, fetch_word()); }, 12);
break;
case 0xC2:
exec_instruction([&] () { instr_jp(JumpCondition::NonZero, fetch_word()); }, 12);
break;
case 0xCA:
exec_instruction([&] () { instr_jp(JumpCondition::Zero, fetch_word()); }, 12);
break;
case 0xD2:
exec_instruction([&] () { instr_jp(JumpCondition::NonCarry, fetch_word()); }, 12);
break;
case 0xDA:
exec_instruction([&] () { instr_jp(JumpCondition::Carry, fetch_word()); }, 12);
break;
case 0xE9:
exec_instruction([&] () { instr_jp(JumpCondition::None, _components.mem_bus->read<Byte>(_hl.word)); }, 4);
break;
case 0x18:
exec_instruction([&] () { instr_jr(JumpCondition::None, *it++); }, 8);
break;
case 0x20:
exec_instruction([&] () { instr_jr(JumpCondition::NonZero, *it++); }, 8);
break;
case 0x28:
exec_instruction([&] () { instr_jr(JumpCondition::Zero, *it++); }, 8);
break;
case 0x30:
exec_instruction([&] () { instr_jr(JumpCondition::NonCarry, *it++); }, 8);
break;
case 0x38:
exec_instruction([&] () { instr_jr(JumpCondition::Carry, *it++); }, 8);
break;
case 0xCD:
exec_instruction([&] () { instr_call(JumpCondition::None, fetch_word()); }, 12);
break;
case 0xC4:
exec_instruction([&] () { instr_call(JumpCondition::NonZero, fetch_word()); }, 12);
break;
case 0xCC:
exec_instruction([&] () { instr_call(JumpCondition::Zero, fetch_word()); }, 12);
break;
case 0xD4:
exec_instruction([&] () { instr_call(JumpCondition::NonCarry, fetch_word()); }, 12);
break;
case 0xDC:
exec_instruction([&] () { instr_call(JumpCondition::Carry, fetch_word()); }, 12);
break;
case 0xC7:
exec_instruction([&] () { instr_rst(0x00); }, 32);
break;
case 0xCF:
exec_instruction([&] () { instr_rst(0x08); }, 32);
break;
case 0xD7:
exec_instruction([&] () { instr_rst(0x10); }, 32);
break;
case 0xDF:
exec_instruction([&] () { instr_rst(0x18); }, 32);
break;
case 0xE7:
exec_instruction([&] () { instr_rst(0x20); }, 32);
break;
case 0xEF:
exec_instruction([&] () { instr_rst(0x28); }, 32);
break;
case 0xF7:
exec_instruction([&] () { instr_rst(0x30); }, 32);
break;
case 0xFF:
exec_instruction([&] () { instr_rst(0x38); }, 32);
break;
case 0xC9:
exec_instruction([&] () { instr_ret(JumpCondition::None); }, 8);
break;
case 0xC0:
exec_instruction([&] () { instr_ret(JumpCondition::NonZero); }, 8);
break;
case 0xC8:
exec_instruction([&] () { instr_ret(JumpCondition::Zero); }, 8);
break;
case 0xD0:
exec_instruction([&] () { instr_ret(JumpCondition::NonCarry); }, 8);
break;
case 0xD8:
exec_instruction([&] () { instr_ret(JumpCondition::Carry); }, 8);
break;
case 0xD9:
exec_instruction([&] () { instr_reti(); }, 8);
break;
case 0xCB:
switch(*it++) {
case 0x07:
exec_instruction([&] () { instr_rlc(_af.high); }, 8);
break;
case 0x00:
exec_instruction([&] () { instr_rlc(_bc.high); }, 8);
break;
case 0x01:
exec_instruction([&] () { instr_rlc(_bc.low); }, 8);
break;
case 0x02:
exec_instruction([&] () { instr_rlc(_de.high); }, 8);
break;
case 0x03:
exec_instruction([&] () { instr_rlc(_de.low); }, 8);
break;
case 0x04:
exec_instruction([&] () { instr_rlc(_hl.high); }, 8);
break;
case 0x05:
exec_instruction([&] () { instr_rlc(_hl.low); }, 8);
break;
case 0x06:
exec_instruction([&] (Byte &v) { instr_rlc(v); }, _hl.word, 16);
break;
case 0x17:
exec_instruction([&] () { instr_rl(_af.high); }, 8);
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
case 0x0F:
exec_instruction([&] () { instr_rrc(_af.high); }, 8);
break;
case 0x08:
exec_instruction([&] () { instr_rrc(_bc.high); }, 8);
break;
case 0x09:
exec_instruction([&] () { instr_rrc(_bc.low); }, 8);
break;
case 0x0A:
exec_instruction([&] () { instr_rrc(_de.high); }, 8);
break;
case 0x0B:
exec_instruction([&] () { instr_rrc(_de.low); }, 8);
break;
case 0x0C:
exec_instruction([&] () { instr_rrc(_hl.high); }, 8);
break;
case 0x0D:
exec_instruction([&] () { instr_rrc(_hl.low); }, 8);
break;
case 0x0E:
exec_instruction([&] (Byte &v) { instr_rrc(v); }, _hl.word, 16);
break;
case 0x1F:
exec_instruction([&] () { instr_rr(_af.high); }, 8);
break;
case 0x18:
exec_instruction([&] () { instr_rr(_bc.high); }, 8);
break;
case 0x19:
exec_instruction([&] () { instr_rr(_bc.low); }, 8);
break;
case 0x1A:
exec_instruction([&] () { instr_rr(_de.high); }, 8);
break;
case 0x1B:
exec_instruction([&] () { instr_rr(_de.low); }, 8);
break;
case 0x1C:
exec_instruction([&] () { instr_rr(_hl.high); }, 8);
break;
case 0x1D:
exec_instruction([&] () { instr_rr(_hl.low); }, 8);
break;
case 0x1E:
exec_instruction([&] (Byte &v) { instr_rr(v); }, _hl.word, 16);
break;
case 0x27:
exec_instruction([&] () { instr_sla(_af.high); }, 8);
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
case 0x2F:
exec_instruction([&] () { instr_sra(_af.high); }, 8);
break;
case 0x28:
exec_instruction([&] () { instr_sra(_bc.high); }, 8);
break;
case 0x29:
exec_instruction([&] () { instr_sra(_bc.low); }, 8);
break;
case 0x2A:
exec_instruction([&] () { instr_sra(_de.high); }, 8);
break;
case 0x2B:
exec_instruction([&] () { instr_sra(_de.low); }, 8);
break;
case 0x2C:
exec_instruction([&] () { instr_sra(_hl.high); }, 8);
break;
case 0x2D:
exec_instruction([&] () { instr_sra(_hl.low); }, 8);
break;
case 0x2E:
exec_instruction([&] (Byte &v) { instr_sra(v); }, _hl.word, 16);
break;
case 0x37:
exec_instruction([&] () { instr_swap(_af.high); }, 8);
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
case 0x3F:
exec_instruction([&] () { instr_srl(_af.high); }, 8);
break;
case 0x38:
exec_instruction([&] () { instr_srl(_bc.high); }, 8);
break;
case 0x39:
exec_instruction([&] () { instr_srl(_bc.low); }, 8);
break;
case 0x3A:
exec_instruction([&] () { instr_srl(_de.high); }, 8);
break;
case 0x3B:
exec_instruction([&] () { instr_srl(_de.low); }, 8);
break;
case 0x3C:
exec_instruction([&] () { instr_srl(_hl.high); }, 8);
break;
case 0x3D:
exec_instruction([&] () { instr_srl(_hl.low); }, 8);
break;
case 0x3E:
exec_instruction([&] (Byte &v) { instr_srl(v); }, _hl.word, 16);
break;
case 0x47:
exec_instruction([&] () { instr_bit(*it++, _af.high); }, 8);
break;
case 0x40:
exec_instruction([&] () { instr_bit(*it++, _bc.high); }, 8);
break;
case 0x41:
exec_instruction([&] () { instr_bit(*it++, _bc.low); }, 8);
break;
case 0x42:
exec_instruction([&] () { instr_bit(*it++, _de.high); }, 8);
break;
case 0x43:
exec_instruction([&] () { instr_bit(*it++, _de.low); }, 8);
break;
case 0x44:
exec_instruction([&] () { instr_bit(*it++, _hl.high); }, 8);
break;
case 0x45:
exec_instruction([&] () { instr_bit(*it++, _hl.low); }, 8);
break;
case 0x46:
exec_instruction([&] () { instr_bit(*it++, _components.mem_bus->read<Byte>(_hl.word)); }, 16);
break;
case 0xC7:
exec_instruction([&] () { instr_set(_af.high, *it++); }, 8);
break;
case 0xC0:
exec_instruction([&] () { instr_set(_bc.high, *it++); }, 8);
break;
case 0xC1:
exec_instruction([&] () { instr_set(_bc.low, *it++); }, 8);
break;
case 0xC2:
exec_instruction([&] () { instr_set(_de.high, *it++); }, 8);
break;
case 0xC3:
exec_instruction([&] () { instr_set(_de.low, *it++); }, 8);
break;
case 0xC4:
exec_instruction([&] () { instr_set(_hl.high, *it++); }, 8);
break;
case 0xC5:
exec_instruction([&] () { instr_set(_hl.low, *it++); }, 8);
break;
case 0xC6:
exec_instruction([&] (Byte &v) { instr_set(v, *it++); }, _hl.word, 16);
break;
case 0x87:
exec_instruction([&] () { instr_res(_af.high, *it++); }, 8);
break;
case 0x80:
exec_instruction([&] () { instr_res(_bc.high, *it++); }, 8);
break;
case 0x81:
exec_instruction([&] () { instr_res(_bc.low, *it++); }, 8);
break;
case 0x82:
exec_instruction([&] () { instr_res(_de.high, *it++); }, 8);
break;
case 0x83:
exec_instruction([&] () { instr_res(_de.low, *it++); }, 8);
break;
case 0x84:
exec_instruction([&] () { instr_res(_hl.high, *it++); }, 8);
break;
case 0x85:
exec_instruction([&] () { instr_res(_hl.low, *it++); }, 8);
break;
case 0x86:
exec_instruction([&] (Byte &v) { instr_res(v, *it++); }, _hl.word, 16);
break;
}
break;
