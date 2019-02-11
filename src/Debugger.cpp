#include "Debugger.hpp"
#include <iostream>
#include <vector>

void Debugger::get_instruction_set(const Core::Iterator &it)
{
	int		i = 0;
	uint16_t	pc_swap;
	std::vector<const char *> instr_set;

	instr_set.reserve(10);

	pc_swap = 0;
	while (i <= 10) {
		//		std::cerr << "Current opcode : [" << std::hex << +*(it + pc_swap) + pc_swap << "] : ";
		if (*(it + pc_swap) == 0xCB && m.find(*(it + 1 + pc_swap)) != m.end()) {
			//			std::cerr << m.find((+*(it + 1 + pc_swap)) | 0xCB00)->second.instr << std::endl;
			instr_set.push_back(m.find((*(it + 1 + pc_swap)) | 0xCB00)->second.instr);
			pc_swap += m.find((*(it + 1 + pc_swap)) | 0xCB00)->second.size;
		} else if (m.find(*(it + pc_swap)) != m.end()) {
			//			std::cerr << m.find(+*(it + pc_swap))->second.instr << std::endl;
			instr_set.push_back(m.find(*(it + pc_swap))->second.instr);
			pc_swap += m.find(*(it + pc_swap))->second.size;
		} else {
			//	instr_set.insert("unkown instruction : " + std::hex << +*(it + pc_swap));
			//			std::cerr << "unknown instruction : " << std::hex << +*(it + pc_swap) << std::endl;
		}
		i++;
	}
	for (const char *instr : instr_set) {
		std::cout << instr << std::endl;
	}
}

void Debugger::wait_user_interaction()
{
	char n;

	while (_wait_next) {
		std::cout << "\nEnter a key" << std::endl;
		std::cin >> n;
		system("sh -c clear");
		break ;
	}
}
