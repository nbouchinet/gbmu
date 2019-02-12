#include "Debugger.hpp"
#include <iostream>
#include <vector>

Debugger::_debug_info Debugger::gen_debug_info(uint16_t pc, uint16_t opcode, _instr_info map_info)
{
	Debugger::_debug_info debug = {pc, opcode, map_info.instr, map_info.size};

	return debug;
}

void Debugger::get_instruction_set(const Core::Iterator &it, uint16_t pc)
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
	for (auto && _debug_info : _instr_pool) {// TODO: debug, remove
		printf("[0x%08x] 0x%04x %s\n", _debug_info.pc, _debug_info.opcode, _debug_info.instr);
	}
}

void Debugger::wait_user_interaction()
{
	char n;

	while (_wait_next) {
		std::cout << "\nEnter a key" << std::endl;
		n = getchar();
		system("sh -c clear");
		break ;
	}
}
