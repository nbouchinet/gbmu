#include "InputController.hpp"

#include "src/Gameboy.hpp"
#include "src/cpu/Core.hpp"
#include "src/cpu/InterruptController.hpp"
#include "utils/Operations_utils.hpp"


InputController::InputController(ComponentsContainer& components)
	: _components(components){
	reset();
}

void InputController::reset() {
	_rP1.store(0xCF);
	_joypad_state.store(0xFF);
}

void InputController::write(Word addr, Byte val) {
	(void)_components;
	if (addr == 0xFF00)
	{
		_rP1 = (_rP1 & 0xF)|(val & 0xF0);
		_rP1 |= 0xC0;
	}
}

Byte InputController::read(Word addr) const{

	/*
	if (addr == 0xFF00) {
		return (_rP1);
	}
	return (0);
	*/
	if (addr == 0xFF00)
		return (get_joypad_state());
	return (0);
}
#include <iostream>
Byte InputController::get_joypad_state() const
{
	Byte ret = _rP1.load();
	//ret ^= 0xFF;
	if (!test_bit(5, ret))
	{
		Byte button_section = _joypad_state.load() >> 4;
		button_section |= 0xF0;
		ret &= button_section;
	}
	else if (!test_bit(4, ret))
	{
		Byte arrow_section = _joypad_state.load() & 0xF;
		arrow_section |= 0xF0;
		ret &= arrow_section;
	}
	return ret;
}

void InputController::key_pressed(int val)
{
	bool was_unset = false;
	if (!test_bit(val, _joypad_state.load()))
		was_unset = true;
	Byte tmp = _joypad_state.load();
	reset_bit(val, tmp);
	_joypad_state.store(tmp);
	bool is_button;
	if (val > 3)
		is_button = true;
	else
		is_button = false;
	Byte key_requested = _rP1;
	/*
	std::cout << "rp1: " << std::hex << +_rP1 << std::endl;
	std::cout << "button: " << is_button << std::endl;
	std::cout << "was_unset: " << was_unset << std::endl;
	*/
	if (((is_button && !test_bit(5, key_requested))
		|| (!is_button && !test_bit(4, key_requested)))
		&& (was_unset))
	{
		//_components.interrupt_controller->request_interrupt(InterruptController::JOYI);
	}
}

void InputController::key_released(int val)
{
	Byte tmp = _joypad_state.load();
	set_bit(val, tmp);
	_joypad_state.store(tmp);
}
