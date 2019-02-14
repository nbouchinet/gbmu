#ifndef PPU_CLASS_H
# define PPU_CLASS_H

# define LCD_WIDTH 160
# define LCD_HEIGHT 144
# define MAX_SPRITE_PER_LINE 10

#include <iostream>
#include <string>
#include "ScreenOutput.class.h"
#include "Fwd.hpp"

typedef struct		s_spriteInfo
{
	uint8_t			yPos;
	uint8_t			xPos;
	uint8_t			tileNumber;
	uint8_t			flags;
}					t_spriteInfo;

typedef struct		s_pixelSegment
{
	uint8_t			value;
	bool			isSprite;
	t_spriteInfo	*spriteInfo;
}					t_pixelSegment;

class PPU
{
public:
	PPU(ComponentsContainer& components);
	~PPU();

	static int				getPPUNumber(void);
	static void				switchPPUDebug(bool status);

	bool					testBit(uint8_t byte, uint8_t bit_number);
	ScreenOutput			*getDriverScreen() { return (&_driverScreen); } // UGO call dis to get screen

private:
	uint16_t				getTileDataAddress(uint8_t tileIdentifier);
	void					setupWindow();
	void					setupBackgroundMemoryStart();
	void					setupSpriteAddressStart();
	bool					isLCDEnabled();
	void					renderScanLine();
	void					setPixelDMG(uint8_t y, uint8_t x, uint8_t value);
	void					finishLineBackgroundAsWindow();
	void					renderTiles();
	void					renderSprites();
	void					getSpritesForLine();

	ScreenOutput			_driverScreen;
	ComponentsContainer&	_components;


	uint8_t					_lcdc;					// PPU controller register (0xFF41)
	uint8_t					_stat;					// PPU status register (flags) (0xFF40)
	uint8_t					_scrollX;				// Scroll of the screen in the memory (0-255)
	uint8_t					_scrollY;				// Same as above (0-255)
	uint8_t					_currentScanline;		// the line we're rendering, is a register
	uint8_t					_windowX;				// Coordinates of the start of the window IN the screen (7-166)
	uint8_t					_windowY;				// Same as above (0-143)
	uint16_t				_backgroundDataStart;
	uint16_t				_backgroundAttrStart;
	uint16_t				_spriteDataStart;
	uint16_t				_windowAttrStart;
	uint8_t					_spriteSize;
	bool					_unsignedTileValues;
	bool					_windowingOn;

	t_pixelSegment			_pixelPipeline[LCD_WIDTH];
	t_spriteInfo			_spritesLine[MAX_SPRITE_PER_LINE]; // by default 10 sprites per line
	uint8_t					_nbSprites;

	static int				_nb_PPU;
	static bool				_debug_PPU;
};


#endif
