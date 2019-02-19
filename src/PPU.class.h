#ifndef PPU_CLASS_H
# define PPU_CLASS_H

# define LCD_WIDTH 160
# define LCD_HEIGHT 144
# define MAX_SPRITE_PER_LINE 10

#include <iostream>
#include <string>
#include "ScreenOutput.class.h"
#include "Fwd.hpp"
#include "IReadWrite.hpp"

/* TODO LIST

	handle color palettes
	do the pixel mixing algorythm
	!!! update read and write with bcps bcpd ocps ocpd !!!
	!!! change the way color palettes are handled (no pre calculations)
*/

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
	t_spriteInfo	spriteInfo;
// need to add stuff related to palette;
}					t_pixelSegment;

class PPU : public IReadWrite
{
public:
	PPU(ComponentsContainer& components);
	~PPU();

	virtual Byte			read(Word addr);
	virtual void			write(Word addr, Byte);

	static int				getPPUNumber(void);
	static void				switchPPUDebug(bool status);
	bool					isScreenFilled(); // pr toi nico :3
	bool					testBit(uint8_t byte, uint8_t bit_number);

private:
	uint16_t				getTileDataAddress(uint8_t tileIdentifier);
	uint8_t					readMemBank(uint8_t bank, uint16_t address);
	void					setupWindow();
	void					setupBackgroundMemoryStart();
	void					setupSpriteAddressStart();
	bool					isLCDEnabled();
	void					renderScanLine();
	void					setPixelDMG(uint8_t y, uint8_t x, uint8_t value);
	void					renderTiles(); // put pixels in the pipeline from Tiles
	void					renderSprites(); // does the same with sprites, handle some merging too
	void					getSpritesForLine();
	void					sendPixelPipeline();
	void					blendPixels(t_pixelSegment &holder, t_pixelSegment &contender);
	void					translatePalettes();

	ComponentsContainer&	_components;

	uint8_t					_lcdc;					// (0xFF40) lcd controller register
	uint8_t					_stat;					// (0xFF41) PPU status register (flags)
	uint8_t					_scy;					// (0xFF42) Same as above (0-255)
	uint8_t					_scx;					// (0xFF43) Scroll of the screen in the memory (0-255)
	uint8_t					_ly;					// (0xFF44) the line we're rendering, is a register (== Current Scanline)
	uint8_t					_lyc;					// (0xFF45) Scanline comparator
	uint8_t					_dma;					// (0xFF46) 
	uint8_t					_bgp;					// (0xFF47) 
	uint8_t					_obp0;					// (0xFF48) 
	uint8_t					_obp1;					// (0xFF49) 
	uint8_t					_wy;					// (0xFF4A) windowY Same as above (0-143)
	uint8_t					_wx;					// (0xFF4B) windowX Coordinates of the start of the window IN the screen (7-166)
	uint8_t					_hdma1;					// (0xFF51) hdma1-5 are probably unused in the emulator
	uint8_t					_hdma2;					// (0xFF52)
	uint8_t					_hdma3;					// (0xFF53)
	uint8_t					_hdma4;					// (0xFF54)
	uint8_t					_hdma5;					// (0xFF55)
	uint8_t					_bcps;					// (0xFF68)
	uint8_t					_bcpd;					// (0xFF69)
	uint8_t					_ocps;					// (0xFF6A)
	uint8_t					_ocpd;					// (0xFF6B)


	uint16_t				_backgroundDataStart;
	uint16_t				_backgroundChrAttrStart;
	uint16_t				_spriteDataStart;
	uint16_t				_windowChrAttrStart;
	uint8_t					_spriteSize;
	bool					_unsignedTileNumbers;
	bool					_windowingOn;

	// fate of CGB palettes position unknown

	uint16_t				_backgroundColorPalettes[8][4];
	uint16_t				_spriteColorPalettes[8][4];

	t_pixelSegment			_pixelPipeline[LCD_WIDTH];
	t_spriteInfo			_spritesLine[MAX_SPRITE_PER_LINE];	// by default 10 sprites per line
	uint8_t					_nbSprites;


	static int				_nb_PPU;
	static bool				_debug_PPU;
};

#endif
