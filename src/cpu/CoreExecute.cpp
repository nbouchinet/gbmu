#include "Core.hpp"
#include "src/Gameboy.hpp"

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
