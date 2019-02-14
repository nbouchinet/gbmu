#include "Debugger.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <algorithm>
#include "src/Gameboy.hpp"
#include "src/cpu/InterruptController.hpp"

Debugger::Debugger(ComponentsContainer &components) : _components(components)
{
	_register_pool = construct_register_pool();
}


Debugger::_debug_info::_debug_info(uint16_t _pc, const Debugger::_instr_info &_map_info, Core::Iterator _it, uint8_t _size) :
	pc(_pc),
	instr(_map_info.instr),
	size(_size)
{
	for (int i = 0; i < 3; i++) {
		value[i] = *(_it + i);
	}
}

using it = std::vector<Byte>::const_iterator;
const std::vector<std::pair<int, uint16_t>> Debugger::get_differences(it prev_begin, it current_begin)
{
	std::vector<std::pair<int, uint16_t>> diffs;

	for (int i = 0; i <= 32; i++, prev_begin++, current_begin++) {
		if (*prev_begin != *current_begin) {
			diffs.emplace_back(i, *current_begin);
		}
	}
	return diffs;
}

void Debugger::update(const Core::Iterator &it, uint16_t pc)
{
	std::vector<uint16_t> current;
	std::vector<std::pair<int, uint16_t>> diffs;

	set_instruction_pool(it, pc);
	current = construct_register_pool();
	diffs = get_differences(_register_pool.cbegin(), current.cbegin());
	_register_pool = current;
	//wait_user_interaction(pc);
}

/**
 * Here it is the current iterator, not begin.
 */

void Debugger::set_instruction_pool(const Core::Iterator &it, uint16_t pc)
{
	uint16_t	pc_add;
	auto		mit = _instr_map.begin();
	auto		mit_next = _instr_map.begin();
	auto		mit_cb = _instr_map.begin();

	pc_add = 0;
	_instr_pool.clear();
	_instr_pool.reserve(_frame_size);

	for (int i = 0; i <= _frame_size; i++) {
		mit = _instr_map.find(*(it + pc_add));
		mit_next = _instr_map.find(*(it + 1 + pc_add));
		mit_cb = _instr_map.find((*(it + 1 + pc_add)) | 0xCB00);

		if (*(it + pc_add) == 0xCB && mit_next != _instr_map.end()) {
			_instr_pool.emplace_back(pc + pc_add, mit->second, it + pc_add, mit_cb->second.size);
			pc_add += mit_cb->second.size;
		} else if (mit != _instr_map.end()) {
			_instr_pool.emplace_back(pc + pc_add, mit->second, it + pc_add, mit->second.size);
			pc_add += mit->second.size;
		} else {
			Debugger::_instr_info bad_value = {"??", 0x00};
			_instr_pool.emplace_back(pc + pc_add, bad_value, it + pc_add, 0);
		}
	}
	//print_instruction_pool();
}

void Debugger::print_instruction_pool()
{
	system("sh -c clear");
	for (Debugger::_debug_info d : _instr_pool) {
		printf("[0x%08x] %s\t", d.pc, d.instr);
		for (uint8_t i = 0; i < d.size; i++) {
			printf("%x ", d.value[i]);
		}
		printf("\n");
	}
}

void Debugger::print_breakpoint_list()
{
	for (uint16_t addr : _breakpoint_pool) {
		printf("0x%08x\n", addr);
	}

}

void Debugger::add_breakpoint(uint16_t addr)
{
	if (std::find(_breakpoint_pool.begin(), _breakpoint_pool.end(), addr) == _breakpoint_pool.end()) {
		_breakpoint_pool.push_back(addr);
	}
}

void Debugger::remove_breakpoint(uint16_t addr)
{
	_breakpoint_pool.erase(std::find(_breakpoint_pool.begin(), _breakpoint_pool.end(), addr));
}

std::vector<uint16_t> Debugger::construct_register_pool()
{
	std::vector<uint16_t> rpool(33);
	//general registers
	rpool[0] = {_components.mem_bus->read<Byte>(0xFF00)};
	rpool[1] = {_components.mem_bus->read<Byte>(0xFF01)};
	rpool[2] = {_components.mem_bus->read<Byte>(0xFF02)};
	rpool[3] = {_components.mem_bus->read<Byte>(0xFF04)};
	rpool[4] = {_components.mem_bus->read<Byte>(0xFF05)};
	rpool[5] = {_components.mem_bus->read<Byte>(0xFF06)};
	rpool[6] = {_components.mem_bus->read<Byte>(0xFF07)};
	rpool[7] = {_components.mem_bus->read<Byte>(0xFF4D)};
	rpool[8] = {_components.mem_bus->read<Byte>(0xFF4F)};
	rpool[9] = {_components.mem_bus->read<Byte>(0xFF51)};
	rpool[10] = {_components.mem_bus->read<Byte>(0xFF52)};
	rpool[11] = {_components.mem_bus->read<Byte>(0xFF53)};
	rpool[12] = {_components.mem_bus->read<Byte>(0xFF54)};
	rpool[13] = {_components.mem_bus->read<Byte>(0xFF55)};
	rpool[14] = {_components.mem_bus->read<Byte>(0xFF70)};
	rpool[15] = {_components.mem_bus->read<Byte>(0xFF0F)};
	rpool[16] = {_components.mem_bus->read<Byte>(0xFFFF)};
	// video registers
	rpool[17] = {_components.mem_bus->read<Byte>(0xFF40)};
	rpool[18] = {_components.mem_bus->read<Byte>(0xFF41)};
	rpool[19] = {_components.mem_bus->read<Byte>(0xFF42)};
	rpool[20] = {_components.mem_bus->read<Byte>(0xFF43)};
	rpool[21] = {_components.mem_bus->read<Byte>(0xFF44)};
	rpool[22] = {_components.mem_bus->read<Byte>(0xFF45)};
	rpool[23] = {_components.mem_bus->read<Byte>(0xFF46)};
	rpool[24] = {_components.mem_bus->read<Byte>(0xFF47)};
	rpool[25] = {_components.mem_bus->read<Byte>(0xFF48)};
	rpool[26] = {_components.mem_bus->read<Byte>(0xFF49)};
	rpool[27] = {_components.mem_bus->read<Byte>(0xFF4A)};
	rpool[28] = {_components.mem_bus->read<Byte>(0xFF4B)};
	rpool[29] = {_components.mem_bus->read<Byte>(0xFF68)};
	rpool[30] = {_components.mem_bus->read<Byte>(0xFF69)};
	rpool[31] = {_components.mem_bus->read<Byte>(0xFF6A)};
	rpool[32] = {_components.mem_bus->read<Byte>(0xFF6B)};

	return rpool;
}

void Debugger::wait_user_interaction(uint16_t pc)
{
	char n;
	static time_t totime = 0;
	std::string input;

	if ((totime != 0 && time(NULL) >= totime) || std::find(_breakpoint_pool.begin(), _breakpoint_pool.end(), pc) != _breakpoint_pool.end()) {
		totime = 0;
		_wait_next = 1;
	}
	while (_wait_next) {
		std::cout << "\n: ";
start:
		n = getchar();
		if (n == '\n')
			goto start;
		if (n == 's') {
			std::cin >> input;
			totime = time(NULL) + stoi(input);
			_wait_next = 0;
		} else if (n == 'b') {
			std::cin >> input;
			if (input == "list") {
				print_instruction_pool();
				print_breakpoint_list();
				continue ;
			}
			else {
				add_breakpoint(stoi(input, 0, 16));
			}
		} else if (n == 'd') {
			std::cin >> input;
			remove_breakpoint(stoi(input, 0, 16));
		} else if (n == 'c') {
			_wait_next = 0;
			break ;
		}
		break ;
	}
}
