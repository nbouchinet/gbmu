#include "Debugger.hpp"
#include "src/Gameboy.hpp"
#include "src/cpu/InterruptController.hpp"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <ratio>
#include <unistd.h>
#include <vector>

Debugger::Debugger(ComponentsContainer &components) : _components(components) {
  _enabled = false;
  _register_pool = construct_register_pool();
}

Debugger::_debug_info::_debug_info(uint16_t _pc,
                                   const Debugger::_instr_info &_map_info,
                                   Core::Iterator _it, uint8_t _size)
    : pc(_pc), instr(_map_info.instr), size(_size) {
  for (int i = 0; i < 3; i++) {
    value[i] = *(_it + i);
  }
}

const std::vector<std::pair<int, uint16_t>>
Debugger::rdiff(const std::vector<uint16_t> &prev,
                const std::vector<uint16_t> &current) {
  auto prev_begin = prev.cbegin();
  auto current_begin = current.cbegin();
  auto prev_end = prev.cend();
  auto current_end = current.cend();

  std::vector<std::pair<int, uint16_t>> diffs;

  for (int i = 0; (prev_begin != prev_end) && (current_begin != current_end);
       i++, prev_begin++, current_begin++) {
    if (*prev_begin != *current_begin) {
      diffs.emplace_back(i, *current_begin);
    }
  }
  return diffs;
}

const std::vector<std::pair<int, uint16_t>> Debugger::get_register_diffs() {
  std::vector<std::pair<int, uint16_t>> register_diffs;

  register_diffs = _register_diffs;
  _register_diffs.clear();
  return register_diffs;
}

/**
 * Here it is the current iterator, not begin.
 */

void Debugger::set_instruction_pool(const Core::Iterator &it, uint16_t pc) {
  uint16_t pc_add;
  auto mit = _instr_map.begin();
  auto mit_next = _instr_map.begin();
  auto mit_cb = _instr_map.begin();

  pc_add = 0;
  _instr_pool.clear();
  _instr_pool.reserve(_frame_size);

  for (int i = 0; i <= _frame_size; i++) {
    mit = _instr_map.find(*(it + pc_add));
    mit_next = _instr_map.find(*(it + 1 + pc_add));
    mit_cb = _instr_map.find((*(it + 1 + pc_add)) | 0xCB00);

    if (*(it + pc_add) == 0xCB && mit_next != _instr_map.end()) {
      _instr_pool.emplace_back(pc + pc_add, mit->second, it + pc_add,
                               mit_cb->second.size);
      pc_add += mit_cb->second.size;
    } else if (mit != _instr_map.end()) {
      _instr_pool.emplace_back(pc + pc_add, mit->second, it + pc_add,
                               mit->second.size);
      pc_add += mit->second.size;
    } else {
      Debugger::_instr_info bad_value = {"??", 0x00};
      _instr_pool.emplace_back(pc + pc_add, bad_value, it + pc_add, 0);
    }
  }
}

void Debugger::add_breakpoint(uint16_t addr) {
  if (std::find(_breakpoint_pool.begin(), _breakpoint_pool.end(), addr) ==
      _breakpoint_pool.end()) {
    _breakpoint_pool.push_back(addr);
  }
}

void Debugger::remove_breakpoint(uint16_t addr) {
  _breakpoint_pool.erase(
      std::find(_breakpoint_pool.begin(), _breakpoint_pool.end(), addr));
}

uint16_t Debugger::get_register_value(uint16_t addr) {
  uint16_t value;

  switch (addr) {
  case 0:
    value = _components.core->pc();
  case 1:
    value = _components.core->af().word;
  case 2:
    value = _components.core->bc().word;
  case 3:
    value = _components.core->de().word;
  case 4:
    value = _components.core->hl().word;
  case 5:
    value = _components.core->sp();
  default:
    value = _components.mem_bus->read<Byte>(addr);
  }
  return value;
}

void Debugger::add_watchpoint(uint16_t addr, int w_value) {
  uint16_t value = get_register_value(addr);

  auto compare =
      [&](const std::pair<uint16_t, _watchpoint_value> &pair) -> bool {
    return pair.first == addr && pair.second.r_value == value &&
           pair.second.w_value == w_value;
  };

  if (std::find_if(_watchpoint_pool.begin(), _watchpoint_pool.end(), compare) ==
      _watchpoint_pool.end()) {
    _watchpoint_value s_w_value = {value, w_value};
    _watchpoint_pool.emplace_back(addr, s_w_value);
  }
}

void Debugger::remove_watchpoint(uint16_t addr, int w_value) {
  uint16_t value = get_register_value(addr);

  auto compare =
      [&](const std::pair<uint16_t, _watchpoint_value> &pair) -> bool {
    return pair.first == addr && pair.second.r_value == value &&
           pair.second.w_value == w_value;
  };

  _watchpoint_pool.erase(
      std::find_if(_watchpoint_pool.begin(), _watchpoint_pool.end(), compare));
}

bool Debugger::watchpoint_changed() {
  bool find = false;

  for (auto value : _watchpoint_pool) {
    auto register_value = get_register_value(value.first);

    if ((value.second.w_value != -1 &&
         value.second.r_value != register_value) ||
        (value.second.w_value == register_value)) {
      value.second.r_value = register_value;
      find = true;
    }
  }
  return find;
}

std::vector<uint16_t> Debugger::construct_register_pool() {
  std::vector<uint16_t> rpool(40);
  // registers
  rpool[0] = {_components.core->pc()};
  rpool[1] = {_components.core->af().word};
  rpool[2] = {_components.core->bc().word};
  rpool[3] = {_components.core->de().word};
  rpool[4] = {_components.core->hl().word};
  rpool[5] = {_components.core->sp()};
  // video registers
  rpool[6] = {_components.mem_bus->read<Byte>(0xFF40)};
  rpool[7] = {_components.mem_bus->read<Byte>(0xFF41)};
  rpool[8] = {_components.mem_bus->read<Byte>(0xFF42)};
  rpool[9] = {_components.mem_bus->read<Byte>(0xFF43)};
  rpool[10] = {_components.mem_bus->read<Byte>(0xFF44)};
  rpool[11] = {_components.mem_bus->read<Byte>(0xFF45)};
  rpool[12] = {_components.mem_bus->read<Byte>(0xFF46)};
  rpool[13] = {_components.mem_bus->read<Byte>(0xFF47)};
  rpool[14] = {_components.mem_bus->read<Byte>(0xFF48)};
  rpool[15] = {_components.mem_bus->read<Byte>(0xFF49)};
  rpool[16] = {_components.mem_bus->read<Byte>(0xFF4A)};
  rpool[17] = {_components.mem_bus->read<Byte>(0xFF4B)};
  rpool[18] = {_components.mem_bus->read<Byte>(0xFF68)};
  rpool[19] = {_components.mem_bus->read<Byte>(0xFF69)};
  rpool[20] = {_components.mem_bus->read<Byte>(0xFF6A)};
  rpool[21] = {_components.mem_bus->read<Byte>(0xFF6B)};
  // general registers
  rpool[22] = {_components.mem_bus->read<Byte>(0xFF00)};
  rpool[23] = {_components.mem_bus->read<Byte>(0xFF01)};
  rpool[24] = {_components.mem_bus->read<Byte>(0xFF02)};
  rpool[25] = {_components.mem_bus->read<Byte>(0xFF04)};
  rpool[26] = {_components.mem_bus->read<Byte>(0xFF05)};
  rpool[27] = {_components.mem_bus->read<Byte>(0xFF06)};
  rpool[28] = {_components.mem_bus->read<Byte>(0xFF07)};
  rpool[29] = {_components.mem_bus->read<Byte>(0xFF4D)};
  rpool[30] = {_components.mem_bus->read<Byte>(0xFF4F)};
  rpool[31] = {_components.mem_bus->read<Byte>(0xFF51)};
  rpool[32] = {_components.mem_bus->read<Byte>(0xFF52)};
  rpool[33] = {_components.mem_bus->read<Byte>(0xFF53)};
  rpool[34] = {_components.mem_bus->read<Byte>(0xFF54)};
  rpool[35] = {_components.mem_bus->read<Byte>(0xFF55)};
  rpool[36] = {_components.mem_bus->read<Byte>(0xFF70)};
  rpool[37] = {_components.mem_bus->read<Byte>(0xFF0F)};
  rpool[38] = {_components.mem_bus->read<Byte>(0xFFFF)};

  return rpool;
}

const std::vector<Byte> Debugger::get_memory_dump(Byte address) const {
  std::vector<Byte> memory_dump;

  for (int i = 0; i <= 100; i++) {
    if (address + i < 0xFFFF) {
      memory_dump.push_back(_components.mem_bus->read<Byte>(address + i));
    }
  }
  return memory_dump;
}

bool Debugger::on_breakpoint(uint16_t pc) {
  if (std::find(_breakpoint_pool.begin(), _breakpoint_pool.end(), pc) !=
      _breakpoint_pool.end()) {
    return true;
  }
  return false;
}

bool Debugger::is_frame_passed() {
  if (_run_one_frame && _components.ppu->isScreenFilled()) {
    _run_one_frame = false;
    return true;
  }
  return false;
}

void Debugger::run_duration(int duration) {
  _register_pool = construct_register_pool();
  _duration = duration;
  _past = std::chrono::high_resolution_clock::now();
  _run_duration = true;
  _lock = false;
}

void Debugger::run_one_frame() {
  _register_pool = construct_register_pool();
  _run_one_frame = true;
  _lock = false;
}

void Debugger::run_one_step() {
  _register_pool = construct_register_pool();
  _run_one_step = true;
  _lock = false;
}

bool Debugger::is_step_passed() {
  if (_run_one_step) {
    _run_one_step = false;
    return true;
  }
  return false;
}

bool Debugger::is_sec_passed() {
  std::chrono::time_point<std::chrono::high_resolution_clock> current =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = current - _past;

  if (_run_duration) {
    if (elapsed_seconds.count() >= _duration) {
      _run_duration = false;
      return true;
    }
  }
  return false;
}

void Debugger::lock_game(const Core::Iterator &it, uint16_t pc) {
  if (on_breakpoint(pc) || is_sec_passed() || is_frame_passed() ||
      is_step_passed() || watchpoint_changed()) {
    update_data(it, pc);
    _lock = true;
  }
}

void Debugger::fetch(const Core::Iterator &it, uint16_t pc) {
  static int first_time = 0;

  if (first_time == 0) {
    update_data(it, pc);
    first_time = 1;
  }
  lock_game(it, pc);
  while (_lock) {
  }
}

void Debugger::update_data(const Core::Iterator &it, uint16_t pc) {
  std::vector<uint16_t> current;

  set_instruction_pool(it, pc);
  current = construct_register_pool();
  _register_diffs = rdiff(_register_pool, current);
}
