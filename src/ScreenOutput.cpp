#include "ScreenOutput.hpp"

//------------------------------------------------------------------------------
ScreenOutput::ScreenOutput()
{
	reset_screen();
	return;
}

//------------------------------------------------------------------------------
ScreenOutput::~ScreenOutput()
{
	return;
}

//==============================================================================
void					ScreenOutput::reset_screen()
{
	for (int y = 0; y < LCD_HEIGHT; y++)
	{
		for (int x = 0; x < LCD_WIDTH; x++)
		{
			_buffer_dirty[y][x] = 0xFFFFFFFF;
			_buffer_clean[y][x] = 0xFFFFFFFF;
		}
	}
	return;
}

//------------------------------------------------------------------------------
uint8_t					ScreenOutput::get_r(uint8_t y, uint8_t x) const
{
	uint32_t			tmp;

	if (y >= LCD_HEIGHT && x >= LCD_WIDTH)
	{
		throw (OutOfScreenException());
	}

	tmp = _buffer_clean[y][x] & 0xFF000000;
	tmp = tmp >> 24;
	return (static_cast<uint8_t>(tmp));
}

//------------------------------------------------------------------------------
uint8_t					ScreenOutput::get_g(uint8_t y, uint8_t x) const
{
	uint32_t			tmp;

	if (y >= LCD_HEIGHT && x >= LCD_WIDTH)
	{
		throw (OutOfScreenException());
	}

	tmp = _buffer_clean[y][x] & 0x00FF0000;
	tmp = tmp >> 16;
	return (static_cast<uint8_t>(tmp));
}

//------------------------------------------------------------------------------
uint8_t					ScreenOutput::get_b(uint8_t y, uint8_t x) const
{
	uint32_t			tmp;

	if (y >= LCD_HEIGHT && x >= LCD_WIDTH)
	{
		throw (OutOfScreenException());
	}

	tmp = _buffer_clean[y][x] & 0x0000FF00;
	tmp = tmp >> 8;

	return (static_cast<uint8_t>(tmp));
}

//------------------------------------------------------------------------------
uint8_t					ScreenOutput::get_a(uint8_t y, uint8_t x) const
{
	uint32_t			tmp;

	if (y >= LCD_HEIGHT && x >= LCD_WIDTH)
	{
		throw (OutOfScreenException());
	}

	tmp = _buffer_clean[y][x] & 0x000000FF;

	return (static_cast<uint8_t>(tmp));
}

//------------------------------------------------------------------------------
uint32_t				ScreenOutput::get_rgba(uint8_t y, uint8_t x) const
{
	if (y >= LCD_HEIGHT && x >= LCD_WIDTH)
	{
		throw (OutOfScreenException());
	}
	return (_buffer_clean[y][x]);
}

//------------------------------------------------------------------------------
void					ScreenOutput::set_rgba(uint8_t y, uint8_t x, uint32_t rgba)
{
	if (y >= LCD_HEIGHT && x >= LCD_WIDTH)
	{
		throw (OutOfScreenException());
	}
	_buffer_dirty[y][x] = rgba;
}

//------------------------------------------------------------------------------
void					ScreenOutput::set_rgba(uint8_t y, uint8_t x, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	uint32_t			r_part;
	uint32_t			g_part;
	uint32_t			b_part;

	if (y >= LCD_HEIGHT && x >= LCD_WIDTH)
	{
		throw (OutOfScreenException());
	}

	r_part = ((static_cast<uint32_t>(r)) << 24);
	g_part = ((static_cast<uint32_t>(g)) << 16);
	b_part = ((static_cast<uint32_t>(b)) << 8);

	_buffer_dirty[y][x] = (r_part + g_part + b_part + a);
}

//==============================================================================
