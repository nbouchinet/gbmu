#include "Core.hpp"
#include "src/Gameboy.hpp"

// void Core::execute(Core::Iterator it) {
// if (_halt)
// return;
// it += _pc.word;
// Iterator original_it = it;
// auto fetch_word = [&]() -> Word {
// Word ret = *it++;
// ret |= *it++ << 8;
// return ret;
//};
// switch (*it++) {
//#include "instructions.inc"
// default:
// break;
//}
// if (_in_jump_state)
//_in_jump_state = false;
// else
//_pc.word += it - original_it;
//}

void Core::execute() {
  if (_halt)
    return;

  Word addr = _pc.word;
  Word original_addr = addr;

  auto fetch_word = [&]() -> Word {
    Word ret = _components.mem_bus->read<Byte>(addr++);
    ret |= _components.mem_bus->read<Byte>(addr++) << 8;
    return ret;
  };
  switch (_components.mem_bus->read<Byte>(addr++)) {
#include "instructions.inc"
    default:
      break;
  }
  if (_in_jump_state) {
    _in_jump_state = false;
  }
  else {
    _pc.word += addr - original_addr;
  }
  _has_jumped = false;
}
