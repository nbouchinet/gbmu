#ifndef SCREENOUTPUT_HPP
# define SCREENOUTPUT_HPP

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

	void				reset_screen();
	uint8_t				get_r(uint8_t y, uint8_t x) const;
	uint8_t				get_g(uint8_t y, uint8_t x) const;
	uint8_t				get_b(uint8_t y, uint8_t x) const;
	uint8_t				get_a(uint8_t y, uint8_t x) const;
	uint32_t			get_rgba(uint8_t y, uint8_t x) const;

	void				set_rgba(uint8_t y, uint8_t x, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void				set_rgba(uint8_t y, uint8_t x, uint32_t rgba);
	std::array<std::array<uint32_t, LCD_HEIGHT>, LCD_WIDTH> & 		get_screen() { return _screen; }

private:
	std::array<std::array<uint32_t, LCD_HEIGHT>, LCD_WIDTH>			_screen;
};

#endif
