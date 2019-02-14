#include "InputController.hpp"

#include "src/Gameboy.hpp"
#include "src/cpu/Core.hpp"
#include "src/cpu/InterruptController.hpp"

InputController::InputController(ComponentsContainer& components)
	: _components(components), _rP1(0) {}

void InputController::write(Word addr, Byte val) {
	(void)_components;
	if (addr == 0xFF00)
	{
		_rP1 = val;
	}
}

Byte InputController::read(Word addr) const{
	if (addr == 0xFF00)
	{
		return (_rP1);
	}
	return (0);
}
#include <iostream>
void InputController::handle_input(Byte val)
{
	this->write(0xFF00, val);
	_components.interrupt_controller->RequestInterrupt(InterruptController::JOYI);
	_components.interrupt_controller->ExecuteInterrupt(InterruptController::JOYI);
}
