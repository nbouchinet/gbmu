case 0x06:
std::cerr << std::hex << "ld(" << "_bc.high=" << " " << +_bc.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.high, *it++); }, 8);
break;
case 0x0E:
std::cerr << std::hex << "ld(" << "_bc.low=" << " " << +_bc.low << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.low, *it++); }, 8);
break;
case 0x16:
std::cerr << std::hex << "ld(" << "_de.high=" << " " << +_de.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.high, *it++); }, 8);
break;
case 0x1E:
std::cerr << std::hex << "ld(" << "_de.low=" << " " << +_de.low << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.low, *it++); }, 8);
break;
case 0x26:
std::cerr << std::hex << "ld(" << "_hl.high=" << " " << +_hl.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.high, *it++); }, 8);
break;
case 0x2E:
std::cerr << std::hex << "ld(" << "_hl.low=" << " " << +_hl.low << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.low, *it++); }, 8);
break;
case 0x7F:
std::cerr << std::hex << "ld(" << "_af.high=" << " " << +_af.high << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_af.high, _af.high); }, 4);
break;
case 0x78:
std::cerr << std::hex << "ld(" << "_af.high=" << " " << +_af.high << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_af.high, _bc.high); }, 4);
break;
case 0x79:
std::cerr << std::hex << "ld(" << "_af.high=" << " " << +_af.high << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_af.high, _bc.low); }, 4);
break;
case 0x7A:
std::cerr << std::hex << "ld(" << "_af.high=" << " " << +_af.high << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_af.high, _de.high); }, 4);
break;
case 0x7B:
std::cerr << std::hex << "ld(" << "_af.high=" << " " << +_af.high << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_af.high, _de.low); }, 4);
break;
case 0x7C:
std::cerr << std::hex << "ld(" << "_af.high=" << " " << +_af.high << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_af.high, _hl.high); }, 4);
break;
case 0x7D:
std::cerr << std::hex << "ld(" << "_af.high=" << " " << +_af.high << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_af.high, _hl.low); }, 4);
break;
case 0x7E:
std::cerr << std::hex << "ld(" << "_af.high=" << " " << +_af.high << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_af.high, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0x40:
std::cerr << std::hex << "ld(" << "_bc.high=" << " " << +_bc.high << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.high, _bc.high); }, 4);
break;
case 0x41:
std::cerr << std::hex << "ld(" << "_bc.high=" << " " << +_bc.high << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.high, _bc.low); }, 4);
break;
case 0x42:
std::cerr << std::hex << "ld(" << "_bc.high=" << " " << +_bc.high << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.high, _de.high); }, 4);
break;
case 0x43:
std::cerr << std::hex << "ld(" << "_bc.high=" << " " << +_bc.high << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.high, _de.low); }, 4);
break;
case 0x44:
std::cerr << std::hex << "ld(" << "_bc.high=" << " " << +_bc.high << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.high, _hl.high); }, 4);
break;
case 0x45:
std::cerr << std::hex << "ld(" << "_bc.high=" << " " << +_bc.high << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.high, _hl.low); }, 4);
break;
case 0x46:
std::cerr << std::hex << "ld(" << "_bc.high=" << " " << +_bc.high << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.high, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0x48:
std::cerr << std::hex << "ld(" << "_bc.low=" << " " << +_bc.low << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.low, _bc.high); }, 4);
break;
case 0x49:
std::cerr << std::hex << "ld(" << "_bc.low=" << " " << +_bc.low << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.low, _bc.low); }, 4);
break;
case 0x4A:
std::cerr << std::hex << "ld(" << "_bc.low=" << " " << +_bc.low << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.low, _de.high); }, 4);
break;
case 0x4B:
std::cerr << std::hex << "ld(" << "_bc.low=" << " " << +_bc.low << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.low, _de.low); }, 4);
break;
case 0x4C:
std::cerr << std::hex << "ld(" << "_bc.low=" << " " << +_bc.low << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.low, _hl.high); }, 4);
break;
case 0x4D:
std::cerr << std::hex << "ld(" << "_bc.low=" << " " << +_bc.low << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.low, _hl.low); }, 4);
break;
case 0x4E:
std::cerr << std::hex << "ld(" << "_bc.low=" << " " << +_bc.low << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.low, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0x50:
std::cerr << std::hex << "ld(" << "_de.high=" << " " << +_de.high << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.high, _bc.high); }, 4);
break;
case 0x51:
std::cerr << std::hex << "ld(" << "_de.high=" << " " << +_de.high << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.high, _bc.low); }, 4);
break;
case 0x52:
std::cerr << std::hex << "ld(" << "_de.high=" << " " << +_de.high << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.high, _de.high); }, 4);
break;
case 0x53:
std::cerr << std::hex << "ld(" << "_de.high=" << " " << +_de.high << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.high, _de.low); }, 4);
break;
case 0x54:
std::cerr << std::hex << "ld(" << "_de.high=" << " " << +_de.high << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.high, _hl.high); }, 4);
break;
case 0x55:
std::cerr << std::hex << "ld(" << "_de.high=" << " " << +_de.high << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.high, _hl.low); }, 4);
break;
case 0x56:
std::cerr << std::hex << "ld(" << "_de.high=" << " " << +_de.high << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.high, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0x58:
std::cerr << std::hex << "ld(" << "_de.low=" << " " << +_de.low << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.low, _bc.high); }, 4);
break;
case 0x59:
std::cerr << std::hex << "ld(" << "_de.low=" << " " << +_de.low << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.low, _bc.low); }, 4);
break;
case 0x5A:
std::cerr << std::hex << "ld(" << "_de.low=" << " " << +_de.low << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.low, _de.high); }, 4);
break;
case 0x5B:
std::cerr << std::hex << "ld(" << "_de.low=" << " " << +_de.low << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.low, _de.low); }, 4);
break;
case 0x5C:
std::cerr << std::hex << "ld(" << "_de.low=" << " " << +_de.low << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.low, _hl.high); }, 4);
break;
case 0x5D:
std::cerr << std::hex << "ld(" << "_de.low=" << " " << +_de.low << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.low, _hl.low); }, 4);
break;
case 0x5E:
std::cerr << std::hex << "ld(" << "_de.low=" << " " << +_de.low << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.low, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0x60:
std::cerr << std::hex << "ld(" << "_hl.high=" << " " << +_hl.high << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.high, _bc.high); }, 4);
break;
case 0x61:
std::cerr << std::hex << "ld(" << "_hl.high=" << " " << +_hl.high << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.high, _bc.low); }, 4);
break;
case 0x62:
std::cerr << std::hex << "ld(" << "_hl.high=" << " " << +_hl.high << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.high, _de.high); }, 4);
break;
case 0x63:
std::cerr << std::hex << "ld(" << "_hl.high=" << " " << +_hl.high << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.high, _de.low); }, 4);
break;
case 0x64:
std::cerr << std::hex << "ld(" << "_hl.high=" << " " << +_hl.high << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.high, _hl.high); }, 4);
break;
case 0x65:
std::cerr << std::hex << "ld(" << "_hl.high=" << " " << +_hl.high << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.high, _hl.low); }, 4);
break;
case 0x66:
std::cerr << std::hex << "ld(" << "_hl.high=" << " " << +_hl.high << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.high, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0x68:
std::cerr << std::hex << "ld(" << "_hl.low=" << " " << +_hl.low << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.low, _bc.high); }, 4);
break;
case 0x69:
std::cerr << std::hex << "ld(" << "_hl.low=" << " " << +_hl.low << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.low, _bc.low); }, 4);
break;
case 0x6A:
std::cerr << std::hex << "ld(" << "_hl.low=" << " " << +_hl.low << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.low, _de.high); }, 4);
break;
case 0x6B:
std::cerr << std::hex << "ld(" << "_hl.low=" << " " << +_hl.low << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.low, _de.low); }, 4);
break;
case 0x6C:
std::cerr << std::hex << "ld(" << "_hl.low=" << " " << +_hl.low << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.low, _hl.high); }, 4);
break;
case 0x6D:
std::cerr << std::hex << "ld(" << "_hl.low=" << " " << +_hl.low << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.low, _hl.low); }, 4);
break;
case 0x6E:
std::cerr << std::hex << "ld(" << "_hl.low=" << " " << +_hl.low << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.low, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0x70:
std::cerr << std::hex << "ld(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_ld(v, _bc.high); }, _hl.word, 8);
break;
case 0x71:
std::cerr << std::hex << "ld(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_ld(v, _bc.low); }, _hl.word, 8);
break;
case 0x72:
std::cerr << std::hex << "ld(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_ld(v, _de.high); }, _hl.word, 8);
break;
case 0x73:
std::cerr << std::hex << "ld(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_ld(v, _de.low); }, _hl.word, 8);
break;
case 0x74:
std::cerr << std::hex << "ld(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_ld(v, _hl.high); }, _hl.word, 8);
break;
case 0x75:
std::cerr << std::hex << "ld(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_ld(v, _hl.low); }, _hl.word, 8);
break;
case 0x36:
std::cerr << std::hex << "ld(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_ld(v, *it++); }, _hl.word, 12);
break;
case 0x0A:
std::cerr << std::hex << "ld(" << "_af.high=" << " " << +_af.high << " " << "&_bc.word=" << " " << +mem_bus->read<Byte>(_bc.word) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_af.high, mem_bus->read<Byte>(_bc.word)); }, 8);
break;
case 0x1A:
std::cerr << std::hex << "ld(" << "_af.high=" << " " << +_af.high << " " << "&_de.word=" << " " << +mem_bus->read<Byte>(_de.word) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_af.high, mem_bus->read<Byte>(_de.word)); }, 8);
break;
case 0xFA:
std::cerr << std::hex << "ld(" << "_af.high=" << " " << +_af.high << " " << "&fetch_word()=" << " " << +mem_bus->read<Byte>(static_cast<Word>(*it << 8 | *(it + 1))) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_af.high, mem_bus->read<Byte>(fetch_word())); }, 16);
break;
case 0x3E:
std::cerr << std::hex << "ld(" << "_af.high=" << " " << +_af.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_ld(_af.high, *it++); }, 8);
break;
case 0x47:
std::cerr << std::hex << "ld(" << "_bc.high=" << " " << +_bc.high << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.high, _af.high); }, 4);
break;
case 0x4F:
std::cerr << std::hex << "ld(" << "_bc.low=" << " " << +_bc.low << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.low, _af.high); }, 4);
break;
case 0x57:
std::cerr << std::hex << "ld(" << "_de.high=" << " " << +_de.high << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.high, _af.high); }, 4);
break;
case 0x5F:
std::cerr << std::hex << "ld(" << "_de.low=" << " " << +_de.low << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.low, _af.high); }, 4);
break;
case 0x67:
std::cerr << std::hex << "ld(" << "_hl.high=" << " " << +_hl.high << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.high, _af.high); }, 4);
break;
case 0x6F:
std::cerr << std::hex << "ld(" << "_hl.low=" << " " << +_hl.low << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.low, _af.high); }, 4);
break;
case 0x02:
std::cerr << std::hex << "ld(" << "&_bc.word=" << " " << +mem_bus->read<Byte>(_bc.word) << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, _bc.word, 8);
break;
case 0x12:
std::cerr << std::hex << "ld(" << "&_de.word=" << " " << +mem_bus->read<Byte>(_de.word) << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, _de.word, 8);
break;
case 0x77:
std::cerr << std::hex << "ld(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, _hl.word, 8);
break;
case 0xEA:
std::cerr << std::hex << "ld(" << "&fetch_word()=" << " " << +mem_bus->read<Byte>(static_cast<Word>(*it << 8 | *(it + 1))) << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, fetch_word(), 16);
break;
case 0xF2:
std::cerr << std::hex << "ld(" << "_af.high=" << " " << +_af.high << " " << "&_bc.low=" << " " << +mem_bus->read<Byte>(_bc.low) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_af.high, mem_bus->read<Byte>(_bc.low)); }, 8);
break;
case 0xE2:
std::cerr << std::hex << "ld(" << "&0xFF00 + _bc.low=" << " " << +mem_bus->read<Byte>(0xFF00 + _bc.low) << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_ld(v, _af.high); }, 0xFF00 + _bc.low, 8);
break;
case 0x3A:
std::cerr << std::hex << "ldd(" << "_af.high=" << " " << +_af.high << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_ldd(_af.high, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0x32:
std::cerr << std::hex << "ldd(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_ldd(v, _af.high); }, _hl.word, 8);
break;
case 0x2A:
std::cerr << std::hex << "ldi(" << "_af.high=" << " " << +_af.high << " " << "_hl.word=" << " " << +_hl.word << ")" << std::endl;
exec_instruction([&] () { instr_ldi(_af.high, _hl.word); }, 8);
break;
case 0xF0:
std::cerr << std::hex << "ld(" << "_af.high=" << " " << +_af.high << " " << "&0xFF00 + *it++=" << " " << +mem_bus->read<Byte>(0xFF00 + *it++) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_af.high, mem_bus->read<Byte>(0xFF00 + *it++)); }, 12);
break;
case 0x01:
std::cerr << std::hex << "ld(" << "_bc.word=" << " " << +_bc.word << " " << "fetch_word()=" << " " << +static_cast<Word>(*it << 8 | *(it + 1)) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_bc.word, fetch_word()); }, 12);
break;
case 0x11:
std::cerr << std::hex << "ld(" << "_de.word=" << " " << +_de.word << " " << "fetch_word()=" << " " << +static_cast<Word>(*it << 8 | *(it + 1)) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_de.word, fetch_word()); }, 12);
break;
case 0x21:
std::cerr << std::hex << "ld(" << "_hl.word=" << " " << +_hl.word << " " << "fetch_word()=" << " " << +static_cast<Word>(*it << 8 | *(it + 1)) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_hl.word, fetch_word()); }, 12);
break;
case 0x31:
std::cerr << std::hex << "ld(" << "_sp.word=" << " " << +_sp.word << " " << "fetch_word()=" << " " << +static_cast<Word>(*it << 8 | *(it + 1)) << ")" << std::endl;
exec_instruction([&] () { instr_ld(_sp.word, fetch_word()); }, 12);
break;
case 0xF9:
std::cerr << std::hex << "ld(" << "_sp.word=" << " " << +_sp.word << " " << "_hl.word=" << " " << +_hl.word << ")" << std::endl;
exec_instruction([&] () { instr_ld(_sp.word, _hl.word); }, 8);
break;
case 0xF8:
std::cerr << std::hex << "ldhl(" << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_ldhl(*it++); }, 12);
break;
case 0x08:
std::cerr << std::hex << "ld(" << "&fetch_word()=" << " " << +mem_bus->read<Byte>(static_cast<Word>(*it << 8 | *(it + 1))) << " " << "_sp.word=" << " " << +_sp.word << ")" << std::endl;
exec_instruction([&] (Word &v) { instr_ld(v, _sp.word); }, fetch_word(), 20);
break;
case 0xF5:
std::cerr << std::hex << "push(" << "_af.word=" << " " << +_af.word << ")" << std::endl;
exec_instruction([&] () { instr_push(_af.word); }, 16);
break;
case 0xC5:
std::cerr << std::hex << "push(" << "_bc.word=" << " " << +_bc.word << ")" << std::endl;
exec_instruction([&] () { instr_push(_bc.word); }, 16);
break;
case 0xD5:
std::cerr << std::hex << "push(" << "_de.word=" << " " << +_de.word << ")" << std::endl;
exec_instruction([&] () { instr_push(_de.word); }, 16);
break;
case 0xE5:
std::cerr << std::hex << "push(" << "_hl.word=" << " " << +_hl.word << ")" << std::endl;
exec_instruction([&] () { instr_push(_hl.word); }, 16);
break;
case 0xF1:
std::cerr << std::hex << "pop(" << "_af.word=" << " " << +_af.word << ")" << std::endl;
exec_instruction([&] () { instr_pop(_af.word); }, 12);
break;
case 0xC1:
std::cerr << std::hex << "pop(" << "_bc.word=" << " " << +_bc.word << ")" << std::endl;
exec_instruction([&] () { instr_pop(_bc.word); }, 12);
break;
case 0xD1:
std::cerr << std::hex << "pop(" << "_de.word=" << " " << +_de.word << ")" << std::endl;
exec_instruction([&] () { instr_pop(_de.word); }, 12);
break;
case 0xE1:
std::cerr << std::hex << "pop(" << "_hl.word=" << " " << +_hl.word << ")" << std::endl;
exec_instruction([&] () { instr_pop(_hl.word); }, 12);
break;
case 0x87:
std::cerr << std::hex << "add(" << "_af.high=" << " " << +_af.high << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_add(_af.high, _af.high); }, 4);
break;
case 0x80:
std::cerr << std::hex << "add(" << "_af.high=" << " " << +_af.high << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_add(_af.high, _bc.high); }, 4);
break;
case 0x81:
std::cerr << std::hex << "add(" << "_af.high=" << " " << +_af.high << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_add(_af.high, _bc.low); }, 4);
break;
case 0x82:
std::cerr << std::hex << "add(" << "_af.high=" << " " << +_af.high << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_add(_af.high, _de.high); }, 4);
break;
case 0x83:
std::cerr << std::hex << "add(" << "_af.high=" << " " << +_af.high << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_add(_af.high, _de.low); }, 4);
break;
case 0x84:
std::cerr << std::hex << "add(" << "_af.high=" << " " << +_af.high << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_add(_af.high, _hl.high); }, 4);
break;
case 0x85:
std::cerr << std::hex << "add(" << "_af.high=" << " " << +_af.high << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_add(_af.high, _hl.low); }, 4);
break;
case 0x86:
std::cerr << std::hex << "add(" << "_af.high=" << " " << +_af.high << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_add(_af.high, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0xC6:
std::cerr << std::hex << "add(" << "_af.high=" << " " << +_af.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_add(_af.high, *it++); }, 8);
break;
case 0x8F:
std::cerr << std::hex << "adc(" << "_af.high=" << " " << +_af.high << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_adc(_af.high, _af.high); }, 4);
break;
case 0x88:
std::cerr << std::hex << "adc(" << "_af.high=" << " " << +_af.high << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_adc(_af.high, _bc.high); }, 4);
break;
case 0x89:
std::cerr << std::hex << "adc(" << "_af.high=" << " " << +_af.high << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_adc(_af.high, _bc.low); }, 4);
break;
case 0x8A:
std::cerr << std::hex << "adc(" << "_af.high=" << " " << +_af.high << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_adc(_af.high, _de.high); }, 4);
break;
case 0x8B:
std::cerr << std::hex << "adc(" << "_af.high=" << " " << +_af.high << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_adc(_af.high, _de.low); }, 4);
break;
case 0x8C:
std::cerr << std::hex << "adc(" << "_af.high=" << " " << +_af.high << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_adc(_af.high, _hl.high); }, 4);
break;
case 0x8D:
std::cerr << std::hex << "adc(" << "_af.high=" << " " << +_af.high << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_adc(_af.high, _hl.low); }, 4);
break;
case 0x8E:
std::cerr << std::hex << "adc(" << "_af.high=" << " " << +_af.high << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_adc(_af.high, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0xCE:
std::cerr << std::hex << "adc(" << "_af.high=" << " " << +_af.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_adc(_af.high, *it++); }, 8);
break;
case 0x97:
std::cerr << std::hex << "sub(" << "_af.high=" << " " << +_af.high << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_sub(_af.high, _af.high); }, 4);
break;
case 0x90:
std::cerr << std::hex << "sub(" << "_af.high=" << " " << +_af.high << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_sub(_af.high, _bc.high); }, 4);
break;
case 0x91:
std::cerr << std::hex << "sub(" << "_af.high=" << " " << +_af.high << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_sub(_af.high, _bc.low); }, 4);
break;
case 0x92:
std::cerr << std::hex << "sub(" << "_af.high=" << " " << +_af.high << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_sub(_af.high, _de.high); }, 4);
break;
case 0x93:
std::cerr << std::hex << "sub(" << "_af.high=" << " " << +_af.high << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_sub(_af.high, _de.low); }, 4);
break;
case 0x94:
std::cerr << std::hex << "sub(" << "_af.high=" << " " << +_af.high << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_sub(_af.high, _hl.high); }, 4);
break;
case 0x95:
std::cerr << std::hex << "sub(" << "_af.high=" << " " << +_af.high << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_sub(_af.high, _hl.low); }, 4);
break;
case 0x96:
std::cerr << std::hex << "sub(" << "_af.high=" << " " << +_af.high << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_sub(_af.high, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0xD6:
std::cerr << std::hex << "sub(" << "_af.high=" << " " << +_af.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_sub(_af.high, *it++); }, 8);
break;
case 0x9F:
std::cerr << std::hex << "sbc(" << "_af.high=" << " " << +_af.high << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_sbc(_af.high, _af.high); }, 4);
break;
case 0x98:
std::cerr << std::hex << "sbc(" << "_af.high=" << " " << +_af.high << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_sbc(_af.high, _bc.high); }, 4);
break;
case 0x99:
std::cerr << std::hex << "sbc(" << "_af.high=" << " " << +_af.high << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_sbc(_af.high, _bc.low); }, 4);
break;
case 0x9A:
std::cerr << std::hex << "sbc(" << "_af.high=" << " " << +_af.high << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_sbc(_af.high, _de.high); }, 4);
break;
case 0x9B:
std::cerr << std::hex << "sbc(" << "_af.high=" << " " << +_af.high << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_sbc(_af.high, _de.low); }, 4);
break;
case 0x9C:
std::cerr << std::hex << "sbc(" << "_af.high=" << " " << +_af.high << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_sbc(_af.high, _hl.high); }, 4);
break;
case 0x9D:
std::cerr << std::hex << "sbc(" << "_af.high=" << " " << +_af.high << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_sbc(_af.high, _hl.low); }, 4);
break;
case 0x9E:
std::cerr << std::hex << "sbc(" << "_af.high=" << " " << +_af.high << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_sbc(_af.high, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0xA7:
std::cerr << std::hex << "and(" << "_af.high=" << " " << +_af.high << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_and(_af.high, _af.high); }, 4);
break;
case 0xA0:
std::cerr << std::hex << "and(" << "_af.high=" << " " << +_af.high << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_and(_af.high, _bc.high); }, 4);
break;
case 0xA1:
std::cerr << std::hex << "and(" << "_af.high=" << " " << +_af.high << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_and(_af.high, _bc.low); }, 4);
break;
case 0xA2:
std::cerr << std::hex << "and(" << "_af.high=" << " " << +_af.high << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_and(_af.high, _de.high); }, 4);
break;
case 0xA3:
std::cerr << std::hex << "and(" << "_af.high=" << " " << +_af.high << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_and(_af.high, _de.low); }, 4);
break;
case 0xA4:
std::cerr << std::hex << "and(" << "_af.high=" << " " << +_af.high << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_and(_af.high, _hl.high); }, 4);
break;
case 0xA5:
std::cerr << std::hex << "and(" << "_af.high=" << " " << +_af.high << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_and(_af.high, _hl.low); }, 4);
break;
case 0xA6:
std::cerr << std::hex << "and(" << "_af.high=" << " " << +_af.high << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_and(_af.high, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0xE6:
std::cerr << std::hex << "and(" << "_af.high=" << " " << +_af.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_and(_af.high, *it++); }, 8);
break;
case 0xB7:
std::cerr << std::hex << "or(" << "_af.high=" << " " << +_af.high << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_or(_af.high, _af.high); }, 4);
break;
case 0xB0:
std::cerr << std::hex << "or(" << "_af.high=" << " " << +_af.high << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_or(_af.high, _bc.high); }, 4);
break;
case 0xB1:
std::cerr << std::hex << "or(" << "_af.high=" << " " << +_af.high << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_or(_af.high, _bc.low); }, 4);
break;
case 0xB2:
std::cerr << std::hex << "or(" << "_af.high=" << " " << +_af.high << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_or(_af.high, _de.high); }, 4);
break;
case 0xB3:
std::cerr << std::hex << "or(" << "_af.high=" << " " << +_af.high << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_or(_af.high, _de.low); }, 4);
break;
case 0xB4:
std::cerr << std::hex << "or(" << "_af.high=" << " " << +_af.high << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_or(_af.high, _hl.high); }, 4);
break;
case 0xB5:
std::cerr << std::hex << "or(" << "_af.high=" << " " << +_af.high << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_or(_af.high, _hl.low); }, 4);
break;
case 0xB6:
std::cerr << std::hex << "or(" << "_af.high=" << " " << +_af.high << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_or(_af.high, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0xF6:
std::cerr << std::hex << "or(" << "_af.high=" << " " << +_af.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_or(_af.high, *it++); }, 8);
break;
case 0xAF:
std::cerr << std::hex << "xor(" << "_af.high=" << " " << +_af.high << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_xor(_af.high, _af.high); }, 4);
break;
case 0xA8:
std::cerr << std::hex << "xor(" << "_af.high=" << " " << +_af.high << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_xor(_af.high, _bc.high); }, 4);
break;
case 0xA9:
std::cerr << std::hex << "xor(" << "_af.high=" << " " << +_af.high << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_xor(_af.high, _bc.low); }, 4);
break;
case 0xAA:
std::cerr << std::hex << "xor(" << "_af.high=" << " " << +_af.high << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_xor(_af.high, _de.high); }, 4);
break;
case 0xAB:
std::cerr << std::hex << "xor(" << "_af.high=" << " " << +_af.high << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_xor(_af.high, _de.low); }, 4);
break;
case 0xAC:
std::cerr << std::hex << "xor(" << "_af.high=" << " " << +_af.high << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_xor(_af.high, _hl.high); }, 4);
break;
case 0xAD:
std::cerr << std::hex << "xor(" << "_af.high=" << " " << +_af.high << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_xor(_af.high, _hl.low); }, 4);
break;
case 0xAE:
std::cerr << std::hex << "xor(" << "_af.high=" << " " << +_af.high << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_xor(_af.high, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0xEE:
std::cerr << std::hex << "xor(" << "_af.high=" << " " << +_af.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_xor(_af.high, *it++); }, 8);
break;
case 0xBF:
std::cerr << std::hex << "cp(" << "_af.high=" << " " << +_af.high << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_cp(_af.high, _af.high); }, 4);
break;
case 0xB8:
std::cerr << std::hex << "cp(" << "_af.high=" << " " << +_af.high << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_cp(_af.high, _bc.high); }, 4);
break;
case 0xB9:
std::cerr << std::hex << "cp(" << "_af.high=" << " " << +_af.high << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_cp(_af.high, _bc.low); }, 4);
break;
case 0xBA:
std::cerr << std::hex << "cp(" << "_af.high=" << " " << +_af.high << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_cp(_af.high, _de.high); }, 4);
break;
case 0xBB:
std::cerr << std::hex << "cp(" << "_af.high=" << " " << +_af.high << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_cp(_af.high, _de.low); }, 4);
break;
case 0xBC:
std::cerr << std::hex << "cp(" << "_af.high=" << " " << +_af.high << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_cp(_af.high, _hl.high); }, 4);
break;
case 0xBD:
std::cerr << std::hex << "cp(" << "_af.high=" << " " << +_af.high << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_cp(_af.high, _hl.low); }, 4);
break;
case 0xBE:
std::cerr << std::hex << "cp(" << "_af.high=" << " " << +_af.high << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_cp(_af.high, mem_bus->read<Byte>(_hl.word)); }, 8);
break;
case 0xFE:
std::cerr << std::hex << "cp(" << "_af.high=" << " " << +_af.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_cp(_af.high, *it++); }, 8);
break;
case 0x3C:
std::cerr << std::hex << "inc(" << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_inc(_af.high); }, 4);
break;
case 0x04:
std::cerr << std::hex << "inc(" << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_inc(_bc.high); }, 4);
break;
case 0x0C:
std::cerr << std::hex << "inc(" << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_inc(_bc.low); }, 4);
break;
case 0x14:
std::cerr << std::hex << "inc(" << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_inc(_de.high); }, 4);
break;
case 0x1C:
std::cerr << std::hex << "inc(" << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_inc(_de.low); }, 4);
break;
case 0x24:
std::cerr << std::hex << "inc(" << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_inc(_hl.high); }, 4);
break;
case 0x2C:
std::cerr << std::hex << "inc(" << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_inc(_hl.low); }, 4);
break;
case 0x34:
std::cerr << std::hex << "inc(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_inc(v); }, _hl.word, 12);
break;
case 0x3D:
std::cerr << std::hex << "dec(" << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_dec(_af.high); }, 4);
break;
case 0x05:
std::cerr << std::hex << "dec(" << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_dec(_bc.high); }, 4);
break;
case 0x0D:
std::cerr << std::hex << "dec(" << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_dec(_bc.low); }, 4);
break;
case 0x15:
std::cerr << std::hex << "dec(" << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_dec(_de.high); }, 4);
break;
case 0x1D:
std::cerr << std::hex << "dec(" << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_dec(_de.low); }, 4);
break;
case 0x25:
std::cerr << std::hex << "dec(" << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_dec(_hl.high); }, 4);
break;
case 0x2D:
std::cerr << std::hex << "dec(" << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_dec(_hl.low); }, 4);
break;
case 0x35:
std::cerr << std::hex << "dec(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_dec(v); }, _hl.word, 12);
break;
case 0x09:
std::cerr << std::hex << "add(" << "_hl.word=" << " " << +_hl.word << " " << "_bc.word=" << " " << +_bc.word << ")" << std::endl;
exec_instruction([&] () { instr_add(_hl.word, _bc.word); }, 8);
break;
case 0x19:
std::cerr << std::hex << "add(" << "_hl.word=" << " " << +_hl.word << " " << "_de.word=" << " " << +_de.word << ")" << std::endl;
exec_instruction([&] () { instr_add(_hl.word, _de.word); }, 8);
break;
case 0x29:
std::cerr << std::hex << "add(" << "_hl.word=" << " " << +_hl.word << " " << "_hl.word=" << " " << +_hl.word << ")" << std::endl;
exec_instruction([&] () { instr_add(_hl.word, _hl.word); }, 8);
break;
case 0x39:
std::cerr << std::hex << "add(" << "_hl.word=" << " " << +_hl.word << " " << "_sp.word=" << " " << +_sp.word << ")" << std::endl;
exec_instruction([&] () { instr_add(_hl.word, _sp.word); }, 8);
break;
case 0xE8:
std::cerr << std::hex << "add(" << "_sp.word=" << " " << +_sp.word << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_add(_sp.word, *it++); }, 16);
break;
case 0x03:
std::cerr << std::hex << "inc(" << "_bc.word=" << " " << +_bc.word << ")" << std::endl;
exec_instruction([&] () { instr_inc(_bc.word); }, 8);
break;
case 0x13:
std::cerr << std::hex << "inc(" << "_de.word=" << " " << +_de.word << ")" << std::endl;
exec_instruction([&] () { instr_inc(_de.word); }, 8);
break;
case 0x23:
std::cerr << std::hex << "inc(" << "_hl.word=" << " " << +_hl.word << ")" << std::endl;
exec_instruction([&] () { instr_inc(_hl.word); }, 8);
break;
case 0x33:
std::cerr << std::hex << "inc(" << "_sp.word=" << " " << +_sp.word << ")" << std::endl;
exec_instruction([&] () { instr_inc(_sp.word); }, 8);
break;
case 0x0B:
std::cerr << std::hex << "dec(" << "_bc.word=" << " " << +_bc.word << ")" << std::endl;
exec_instruction([&] () { instr_dec(_bc.word); }, 8);
break;
case 0x1B:
std::cerr << std::hex << "dec(" << "_de.word=" << " " << +_de.word << ")" << std::endl;
exec_instruction([&] () { instr_dec(_de.word); }, 8);
break;
case 0x2B:
std::cerr << std::hex << "dec(" << "_hl.word=" << " " << +_hl.word << ")" << std::endl;
exec_instruction([&] () { instr_dec(_hl.word); }, 8);
break;
case 0x3B:
std::cerr << std::hex << "dec(" << "_sp.word=" << " " << +_sp.word << ")" << std::endl;
exec_instruction([&] () { instr_dec(_sp.word); }, 8);
break;
case 0x27:
std::cerr << std::hex << "daa(" << "" << ")" << std::endl;
exec_instruction([&] () { instr_daa(); }, 4);
break;
case 0x2F:
std::cerr << std::hex << "cpl(" << "" << ")" << std::endl;
exec_instruction([&] () { instr_cpl(); }, 4);
break;
case 0x3F:
std::cerr << std::hex << "ccf(" << "" << ")" << std::endl;
exec_instruction([&] () { instr_ccf(); }, 4);
break;
case 0x37:
std::cerr << std::hex << "scf(" << "" << ")" << std::endl;
exec_instruction([&] () { instr_scf(); }, 4);
break;
case 0x00:
std::cerr << std::hex << "nop(" << "" << ")" << std::endl;
exec_instruction([&] () { instr_nop(); }, 4);
break;
case 0x76:
std::cerr << std::hex << "halt(" << "" << ")" << std::endl;
exec_instruction([&] () { instr_halt(); }, 4);
break;
case 0x10:
std::cerr << std::hex << "stop(" << "" << ")" << std::endl;
exec_instruction([&] () { instr_stop(); }, 4);
break;
case 0xF3:
std::cerr << std::hex << "di(" << "" << ")" << std::endl;
exec_instruction([&] () { instr_di(); }, 4);
break;
case 0xFB:
std::cerr << std::hex << "ei(" << "" << ")" << std::endl;
exec_instruction([&] () { instr_ei(); }, 4);
break;
case 0x07:
std::cerr << std::hex << "rlc(" << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_rlc(_af.high); }, 4);
break;
case 0x17:
std::cerr << std::hex << "rl(" << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_rl(_af.high); }, 4);
break;
case 0x0F:
std::cerr << std::hex << "rrc(" << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_rrc(_af.high); }, 4);
break;
case 0x1F:
std::cerr << std::hex << "rr(" << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_rr(_af.high); }, 4);
break;
case 0xC3:
std::cerr << std::hex << "jp(" << "JumpCondition::None" << " " << "fetch_word()=" << " " << +static_cast<Word>(*it << 8 | *(it + 1)) << ")" << std::endl;
exec_instruction([&] () { instr_jp(JumpCondition::None, fetch_word()); }, 12);
break;
case 0xC2:
std::cerr << std::hex << "jp(" << "JumpCondition::NonZero" << " " << "fetch_word()=" << " " << +static_cast<Word>(*it << 8 | *(it + 1)) << ")" << std::endl;
exec_instruction([&] () { instr_jp(JumpCondition::NonZero, fetch_word()); }, 12);
break;
case 0xCA:
std::cerr << std::hex << "jp(" << "JumpCondition::Zero" << " " << "fetch_word()=" << " " << +static_cast<Word>(*it << 8 | *(it + 1)) << ")" << std::endl;
exec_instruction([&] () { instr_jp(JumpCondition::Zero, fetch_word()); }, 12);
break;
case 0xD2:
std::cerr << std::hex << "jp(" << "JumpCondition::NonCarry" << " " << "fetch_word()=" << " " << +static_cast<Word>(*it << 8 | *(it + 1)) << ")" << std::endl;
exec_instruction([&] () { instr_jp(JumpCondition::NonCarry, fetch_word()); }, 12);
break;
case 0xDA:
std::cerr << std::hex << "jp(" << "JumpCondition::Carry" << " " << "fetch_word()=" << " " << +static_cast<Word>(*it << 8 | *(it + 1)) << ")" << std::endl;
exec_instruction([&] () { instr_jp(JumpCondition::Carry, fetch_word()); }, 12);
break;
case 0xE9:
std::cerr << std::hex << "jp(" << "JumpCondition::None" << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_jp(JumpCondition::None, mem_bus->read<Byte>(_hl.word)); }, 4);
break;
case 0x18:
std::cerr << std::hex << "jr(" << "JumpCondition::None" << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_jr(JumpCondition::None, *it++); }, 8);
break;
case 0x20:
std::cerr << std::hex << "jr(" << "JumpCondition::NonZero" << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_jr(JumpCondition::NonZero, *it++); }, 8);
break;
case 0x28:
std::cerr << std::hex << "jr(" << "JumpCondition::Zero" << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_jr(JumpCondition::Zero, *it++); }, 8);
break;
case 0x30:
std::cerr << std::hex << "jr(" << "JumpCondition::NonCarry" << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_jr(JumpCondition::NonCarry, *it++); }, 8);
break;
case 0x38:
std::cerr << std::hex << "jr(" << "JumpCondition::Carry" << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_jr(JumpCondition::Carry, *it++); }, 8);
break;
case 0xCD:
std::cerr << std::hex << "call(" << "JumpCondition::None" << " " << "fetch_word()=" << " " << +static_cast<Word>(*it << 8 | *(it + 1)) << ")" << std::endl;
exec_instruction([&] () { instr_call(JumpCondition::None, fetch_word()); }, 12);
break;
case 0xC4:
std::cerr << std::hex << "call(" << "JumpCondition::NonZero" << " " << "fetch_word()=" << " " << +static_cast<Word>(*it << 8 | *(it + 1)) << ")" << std::endl;
exec_instruction([&] () { instr_call(JumpCondition::NonZero, fetch_word()); }, 12);
break;
case 0xCC:
std::cerr << std::hex << "call(" << "JumpCondition::Zero" << " " << "fetch_word()=" << " " << +static_cast<Word>(*it << 8 | *(it + 1)) << ")" << std::endl;
exec_instruction([&] () { instr_call(JumpCondition::Zero, fetch_word()); }, 12);
break;
case 0xD4:
std::cerr << std::hex << "call(" << "JumpCondition::NonCarry" << " " << "fetch_word()=" << " " << +static_cast<Word>(*it << 8 | *(it + 1)) << ")" << std::endl;
exec_instruction([&] () { instr_call(JumpCondition::NonCarry, fetch_word()); }, 12);
break;
case 0xDC:
std::cerr << std::hex << "call(" << "JumpCondition::Carry" << " " << "fetch_word()=" << " " << +static_cast<Word>(*it << 8 | *(it + 1)) << ")" << std::endl;
exec_instruction([&] () { instr_call(JumpCondition::Carry, fetch_word()); }, 12);
break;
case 0xC7:
std::cerr << std::hex << "rst(" << "0x00=" << " " << +0x00 << ")" << std::endl;
exec_instruction([&] () { instr_rst(0x00); }, 32);
break;
case 0xCF:
std::cerr << std::hex << "rst(" << "0x08=" << " " << +0x08 << ")" << std::endl;
exec_instruction([&] () { instr_rst(0x08); }, 32);
break;
case 0xD7:
std::cerr << std::hex << "rst(" << "0x10=" << " " << +0x10 << ")" << std::endl;
exec_instruction([&] () { instr_rst(0x10); }, 32);
break;
case 0xDF:
std::cerr << std::hex << "rst(" << "0x18=" << " " << +0x18 << ")" << std::endl;
exec_instruction([&] () { instr_rst(0x18); }, 32);
break;
case 0xE7:
std::cerr << std::hex << "rst(" << "0x20=" << " " << +0x20 << ")" << std::endl;
exec_instruction([&] () { instr_rst(0x20); }, 32);
break;
case 0xEF:
std::cerr << std::hex << "rst(" << "0x28=" << " " << +0x28 << ")" << std::endl;
exec_instruction([&] () { instr_rst(0x28); }, 32);
break;
case 0xF7:
std::cerr << std::hex << "rst(" << "0x30=" << " " << +0x30 << ")" << std::endl;
exec_instruction([&] () { instr_rst(0x30); }, 32);
break;
case 0xFF:
std::cerr << std::hex << "rst(" << "0x38=" << " " << +0x38 << ")" << std::endl;
exec_instruction([&] () { instr_rst(0x38); }, 32);
break;
case 0xC9:
std::cerr << std::hex << "ret(" << "JumpCondition::None" << ")" << std::endl;
exec_instruction([&] () { instr_ret(JumpCondition::None); }, 8);
break;
case 0xC0:
std::cerr << std::hex << "ret(" << "JumpCondition::NonZero" << ")" << std::endl;
exec_instruction([&] () { instr_ret(JumpCondition::NonZero); }, 8);
break;
case 0xC8:
std::cerr << std::hex << "ret(" << "JumpCondition::Zero" << ")" << std::endl;
exec_instruction([&] () { instr_ret(JumpCondition::Zero); }, 8);
break;
case 0xD0:
std::cerr << std::hex << "ret(" << "JumpCondition::NonCarry" << ")" << std::endl;
exec_instruction([&] () { instr_ret(JumpCondition::NonCarry); }, 8);
break;
case 0xD8:
std::cerr << std::hex << "ret(" << "JumpCondition::Carry" << ")" << std::endl;
exec_instruction([&] () { instr_ret(JumpCondition::Carry); }, 8);
break;
case 0xD9:
std::cerr << std::hex << "reti(" << "" << ")" << std::endl;
exec_instruction([&] () { instr_reti(); }, 8);
break;
case 0xCB:
switch(*it++) {
case 0x07:
std::cerr << std::hex << "rlc(" << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_rlc(_af.high); }, 8);
break;
case 0x00:
std::cerr << std::hex << "rlc(" << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_rlc(_bc.high); }, 8);
break;
case 0x01:
std::cerr << std::hex << "rlc(" << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_rlc(_bc.low); }, 8);
break;
case 0x02:
std::cerr << std::hex << "rlc(" << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_rlc(_de.high); }, 8);
break;
case 0x03:
std::cerr << std::hex << "rlc(" << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_rlc(_de.low); }, 8);
break;
case 0x04:
std::cerr << std::hex << "rlc(" << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_rlc(_hl.high); }, 8);
break;
case 0x05:
std::cerr << std::hex << "rlc(" << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_rlc(_hl.low); }, 8);
break;
case 0x06:
std::cerr << std::hex << "rlc(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_rlc(v); }, _hl.word, 16);
break;
case 0x17:
std::cerr << std::hex << "rl(" << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_rl(_af.high); }, 8);
break;
case 0x10:
std::cerr << std::hex << "rl(" << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_rl(_bc.high); }, 8);
break;
case 0x11:
std::cerr << std::hex << "rl(" << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_rl(_bc.low); }, 8);
break;
case 0x12:
std::cerr << std::hex << "rl(" << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_rl(_de.high); }, 8);
break;
case 0x13:
std::cerr << std::hex << "rl(" << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_rl(_de.low); }, 8);
break;
case 0x14:
std::cerr << std::hex << "rl(" << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_rl(_hl.high); }, 8);
break;
case 0x15:
std::cerr << std::hex << "rl(" << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_rl(_hl.low); }, 8);
break;
case 0x16:
std::cerr << std::hex << "rl(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_rl(v); }, _hl.word, 16);
break;
case 0x0F:
std::cerr << std::hex << "rrc(" << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_rrc(_af.high); }, 8);
break;
case 0x08:
std::cerr << std::hex << "rrc(" << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_rrc(_bc.high); }, 8);
break;
case 0x09:
std::cerr << std::hex << "rrc(" << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_rrc(_bc.low); }, 8);
break;
case 0x0A:
std::cerr << std::hex << "rrc(" << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_rrc(_de.high); }, 8);
break;
case 0x0B:
std::cerr << std::hex << "rrc(" << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_rrc(_de.low); }, 8);
break;
case 0x0C:
std::cerr << std::hex << "rrc(" << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_rrc(_hl.high); }, 8);
break;
case 0x0D:
std::cerr << std::hex << "rrc(" << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_rrc(_hl.low); }, 8);
break;
case 0x0E:
std::cerr << std::hex << "rrc(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_rrc(v); }, _hl.word, 16);
break;
case 0x1F:
std::cerr << std::hex << "rr(" << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_rr(_af.high); }, 8);
break;
case 0x18:
std::cerr << std::hex << "rr(" << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_rr(_bc.high); }, 8);
break;
case 0x19:
std::cerr << std::hex << "rr(" << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_rr(_bc.low); }, 8);
break;
case 0x1A:
std::cerr << std::hex << "rr(" << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_rr(_de.high); }, 8);
break;
case 0x1B:
std::cerr << std::hex << "rr(" << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_rr(_de.low); }, 8);
break;
case 0x1C:
std::cerr << std::hex << "rr(" << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_rr(_hl.high); }, 8);
break;
case 0x1D:
std::cerr << std::hex << "rr(" << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_rr(_hl.low); }, 8);
break;
case 0x1E:
std::cerr << std::hex << "rr(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_rr(v); }, _hl.word, 16);
break;
case 0x27:
std::cerr << std::hex << "sla(" << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_sla(_af.high); }, 8);
break;
case 0x20:
std::cerr << std::hex << "sla(" << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_sla(_bc.high); }, 8);
break;
case 0x21:
std::cerr << std::hex << "sla(" << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_sla(_bc.low); }, 8);
break;
case 0x22:
std::cerr << std::hex << "sla(" << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_sla(_de.high); }, 8);
break;
case 0x23:
std::cerr << std::hex << "sla(" << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_sla(_de.low); }, 8);
break;
case 0x24:
std::cerr << std::hex << "sla(" << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_sla(_hl.high); }, 8);
break;
case 0x25:
std::cerr << std::hex << "sla(" << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_sla(_hl.low); }, 8);
break;
case 0x26:
std::cerr << std::hex << "sla(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_sla(v); }, _hl.word, 16);
break;
case 0x2F:
std::cerr << std::hex << "sra(" << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_sra(_af.high); }, 8);
break;
case 0x28:
std::cerr << std::hex << "sra(" << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_sra(_bc.high); }, 8);
break;
case 0x29:
std::cerr << std::hex << "sra(" << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_sra(_bc.low); }, 8);
break;
case 0x2A:
std::cerr << std::hex << "sra(" << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_sra(_de.high); }, 8);
break;
case 0x2B:
std::cerr << std::hex << "sra(" << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_sra(_de.low); }, 8);
break;
case 0x2C:
std::cerr << std::hex << "sra(" << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_sra(_hl.high); }, 8);
break;
case 0x2D:
std::cerr << std::hex << "sra(" << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_sra(_hl.low); }, 8);
break;
case 0x2E:
std::cerr << std::hex << "sra(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_sra(v); }, _hl.word, 16);
break;
case 0x37:
std::cerr << std::hex << "swap(" << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_swap(_af.high); }, 8);
break;
case 0x30:
std::cerr << std::hex << "swap(" << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_swap(_bc.high); }, 8);
break;
case 0x31:
std::cerr << std::hex << "swap(" << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_swap(_bc.low); }, 8);
break;
case 0x32:
std::cerr << std::hex << "swap(" << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_swap(_de.high); }, 8);
break;
case 0x33:
std::cerr << std::hex << "swap(" << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_swap(_de.low); }, 8);
break;
case 0x34:
std::cerr << std::hex << "swap(" << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_swap(_hl.high); }, 8);
break;
case 0x35:
std::cerr << std::hex << "swap(" << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_swap(_hl.low); }, 8);
break;
case 0x36:
std::cerr << std::hex << "swap(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_swap(v); }, _hl.word, 16);
break;
case 0x3F:
std::cerr << std::hex << "srl(" << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_srl(_af.high); }, 8);
break;
case 0x38:
std::cerr << std::hex << "srl(" << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_srl(_bc.high); }, 8);
break;
case 0x39:
std::cerr << std::hex << "srl(" << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_srl(_bc.low); }, 8);
break;
case 0x3A:
std::cerr << std::hex << "srl(" << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_srl(_de.high); }, 8);
break;
case 0x3B:
std::cerr << std::hex << "srl(" << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_srl(_de.low); }, 8);
break;
case 0x3C:
std::cerr << std::hex << "srl(" << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_srl(_hl.high); }, 8);
break;
case 0x3D:
std::cerr << std::hex << "srl(" << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_srl(_hl.low); }, 8);
break;
case 0x3E:
std::cerr << std::hex << "srl(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_srl(v); }, _hl.word, 16);
break;
case 0x47:
std::cerr << std::hex << "bit(" << "*it++=" << " " << +*it << " " << "_af.high=" << " " << +_af.high << ")" << std::endl;
exec_instruction([&] () { instr_bit(*it++, _af.high); }, 8);
break;
case 0x40:
std::cerr << std::hex << "bit(" << "*it++=" << " " << +*it << " " << "_bc.high=" << " " << +_bc.high << ")" << std::endl;
exec_instruction([&] () { instr_bit(*it++, _bc.high); }, 8);
break;
case 0x41:
std::cerr << std::hex << "bit(" << "*it++=" << " " << +*it << " " << "_bc.low=" << " " << +_bc.low << ")" << std::endl;
exec_instruction([&] () { instr_bit(*it++, _bc.low); }, 8);
break;
case 0x42:
std::cerr << std::hex << "bit(" << "*it++=" << " " << +*it << " " << "_de.high=" << " " << +_de.high << ")" << std::endl;
exec_instruction([&] () { instr_bit(*it++, _de.high); }, 8);
break;
case 0x43:
std::cerr << std::hex << "bit(" << "*it++=" << " " << +*it << " " << "_de.low=" << " " << +_de.low << ")" << std::endl;
exec_instruction([&] () { instr_bit(*it++, _de.low); }, 8);
break;
case 0x44:
std::cerr << std::hex << "bit(" << "*it++=" << " " << +*it << " " << "_hl.high=" << " " << +_hl.high << ")" << std::endl;
exec_instruction([&] () { instr_bit(*it++, _hl.high); }, 8);
break;
case 0x45:
std::cerr << std::hex << "bit(" << "*it++=" << " " << +*it << " " << "_hl.low=" << " " << +_hl.low << ")" << std::endl;
exec_instruction([&] () { instr_bit(*it++, _hl.low); }, 8);
break;
case 0x46:
std::cerr << std::hex << "bit(" << "*it++=" << " " << +*it << " " << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << ")" << std::endl;
exec_instruction([&] () { instr_bit(*it++, mem_bus->read<Byte>(_hl.word)); }, 16);
break;
case 0xC7:
std::cerr << std::hex << "set(" << "_af.high=" << " " << +_af.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_set(_af.high, *it++); }, 8);
break;
case 0xC0:
std::cerr << std::hex << "set(" << "_bc.high=" << " " << +_bc.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_set(_bc.high, *it++); }, 8);
break;
case 0xC1:
std::cerr << std::hex << "set(" << "_bc.low=" << " " << +_bc.low << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_set(_bc.low, *it++); }, 8);
break;
case 0xC2:
std::cerr << std::hex << "set(" << "_de.high=" << " " << +_de.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_set(_de.high, *it++); }, 8);
break;
case 0xC3:
std::cerr << std::hex << "set(" << "_de.low=" << " " << +_de.low << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_set(_de.low, *it++); }, 8);
break;
case 0xC4:
std::cerr << std::hex << "set(" << "_hl.high=" << " " << +_hl.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_set(_hl.high, *it++); }, 8);
break;
case 0xC5:
std::cerr << std::hex << "set(" << "_hl.low=" << " " << +_hl.low << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_set(_hl.low, *it++); }, 8);
break;
case 0xC6:
std::cerr << std::hex << "set(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_set(v, *it++); }, _hl.word, 16);
break;
case 0x87:
std::cerr << std::hex << "res(" << "_af.high=" << " " << +_af.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_res(_af.high, *it++); }, 8);
break;
case 0x80:
std::cerr << std::hex << "res(" << "_bc.high=" << " " << +_bc.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_res(_bc.high, *it++); }, 8);
break;
case 0x81:
std::cerr << std::hex << "res(" << "_bc.low=" << " " << +_bc.low << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_res(_bc.low, *it++); }, 8);
break;
case 0x82:
std::cerr << std::hex << "res(" << "_de.high=" << " " << +_de.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_res(_de.high, *it++); }, 8);
break;
case 0x83:
std::cerr << std::hex << "res(" << "_de.low=" << " " << +_de.low << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_res(_de.low, *it++); }, 8);
break;
case 0x84:
std::cerr << std::hex << "res(" << "_hl.high=" << " " << +_hl.high << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_res(_hl.high, *it++); }, 8);
break;
case 0x85:
std::cerr << std::hex << "res(" << "_hl.low=" << " " << +_hl.low << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] () { instr_res(_hl.low, *it++); }, 8);
break;
case 0x86:
std::cerr << std::hex << "res(" << "&_hl.word=" << " " << +mem_bus->read<Byte>(_hl.word) << " " << "*it++=" << " " << +*it << ")" << std::endl;
exec_instruction([&] (Byte &v) { instr_res(v, *it++); }, _hl.word, 16);
break;
}
break;
