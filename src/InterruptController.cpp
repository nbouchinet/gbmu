#include "InterruptController.hpp"
#include "cpu/Core.hpp"

InterruptController::InterruptController()
{
}

void	InterruptController::SetCore(Core *core)
{
	this->core = core;
}

void InterruptController::Write(uint16_t addr, uint8_t val)
{
	std::cout << "WRITE_INT" << std::endl;
	switch (addr) {
		case 0xFF0F:
			_rIF = val;
			break ;
		case 0xFFFF:
			_rIE = val;
			break ;
		default:
			return ;
	}
}

uint8_t InterruptController::Read(uint16_t addr) const
{
	std::cout << "READ_INT" << std::endl;
	switch (addr) {
		case 0xFF0F:
			return (_rIF);
		case 0xFFFF:
			return (_rIE);
		default:
			return (0);
	}
}

void InterruptController::ParseInterrupt()
{
	uint8_t rIF;
	uint8_t rIE;

	std::cout << "ParseInterrupt" << std::endl;
	rIF = _rIF;
	rIE = _rIE;
	if (_rIME && rIF) {
		for (uint8_t i = 0; i < 5; i--) {
			if ((rIF & 0x01) == (rIE & 0x01)) {
				std::cout << "ExecuteInterrupt" << i << std::endl;
				ExecuteInterrupt(i);
			}
			rIF >>= rIF;
			rIE >>= rIE;
		}
	}
}

void InterruptController::ExecuteInterrupt(uint8_t interrupt)
{
	_rIME = 0;
	_rIF = (_rIF & ~interrupt);
	switch (interrupt) {
		case 0:
			std::cout << "vertical blank interrupt" << std::endl;
			core->instr_call(Core::JumpCondition::None, 0x0040);
			break;
		case 1:
			std::cout << "lcdc status interrupt" << std::endl;
			core->instr_call(Core::JumpCondition::None, 0x0048);
			break;
		case 2:
			std::cout << "timer overflow interrupt" << std::endl;
			core->instr_call(Core::JumpCondition::None, 0x0050);
			break ;
		case 3:
			break;
		case 4:
			std::cout << "joypad interrupt" << std::endl;
			core->instr_call(Core::JumpCondition::None, 0x0060);
			break;
	}
}

void InterruptController::RequestInterrupt(uint16_t interrupt)
{
	switch (interrupt) {
		case VBI:
			_rIF |= 1;
			break;
		case LCDCSI:
			_rIF |= 2;
			break;
		case TOI:
			_rIF |= 4;
			break;
		case STCI:
			_rIF |= 8;
			break;
		case JOYI:
			_rIF |= 16;
			break;
	}
}

void InterruptController::SetIME(bool state)
{
	_rIME = (state == true) ? 1 : 0;
}
