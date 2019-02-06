#ifndef TIMER_H
#define TIMER_H
#include <cstdint>

class InterruptController;

class Timer
{
	private:
		static constexpr uint16_t DIV = 0xFF04; // Divider register
		static constexpr uint16_t TIMA = 0xFF05; // Timer counter
		static constexpr uint16_t TMA = 0xFF06; // Timer modulo
		static constexpr uint16_t TAC = 0xFF07; // Timer controller
		InterruptController *ic;

		uint8_t		_rDIV:8;
		uint8_t		_rTIMA:8;
		uint8_t		_rTMA:8;
		uint8_t		_rTAC:3;
		uint16_t	_counter;
		uint8_t		_rDIVCounter;

	public:
		Timer(InterruptController *ic) : ic(ic){};
		auto		GetFrequence() const { return Read(TAC) & 0x3; }
		auto		GetCounter() const { return _counter; }
		void		UpdateDivider(uint16_t cycles);
		bool		TimerEnabled() const { return (_rTAC & 0x4); }
		void		EnableTimer() {_rTAC |= 0x4;}
		void		SetFrequence();
		void		Update(uint16_t cycles);
		uint8_t		Read(uint16_t addr) const;
		void		Write(uint16_t addr, uint8_t val);
};

#endif /* TIMER_H */
