#include "Core.hpp"

void Core::instr_ldd(Byte& a, Byte b) {
  a = b;
  --_hl.word;
}

void Core::instr_ldi(Byte& a, Byte b) {
  a = b;
  ++_hl.word;
}

void Core::instr_ldhl(Byte& n) {
  _hl.word = _sp.word + static_cast<int8_t>(n);
  //TODO set H 
  _flags = 0u;
}

void Core::instr_push(Word v) {
  write_byte(_sp.word--, v & 0xFF00);
  write_byte(_sp.word--, v & 0x00FF);
}

void Core::instr_pop(Word& dest) {
  dest |= static_cast<Word>(read_byte(_sp.word++)) << 8;
  dest += read_byte(_sp.word++);
}

void Core::instr_add(Word& dest) {
  dest |= static_cast<Word>(read_byte(_sp.word++)) << 8;
  dest += read_byte(_sp.word++);
}
