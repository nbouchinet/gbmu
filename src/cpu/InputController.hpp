#ifndef INPUTCONTROLLER_H
# define INPUTCONTROLLER_H

#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"
#include <atomic>

class InputController : public IReadWrite {
	private:
		ComponentsContainer& _components;
		std::atomic<Byte> _rP1;  //0xFF00
		std::atomic<Byte> _joypad_state;
	
	public:
		void write(Word addr, Byte val) override;
		Byte read(Word addr) const override;
		void key_pressed(int val);
		void key_released(int val);
		Byte get_joypad_state() const;

		InputController(ComponentsContainer& components);
		void reset();
};

#endif // INPUTCONTROLLER_H
