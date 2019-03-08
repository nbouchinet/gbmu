#ifndef SCREENOUTPUT_CLASS_H
# define SCREENOUTPUT_CLASS_H

#include <iostream>
#include <array>

#define LCD_HEIGHT 144
#define LCD_WIDTH 160

/*
 * RGBA format on uint32_t (each fields gets 1 byte)
 *
 */

class OutOfScreenException : public std::exception
{
	public:
	OutOfScreenException() : std::exception() { }
	virtual ~OutOfScreenException() throw() { }
	virtual const char * what() const throw() { return ("OutOfScreenException : coordinates x or y are out of the specified dimentions"); }
};

class ScreenOutput
{
public:
	ScreenOutput();
	~ScreenOutput();

	static void			switchScreenOutputDebug(bool status);

	uint8_t				getR(uint8_t y, uint8_t x) const;
	uint8_t				getG(uint8_t y, uint8_t x) const;
	uint8_t				getB(uint8_t y, uint8_t x) const;
	uint8_t				getA(uint8_t y, uint8_t x) const;
	uint32_t			getRGBA(uint8_t y, uint8_t x) const;

	void				setRGBA(uint8_t y, uint8_t x, uint8_t R, uint8_t G, uint8_t B, uint8_t A);
	void				setRGBA(uint8_t y, uint8_t x, uint32_t rgba);
	std::array<std::array<uint32_t, LCD_HEIGHT>, LCD_WIDTH> & 		getScreen() { return screen; }

private:
	std::array<std::array<uint32_t, LCD_HEIGHT>, LCD_WIDTH>			screen;

	static bool			_debug_ScreenOutput;
};

#endif