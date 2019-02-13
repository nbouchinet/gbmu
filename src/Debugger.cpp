#include "Debugger.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <algorithm>


Debugger::_debug_info Debugger::gen_debug_info(uint16_t pc, uint16_t opcode, _instr_info map_info)
{
	Debugger::_debug_info debug = {pc, opcode, map_info.instr, map_info.size};

	return debug;
}

void Debugger::set_instruction_pool(const Core::Iterator &it, uint16_t pc)
{
	int		i = 0;
	uint16_t	pc_swap;
	uint16_t	false_pc;
	auto		mit = _instr_map.begin();
	auto		mit_next = _instr_map.begin();
	auto		mit_cb = _instr_map.begin();

	pc_swap = pc;
	false_pc = 0;
	_instr_pool.clear();
	_instr_pool.reserve(_frame_size);

	while (i <= _frame_size) {
		mit = _instr_map.find(*(it + false_pc));
		mit_next = _instr_map.find(*(it + 1 + false_pc));
		mit_cb = _instr_map.find((*(it + 1 + false_pc)) | 0xCB00);

		if (*(it + false_pc) == 0xCB && mit_next != _instr_map.end()) {
			_instr_pool.push_back(gen_debug_info(pc_swap + false_pc, *(it + 1 + false_pc) | 0xCB00, mit_cb->second));
			false_pc += mit_cb->second.size;
		} else if (mit != _instr_map.end()) {
			_instr_pool.push_back(gen_debug_info(pc_swap + false_pc, *(it + false_pc), mit->second));
			false_pc += mit->second.size;
		} else {
			Debugger::_instr_info bad_value = {"??", 0x00};
			_instr_pool.push_back(gen_debug_info(pc_swap + false_pc, *(it + false_pc), bad_value));
		}
		i++;
	}
	print_instruction_pool();
}

void Debugger::print_instruction_pool()
{
	system("sh -c clear");
	for (auto && _debug_info : _instr_pool) {
		printf("[0x%08x] 0x%04x %s\n", _debug_info.pc, _debug_info.opcode, _debug_info.instr);
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
