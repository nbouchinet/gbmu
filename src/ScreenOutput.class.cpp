#include "ScreenOutput.class.h"

//------------------------------------------------------------------------------
ScreenOutput::ScreenOutput()
{
	if (_debug_ScreenOutput == true)
		std::cerr << "[ScreenOutput default constructor called]" << std::endl;
	return;
}

//------------------------------------------------------------------------------
ScreenOutput::~ScreenOutput()
{
	if (_debug_ScreenOutput == true)
		std::cerr << "[ScreenOutput destructor called]" << std::endl;
	return;
}

//==============================================================================
uint8_t					ScreenOutput::getR(uint8_t y, uint8_t x) const
{
	uint32_t			tmp;

	if (y >= LCD_HEIGHT && x >= LCD_WIDTH)
	{
		throw (OutOfScreenException());
	}

	tmp = screen[y][x] & 0xFF000000;
	tmp = tmp >> 24;
	return (static_cast<uint8_t>(tmp));
}

//------------------------------------------------------------------------------
uint8_t					ScreenOutput::getG(uint8_t y, uint8_t x) const
{
	uint32_t			tmp;

	if (y >= LCD_HEIGHT && x >= LCD_WIDTH)
	{
		throw (OutOfScreenException());
	}

	tmp = screen[y][x] & 0x00FF0000;
	tmp = tmp >> 16;
	return (static_cast<uint8_t>(tmp));
}

//------------------------------------------------------------------------------
uint8_t					ScreenOutput::getB(uint8_t y, uint8_t x) const
{
	uint32_t			tmp;

	if (y >= LCD_HEIGHT && x >= LCD_WIDTH)
	{
		throw (OutOfScreenException());
	}

	tmp = screen[y][x] & 0x0000FF00;
	tmp = tmp >> 8;

	return (static_cast<uint8_t>(tmp));
}

//------------------------------------------------------------------------------
uint8_t					ScreenOutput::getA(uint8_t y, uint8_t x) const
{
	uint32_t			tmp;

	if (y >= LCD_HEIGHT && x >= LCD_WIDTH)
	{
		throw (OutOfScreenException());
	}

	tmp = screen[y][x] & 0x000000FF;

	return (static_cast<uint8_t>(tmp));
}

//------------------------------------------------------------------------------
uint32_t				ScreenOutput::getRGBA(uint8_t y, uint8_t x) const
{
	if (y >= LCD_HEIGHT && x >= LCD_WIDTH)
	{
		throw (OutOfScreenException());
	}
	return (screen[y][x]);
}

//------------------------------------------------------------------------------
void					ScreenOutput::setRGBA(uint8_t y, uint8_t x, uint32_t rgba)
{
	if (y >= LCD_HEIGHT && x >= LCD_WIDTH)
	{
		throw (OutOfScreenException());
	}
	screen[y][x] = rgba;
}

//------------------------------------------------------------------------------
void					ScreenOutput::setRGBA(uint8_t y, uint8_t x, uint8_t R, uint8_t G, uint8_t B, uint8_t A)
{
	uint32_t			rPart;
	uint32_t			gPart;
	uint32_t			bPart;

	if (y >= LCD_HEIGHT && x >= LCD_WIDTH)
	{
		throw (OutOfScreenException());
	}

	rPart = ((static_cast<uint32_t>(R)) << 24);
	gPart = ((static_cast<uint32_t>(G)) << 16);
	bPart = ((static_cast<uint32_t>(B)) << 8);

	screen[y][x] = (rPart + gPart + bPart + A);
}

//==============================================================================
void					ScreenOutput::switchScreenOutputDebug(bool status) { ScreenOutput::_debug_ScreenOutput = status; }

//------------------------------------------------------------------------------
bool					ScreenOutput::_debug_ScreenOutput = false;