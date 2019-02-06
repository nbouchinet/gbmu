#ifndef INTERRUPTCONTROLLER_CLASS_H
#define INTERRUPTCONTROLLER_CLASS_H
#include <cstdint>

class Core;

class InterruptController
{
	private:
		Core *core;

		uint8_t		_rIF:5; // 0xFF0F
		uint8_t		_rIE:5; // 0xFFFF
		uint8_t		_rIME:1;

	public:
		static constexpr uint16_t VBI = 0x0040;// Vertical Blank Interrupt
		static constexpr uint16_t LCDCSI = 0x0048;// LCDC Status Interrupt
		static constexpr uint16_t TOI = 0x0050;// Timer Overflow Interrupt
		static constexpr uint16_t STCI = 0x0058;// Serial Transfert Completion Interrupt
		static constexpr uint16_t JOYI = 0x0060;// Joypad interrupt

		void	SetCore(Core *core);
		void	SetIME(bool state);
		void	Write(uint16_t addr, uint8_t val);
		uint8_t	Read(uint16_t addr) const;
		void	ParseInterrupt();
		void	ExecuteInterrupt(uint8_t interrupt);
		void	RequestInterrupt(uint16_t interrupt);

		InterruptController(void);
		InterruptController(InterruptController const & src);
		~InterruptController(void);
};

#endif /* INTERRUPTCONTROLLER_CLASS_H */
