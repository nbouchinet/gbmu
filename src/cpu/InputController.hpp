#ifndef INPUTCONTROLLER_H
# define INPUTCONTROLLER_H

#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"

class InputController : public IReadWrite {
	private:
		ComponentsContainer& _components;
		Byte _rP1;  //0xFF00
	
	public:
		void write(Word addr, Byte val) override;
		Byte read(Word addr) const override;
		void handle_input(Byte val);

		InputController(ComponentsContainer& components);
		void reset();
};

#endif // INPUTCONTROLLER_H
